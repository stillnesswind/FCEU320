/* FCE Ultra - NES/Famicom Emulator
 *
 * Copyright notice for this file:
 *  Copyright (C) 2002 Xodnizel  
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License 
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

/// \file
/// \brief Handles the graphical game display for the SDL implementation.

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "dingoo.h"
#include "dingoo-video.h"

#include "../common/vidblit.h"
#include "../../fceu.h"
#include "../../version.h"

#include "dface.h"

#include "../common/configSys.h"

// GLOBALS
extern Config *g_config;

// STATIC GLOBALS
static uint16 *s_tmpscreen;

static int s_curbpp;
static int s_srendline, s_erendline;
static int s_tlines;
static int s_inited;

static int s_eefx;
static int s_clipSides;
static int s_fullscreen;
static int noframe;

static int FDSTimer = 0;
int FDSSwitchRequested = 0;

#define NWIDTH	(256 - (s_clipSides ? 16 : 0))
#define NOFFSET	(s_clipSides ? 8 : 0)

/* Blur effect taken from vidblit.cpp */
static uint32 palettetranslate[65536*4];
static uint32 CBM[3] = {63488,2016,31};
static uint16 s_psdl[256];

struct Color {
    uint8 r;
    uint8 g;
    uint8 b;
    uint8 unused;
};

static struct Color s_cpsdl[256];

#define BLUR_RED	30
#define BLUR_GREEN	30
#define BLUR_BLUE	20


/**
g * Attempts to destroy the graphical video display.  Returns 0 on
 * success, -1 on failure.
 */

//draw input aids if we are fullscreen
bool FCEUD_ShouldDrawInputAids()
{
	return s_fullscreen!=0;
}
 
int
KillVideo()
{
    // return failure if the video system was not initialized
    if(s_inited == 0)
        return -1;
    
    // if the rest of the system has been initialized, shut it down
	
    if( s_fullscreen && s_tmpscreen ) free(s_tmpscreen);

    dingoo_clear_video();
    dingoo_flush_video();

    s_inited = 0;
    return 0;
}

/**
 * These functions determine an appropriate scale factor for fullscreen/
 */
inline double GetXScale(int xres)
{
    return ((double)xres) / NWIDTH;
}
inline double GetYScale(int yres)
{
    return ((double)yres) / s_tlines;
}   
void FCEUD_VideoChanged()
{
	int buf;
	g_config->getOption("SDL.PAL", &buf);
	if(buf)
		PAL = 1;
	else
		PAL = 0;
}
/**
 * Attempts to initialize the graphical video display.  Returns 0 on
 * success, -1 on failure.
 */
int
InitVideo(FCEUGI *gi)
{
    FCEUI_printf("Initializing video...\n");

    // load the relevant configuration variables
    g_config->getOption("SDL.Fullscreen", &s_fullscreen);
    g_config->getOption("SDL.ClipSides", &s_clipSides);

    // check the starting, ending, and total scan lines
    FCEUI_GetCurrentVidSystem(&s_srendline, &s_erendline);
    s_tlines = s_erendline - s_srendline + 1;

    int brightness;
    g_config->getOption("SDL.Brightness", &brightness);
    dingoo_set_brightness(brightness);

    // initialize dingoo video mode
    dingoo_set_video_mode(16, 320, 240);

    s_inited = 1;
    FDSSwitchRequested = 0;

    int desbpp;
    g_config->getOption("SDL.SpecialFilter", &s_eefx);
        
    if( s_fullscreen ) {
	    s_tmpscreen = (uint16 *)malloc(320*240*2);
    	if(!s_tmpscreen) {
 	        FCEUD_PrintError("Cannot allocate memory!");
    	    return -1;
	    }
    }
    else s_tmpscreen = (uint16 *)dingoo_screen15;

    SetPaletteBlitToHigh((uint8 *)s_cpsdl);

    return 0;
}

/**
 * Toggles the full-screen display.
 */
