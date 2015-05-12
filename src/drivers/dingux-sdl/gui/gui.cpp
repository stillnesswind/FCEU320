
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../dingoo.h"
#include "../dingoo-video.h" 
 
#include "../dface.h"
  
#include "bitmap.h"
#include "font.h"
  
#include "gfceu320.h" 

// ...
int RunFileBrowser(char *source, char *romname, const char *types[], const char *info = NULL);

typedef struct _menu_entry
{
    const char *name; 
    const char *info;
    int (*command)();
} MenuEntry; 

static struct bitmap16 *g_bg;
static uint16 *g_psdl;
static unsigned short vbuffer[320 * 240];
static uint8 g_preview[256 * 256 + 8];
static uint8 g_ispreview;
static char g_romname[32] = "";
static char g_time[16] = "";
static char g_battery[16] = "";
static int g_dirty = 1;
static int g_slot = 0;
static int g_romtype;


static unsigned long g_key = 0, last_key;
static int counter = 0;
void readkey()
{
    last_key = g_key;
    g_key = dingoo_joystick_read(0);

    if (g_key == 0) counter = 0;
}

int parsekey(unsigned long code, int repeat = 0)
{ 
    if (g_key & code) {
        if (g_key != last_key) {
            counter = 0;
            g_dirty = 1;  
            return 1;
        }

        if (repeat && (counter > 5)) {
            counter = 0;
            g_dirty = 1; 
            return 1;
        }
           
        counter++;
        return 0;
    }

    return 0;
}

void draw_bg(unsigned short *screen, struct bitmap16 *bg)
{
    register uint16 *src = (uint16 *)bg->data;
    register uint16 *dst = (uint16 *)screen;
    int x, y;
    for(y=0;y<240;y++)
        for(x=0;x<320;x++) *dst++ = *src++;
}

int update_time()
{
    static clock_t c, clast = 0;
    struct tm *ltime;
    time_t t;

    c = clock();

    if ((c-clast)/CLOCKS_PER_SEC > 59 || !clast) {
        clast = c;
        time(&t);
        ltime = localtime(&t);
    
        sprintf(g_time, "%02d:%02d\n", ltime->tm_hour, ltime->tm_min); 
        return 1;
    } 
    
    return 0;
}
 
void update_battery()
{ 
#ifdef A320_HARDWARE
    int volts = dingoo_get_voltage();
    int batt = ((volts-3611)/128)*100;
    if (batt < 0) batt = 0; 
    if (batt > 100) batt = 100;
    sprintf(g_battery, "%d%%", batt);
#else
    strcpy(g_battery, "100%");
#endif
}

// Include additional files
#include "file_browser.cpp"
#include "settings_menu.cpp"

/* MENU COMMANDS */

// Load preview from save state
void load_preview()
{
    char sname[2048];
    strcpy(sname, FCEU_MakeFName(FCEUMKF_STATE,g_slot,0).c_str());
    FILE *fp = fopen(sname, "rb");
    if (fp) {
	    // TODO - check the offset ...
        fseek(fp, 5497, SEEK_SET); 
	    fread(g_preview, 1, 256*256 + 8, fp); 
        fclose(fp); 
	    g_ispreview = 1; 
    } 
    else {
	    memset(g_preview, 0, 256*256 + 8);
	    g_ispreview = 0;
    } 
}

#define MASK  			    (0xF7DEF7DE | (0xF7DEF7DE << 16))
#define LMASK 			    (0x08210821 | (0x08210821 << 16))
#define INTERPOLATE(A, B) 	(((A & MASK) >> 1) + ((B & MASK) >> 1) + (A & B & LMASK))