void
ToggleFS()
{
}

/* Taken from /src/drivers/common/vidblit.cpp */
static void CalculateShift(uint32 *CBM, int *cshiftr, int *cshiftl)
{
             int a,x,z,y;
             cshiftl[0]=cshiftl[1]=cshiftl[2]=-1;
             for(a=0;a<3;a++)
             {
              for(x=0,y=-1,z=0;x<32;x++)
              {
               if(CBM[a]&(1<<x))
               {
                if(cshiftl[a]==-1) cshiftl[a]=x;
                z++;
               }
              }
              cshiftr[a]=(8-z);
             }
}

void SetPaletteBlitToHigh(uint8 *src)
{ 
    int cshiftr[3];
    int cshiftl[3];
    int x,y;

    CalculateShift(CBM, cshiftr, cshiftl);

    if (s_eefx)
        for(x=0;x<256;x++)   
        {
            uint32 r,g,b;
            for(y=0;y<256;y++)
            {
                r=src[x<<2]*(100-BLUR_RED);
                g=src[(x<<2)+1]*(100-BLUR_GREEN);
                b=src[(x<<2)+2]*(100-BLUR_BLUE);
  
                r+=src[y<<2]*BLUR_RED;
                g+=src[(y<<2)+1]*BLUR_GREEN;
                b+=src[(y<<2)+2]*BLUR_BLUE;
                r/=100;
	        g/=100; 
	        b/=100;

	        if(r>255) r=255; if(g>255) g=255; if(b>255) b=255;
                palettetranslate[x|(y<<8)]=((r>>cshiftr[0])<<cshiftl[0])|
				   ((g>>cshiftr[1])<<cshiftl[1])|
				   ((b>>cshiftr[2])<<cshiftl[2]);
	    }
        }
        else
            for(x=0;x<65536;x++)
            {
                uint16 lower,upper;

                lower=(src[((x&255)<<2)]>>cshiftr[0])<<cshiftl[0];
                lower|=(src[((x&255)<<2)+1]>>cshiftr[1])<<cshiftl[1];
                lower|=(src[((x&255)<<2)+2]>>cshiftr[2])<<cshiftl[2];
                upper=(src[((x>>8)<<2)]>>cshiftr[0])<<cshiftl[0];
                upper|=(src[((x>>8)<<2)+1]>>cshiftr[1])<<cshiftl[1];
                upper|=(src[((x>>8)<<2)+2]>>cshiftr[2])<<cshiftl[2];

                palettetranslate[x]=lower|(upper<<16);
            }
}

/**
 * Sets the color for a particular index in the palette.
 */
void
FCEUD_SetPalette(uint8 index,
                 uint8 r,
                 uint8 g,
                 uint8 b)
{
   s_cpsdl[index].r = r;
   s_cpsdl[index].g = g;
   s_cpsdl[index].b = b;

   //uint32 col = (r << 16) | (g << 8) | b;
   //s_psdl[index] = (uint16)COL32_TO_16(col);
   s_psdl[index] = dingoo_video_color15(r, g, b);

   if (index == 255) SetPaletteBlitToHigh((uint8 *)s_cpsdl);
}

/**
 * Gets the color for a particular index in the palette.
 */
void
FCEUD_GetPalette(uint8 index,
                 uint8 *r,
                 uint8 *g,
                 uint8 *b)
{
    *r = s_cpsdl[index].r;
    *g = s_cpsdl[index].g;
    *b = s_cpsdl[index].b;
}

uint16 * 
FCEUD_GetPaletteArray16()
{
    return s_psdl;
}

/** 
 * Pushes the palette structure into the underlying video subsystem.
 */
static void
RedoPalette()
{
}

// XXX soules - console lock/unlock unimplemented?

///Currently unimplemented.
void LockConsole(){}

///Currently unimplemented.
void UnlockConsole(){}

#define READU16(x) 	(uint16) ((uint16)(x)[0] | (uint16)(x)[1] << 8) 

/**
 * Pushes the given buffer of bits to the screen.
 */
void
BlitScreen(uint8 *XBuf)
{
    int x, x2, y, y2;

    // Taken from fceugc
    // FDS switch disk requested - need to eject, select, and insert
    // but not all at once!
    if(FDSSwitchRequested)
    {
        switch(FDSSwitchRequested)
        {
            case 1:
                FDSSwitchRequested++;
                FCEUI_FDSInsert(); // eject disk
                FDSTimer = 0;
                break;
            case 2:
                if(FDSTimer > 60)
                {
                    FDSSwitchRequested++;
                    FDSTimer = 0;
                    FCEUI_FDSSelect(); // select other side
                    FCEUI_FDSInsert(); // insert disk
                }
                break;
            case 3:
                if(FDSTimer > 200) 
                {
                    FDSSwitchRequested = 0;
                    FDSTimer = 0;
                }
                break;
        }
        FDSTimer++;
    }

    // TODO - Move these to its own file?
    if (s_fullscreen == 1) { // Semi fullscreen (280x240)
        XBuf += (s_srendline * 256) + 8;
   
	    if (s_eefx) { // Blur effect
            register uint16 *dest = (uint16 *)dingoo_screen15;
            dest += (320 * s_srendline) + 20; 

            for(y=s_tlines;y;y--) {
                for(x=240;x;x-=6) {
		            // TODO - is this necessary?
	    	        // register uint8 *pBuf = XBuf; 

    	            *dest++ = palettetranslate[*XBuf|(*(XBuf-1)<<8)];
	                *dest++ = palettetranslate[*(XBuf+1)|(*(XBuf)<<8)]; 
	                *dest++ = palettetranslate[*(XBuf+2)|(*(XBuf+1)<<8)];
	                *dest++ = palettetranslate[*(XBuf+3)|(*(XBuf+2)<<8)];
	                *dest++ = palettetranslate[*(XBuf+3)|(*(XBuf+2)<<8)];
	                *dest++ = palettetranslate[*(XBuf+4)|(*(XBuf+3)<<8)];
	                *dest++ = palettetranslate[*(XBuf+5)|(*(XBuf+4)<<8)]; 
	    	        XBuf += 6;
                }
            	XBuf += 16;
                dest += 40;
            }
        }
	    else { // semi fullscreen no blur
	        register uint16 *dest = (uint16 *)dingoo_screen15;
	        dest += (320 * s_srendline) + 20;
	        for(y=s_tlines;y;y--) {
                for(x=240;x;x-=6) {
        		    // TODO - is this necessary?
	        	    // register uint8 *d = XBuf; 

                    *dest++ = s_psdl[*XBuf];
	                *dest++ = s_psdl[*(XBuf+1)]; 
	                *dest++ = s_psdl[*(XBuf+2)];
	                *dest++ = s_psdl[*(XBuf+3)];
	                *dest++ = s_psdl[*(XBuf+3)];
	                *dest++ = s_psdl[*(XBuf+4)];
	                *dest++ = s_psdl[*(XBuf+5)];
		            XBuf += 6;
	            }
 	            XBuf += 16;
                dest += 40;
            }
        }
    }
    else if (s_fullscreen == 2) {
        XBuf += (s_srendline * 256) + 8;
   
	    if (s_eefx) { // Blur effect
            register uint16 *dest = (uint16 *)dingoo_screen15;
            dest += (320 * s_srendline); 

            for(y=s_tlines;y;y--) {
                for(x=240;x;x-=6) {
		            // TODO - is this necessary?
	    	        // register uint8 *pBuf = XBuf; 

    	            *dest++ = palettetranslate[*XBuf|(*(XBuf-1)<<8)];
	                *dest++ = palettetranslate[*XBuf|(*(XBuf-1)<<8)];
	                *dest++ = palettetranslate[*(XBuf+1)|(*(XBuf)<<8)]; 
	                *dest++ = palettetranslate[*(XBuf+2)|(*(XBuf+1)<<8)];
	                *dest++ = palettetranslate[*(XBuf+3)|(*(XBuf+2)<<8)];
	                *dest++ = palettetranslate[*(XBuf+3)|(*(XBuf+2)<<8)];
	                *dest++ = palettetranslate[*(XBuf+4)|(*(XBuf+3)<<8)];
	                *dest++ = palettetranslate[*(XBuf+5)|(*(XBuf+4)<<8)]; 
	    	        XBuf += 6;
                }
            	XBuf += 16;
            }
        }
	    else { // Fullscreen no blur
	        register uint32 *dest = (uint32 *)dingoo_screen15;
	        dest += (160 * s_srendline);
	        for(y=s_tlines;y;y--) {
                for(x=240;x;x-=6) {
        		    // TODO - is this necessary?
	        	    // register uint8 *d = XBuf; 

		            *dest++= palettetranslate[ *(uint16 *)XBuf ];
        		    *dest++ = palettetranslate[ READU16(XBuf+1) ];
		            *dest++ = palettetranslate[ READU16(XBuf+3) ];
		            *dest++ = palettetranslate[ *(uint16 *)(XBuf+4) ];
		            XBuf += 6;
	            }
 	            XBuf += 16;
            }
        }
    }
    else {	// No fullscreen
    	static int pinc = (320 - NWIDTH)>>1;

	    if (s_eefx) { // DaBlur!!
            register uint16 *dest = (uint16 *)s_tmpscreen;
  	        static uint8 last = 0x00;
	    
	        // XXX soules - not entirely sure why this is being done yet
	        XBuf += (s_srendline * 256) + NOFFSET;
	        dest += (s_srendline * 320) + pinc;

	        for(y=s_tlines;y;y--,XBuf+=256-NWIDTH) {
	            for(x=NWIDTH>>2;x;x--) {
	        	    *dest++ = palettetranslate[*XBuf|(last<<8)];
	        	    *dest++ = palettetranslate[*(XBuf+1)|(*XBuf<<8)];
	        	    *dest++ = palettetranslate[*(XBuf+2)|(*(XBuf+1)<<8)];
	        	    *dest++ = palettetranslate[*(XBuf+3)|(*(XBuf+2)<<8)];
	        	    last = *(XBuf+3);
	        	    XBuf+=4;
	            }
	            dest += pinc<<1;    
            }
        }
    	else {
	        register uint32 *dest = (uint32 *)s_tmpscreen;

	        // XXX soules - not entirely sure why this is being done yet
	        XBuf += (s_srendline * 256) + NOFFSET;
	        dest += (s_srendline * 320) + pinc>>1;

	        for(y=s_tlines;y;y--,XBuf+=256-NWIDTH) {
	            for(x=NWIDTH>>3;x;x--) {
	    	        *dest++ = palettetranslate[*(uint16 *)XBuf];
	    	        *dest++ = palettetranslate[*(uint16 *)(XBuf+2)];
    	    	    *dest++ = palettetranslate[*(uint16 *)(XBuf+4)];
	        	    *dest++ = palettetranslate[*(uint16 *)(XBuf+6)];
	        	    XBuf+=8;
	            }
	            dest += pinc;    
	        }
        }
    }
}

/**
 *  Converts an x-y coordinate in the window manager into an x-y
 *  coordinate on FCEU's screen.
 */
uint32
PtoV(uint16 x,
     uint16 y)
{
    y = (uint16)((double)y);
    x = (uint16)((double)x);
    if(s_clipSides) {
        x += 8;
    }
    y += s_srendline;
    return (x | (y << 16));
}

bool disableMovieMessages = false;
bool FCEUI_AviDisableMovieMessages()
{
	if (disableMovieMessages)
		return true;

	return false;
}

void FCEUI_SetAviDisableMovieMessages(bool disable)
{
	disableMovieMessages = disable;
}