void draw_preview(unsigned short *dest, int x, int y)
{
    uint8 *PBuf = g_preview;
    uint16 *dst = (uint16 *)dest;

    PBuf += 256*8 + 16;
    dst += y*320 + x;

    for(y=0;y<76;y++) {
        for(x=0;x<32;x++) {    
	    *dst++ = INTERPOLATE(g_psdl[*PBuf], g_psdl[*(PBuf+1)]);
	    *dst++ = INTERPOLATE(g_psdl[*(PBuf+3)], g_psdl[*(PBuf+4)]);
	    *dst++ = INTERPOLATE(g_psdl[*(PBuf+7)], g_psdl[*(PBuf+6)]);
	    PBuf += 8;
	}

	PBuf += 256*2;
	dst += 224;
    }
}

void draw_shot_preview(unsigned short *dest, int x, int y)
{
    extern uint8 *XBuf;
    uint8 *PBuf = XBuf;
    uint16 *dst = (uint16 *)dest;

    PBuf += 256*8 + 16;
    dst += y*320 + x;

    for(y=0;y<76;y++) {
        for(x=0;x<32;x++) {    
	        *dst++ = INTERPOLATE(g_psdl[*PBuf], g_psdl[*(PBuf+1)]);
	        *dst++ = INTERPOLATE(g_psdl[*(PBuf+3)], g_psdl[*(PBuf+4)]);
	        *dst++ = INTERPOLATE(g_psdl[*(PBuf+7)], g_psdl[*(PBuf+6)]);
	        PBuf += 8;
	    }

	    PBuf += 256*2;
	    dst += 224;
    }
}

// Main menu commands
static int load_rom()
{
    const char *types[] = {".nes", ".fds", ".zip", ".fcm", ".fm2", ".nsf", NULL};
    char filename[128], romname[128];
    int error;

    if (!RunFileBrowser(NULL, filename, types)) {
        CloseGame();
        dingoo_deinit();
        exit(-1);
    }

    //  TODO - Must close game here?
    CloseGame();

    // Is this a movie?
    if (!(error = FCEUD_LoadMovie(filename, romname))) 
        error = LoadGame(filename);

   	if(error != 1) {
        CloseGame();
        dingoo_deinit();
  		exit(-1);
   	}    

    return 1;
}

static int reset_nes()
{
    FCEUI_ResetNES(); 
    return 1;
}

// Dirty way of flipping disc
extern uint8 SelectDisk,InDisk;
static int flip_disc()
{
    if (g_romtype != GIT_FDS) return 0;
    //FCEUI_FDSFlip();
    return 1;
}

static int save_state()
{
    FCEUI_SaveState(NULL);
    return 1;
}

static int load_state()
{
    FCEUI_LoadState(NULL);
    return 1;
}

static int save_screenshot()
{
    FCEUI_SaveSnapshot();
    return 1; 
}

static int cmd_settings_menu() 
{
    return RunSettingsMenu(); 
}

static int cmd_exit()
{
    FCEUI_CloseGame();
    return 1;
} 


/* MAIN MENU */

static MenuEntry main_menu[] =
{
    {"Load ROM", "Load new rom or movie", load_rom},
	{"Reset", "Reset NES", reset_nes},
	{"Flip disc", "Switch side or disc (FDS)", flip_disc},
	{"Save state", "Save current state", save_state},
	{"Load state", "Load emulation state", load_state},
    {"Screenshot", "Save current frame shot", save_screenshot},
	{"Settings", "Change current settings",  cmd_settings_menu},
    {"Exit", "Exit emulator", cmd_exit}
};

extern char FileBase[2048];
int FCEUGUI_Init(FCEUGI *gi)
{   
    // Load bg image
    g_bg = load_bmp_16bpp(gfceu320_bg, 320, 240);
    if (g_bg == NULL) return -1;
    
    if (InitFont() < 0) return -2;

    // Call this here?  
    dingoo_flush_video();

    if (gi) {
        if (strlen(FileBase) > 28) {
        	strncpy(g_romname, FileBase, 24);
	        strcat(g_romname, "..."); 
        } 
        else strcpy(g_romname, FileBase); 
        g_romtype = gi->type;
    }

    return 0;
}

void FCEUGUI_Reset(FCEUGI *gi)
{
    g_psdl = FCEUD_GetPaletteArray16();

    if (strlen(FileBase) > 28) {
      	strncpy(g_romname, FileBase, 24);
        strcat(g_romname, "..."); 
    } 
    else strcpy(g_romname, FileBase); 
    g_romtype = gi->type;
}

void FCEUGUI_Kill() 
{
    // free stuff 
    if (g_bg) free_bitmap_16bpp(g_bg); 
    KillFont();
}

void FCEUGUI_Run()
{
    static int index = 0;
    static int spy = 76; 
    int done = 0, y, i;

    // Mute sound thread
    dingoo_sound_thread_mute();

    load_preview();

    g_dirty = 1;
    while (!done) {
	    // Get time and battery every second
        if (update_time()) {
    	    update_battery();
	        g_dirty = 1;
        }
 
        // Parse input
        readkey();
        if (parsekey(DINGOO_B)) done = 1;
           
        if (parsekey(DINGOO_UP, 1)) { 
            if (index > 0) {
	        	index--;  
   			    spy -= 16;
    	    }
	    }

	    if (parsekey(DINGOO_DOWN, 1)) {
	        if (index < 7) {
	            index++; 
	            spy += 16;
   		    } 
    	} 

   		if (parsekey(DINGOO_A))
    	    done = main_menu[index].command();

   		if (index == 3 || index == 4) {
    	    if (parsekey(DINGOO_RIGHT, 1)) {
        		if (g_slot < 9) {
        		    g_slot++;
        		    FCEUI_SelectState(g_slot, 0);
        		    load_preview();
        		}
    	    } 

    	    if (parsekey(DINGOO_LEFT, 1))  {
        		if (g_slot > 0) {
        		    g_slot--;
        		    FCEUI_SelectState(g_slot, 0);
        		    load_preview();
        		}
    	    } 
    	}

	    // Must draw bg only when needed  
        // Draw stuff 
        if( g_dirty )  
        {
	        draw_bg(vbuffer, g_bg);

          	// Draw time and battery every minute
    	    DrawText(vbuffer, g_time, 148, 5); 
            DrawText(vbuffer, g_battery, 214, 5);	

    	    if (index == 3 || index == 4) { 
               // Draw state preview
    	       draw_preview(vbuffer, 185, 100);
	           if (!g_ispreview) DrawChar(vbuffer, SP_NOPREVIEW, 207, 135);
	        }

            if (index == 5) {
                draw_shot_preview(vbuffer, 185, 100);
            }

        	DrawChar(vbuffer, SP_ROM, 40, 38); 
	        DrawText(vbuffer, g_romname, 86, 37); 
 	
    	    // Draw menu 
	        for(i=0,y=72;i < 8;i++,y+=16) {
	           DrawText(vbuffer, main_menu[i].name, 50, y);
            }
 
	        // Draw info
        	DrawText(vbuffer, main_menu[index].info, 16, 225);

	        // Draw selector
	        DrawChar(vbuffer, SP_SELECTOR, 34, spy);
    
	        // If save/load state render slot preview and number
        	if (index == 3 || index == 4) {
	            char tmp[32];
	            sprintf(tmp, "Slot %d", g_slot); 
	            DrawText(vbuffer, tmp, 208, 80);  
		
	            if (g_slot > 0) DrawChar(vbuffer, SP_LEFTARROW, 168, 133);
	            if (g_slot < 9) DrawChar(vbuffer, SP_RIGHTARROW, 286, 133);
	        }    

            // If screenshot render current frame preview
            if (index == 5) {
                DrawText(vbuffer, "Preview", 204, 80);        
            }

            g_dirty = 0;
        }

        dingoo_timer_delay(16);

        // Update real screen
        memcpy(dingoo_screen15, vbuffer, 320*240*sizeof(unsigned short));
    }      

    g_psdl = FCEUD_GetPaletteArray16();

    // Clear screen
    dingoo_clear_video();
}
