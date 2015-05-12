
// Externals
extern Config *g_config;

/* MENU COMMANDS */

// Fullscreen mode
static char *scale_tag[] = {
        "Original",
        "280x240",
        "Fullscreen"
};

static void fullscreen_update(unsigned long key)
{
    int val;
    g_config->getOption("SDL.Fullscreen", &val);

    if (key & DINGOO_RIGHT) val = val < 2 ? val+1 : 2;
    if (key & DINGOO_LEFT) val = val > 0 ? val-1 : 0;
   
    g_config->setOption("SDL.Fullscreen", val);
}

// Blur effect
static void blur_update(unsigned long key)
{
    int val, tmp;
    g_config->getOption("SDL.SpecialFilter", &tmp);
   
    if (key & DINGOO_RIGHT) val = 1;
    if (key & DINGOO_LEFT) val = 0;

    g_config->setOption("SDL.SpecialFilter", val);
}

// Clip sides
static void clip_update(unsigned long key)
{
    int val, tmp;
    g_config->getOption("SDL.ClipSides", &tmp);

    if (key & DINGOO_RIGHT) val = 1;
    if (key & DINGOO_LEFT) val = 0;

    g_config->setOption("SDL.ClipSides", val);
}

// NTSC TV's colors
static void ntsc_update(unsigned long key)
{
    int val;

    if (key & DINGOO_RIGHT) val = 1;
    if (key & DINGOO_LEFT) val = 0;

    g_config->setOption("SDL.NTSCpalette", val);    
}

// NTSC Tint
static void tint_update(unsigned long key)
{
    int val;
    g_config->getOption("SDL.Tint", &val);

    if (key & DINGOO_RIGHT) val = val < 255 ? val+1 : 255;
    if (key & DINGOO_LEFT) val = val > 0 ? val-1 : 0;

    g_config->setOption("SDL.Tint", val);
}

// NTSC Hue
static void hue_update(unsigned long key)
{
    int val;
    g_config->getOption("SDL.Hue", &val);

    if (key & DINGOO_RIGHT) val = val < 255 ? val+1 : 255;
    if (key & DINGOO_LEFT) val = val > 0 ? val-1 : 0;

    g_config->setOption("SDL.Hue", val);
}

// Scanline start
static void slstart_update(unsigned long key)
{
    int val;
    g_config->getOption("SDL.ScanLineStart", &val);

    if (key & DINGOO_RIGHT) val = val < 239 ? val+1 : 239;
    if (key & DINGOO_LEFT) val = val > 0 ? val-1 : 0;

    g_config->setOption("SDL.ScanLineStart", val);
}

// Scanline end
static void slend_update(unsigned long key)
{
    int val;
    g_config->getOption("SDL.ScanLineEnd", &val);

    if (key & DINGOO_RIGHT) val = val < 239 ? val+1 : 239;
    if (key & DINGOO_LEFT) val = val > 0 ? val-1 : 0;

    g_config->setOption("SDL.ScanLineEnd", val);
}


/* VIDEO SETTINGS MENU */

static SettingEntry vd_menu[] = 
{
    {"Video scaling", "Select video scale mode", "SDL.Fullscreen", fullscreen_update},
	{"Blur filter", "Enable blur screen filter", "SDL.SpecialFilter", blur_update},
	{"Clip sides", "Clips left and right columns", "SDL.ClipSides", clip_update},
	
    {"NTSC Palette", "Emulate NTSC TV's colors", "SDL.NTSCpalette", ntsc_update},
	{"Tint", "Sets tint for NTSC color", "SDL.Tint", tint_update},
	{"Hue", "Sets hue for NTSC color", "SDL.Hue", hue_update},

	{"Scanline start", "The first drawn scanline", "SDL.ScanLineStart", slstart_update},
	{"Scanline end", "The last drawn scanline", "SDL.ScanLineEnd", slend_update},
};

int RunVideoSettings()
{
    static int index = 0;
    static int spy = 74;
    int done = 0, y, i;

    char tmp[32];
    int  itmp;

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
        		spy -= 15;
    	    }
    	}
   		if (parsekey(DINGOO_DOWN, 1)) {
    	    if (index < 7) {
    	        index++;
    	        spy += 15;
    	    }
    	}
    	if (parsekey(DINGOO_RIGHT, 1) || parsekey(DINGOO_LEFT, 1))
    	    vd_menu[index].update(g_key);
  
        // Draw stuff
        if( g_dirty ) 
        {
    	    draw_bg(vbuffer, g_bg);

       	    // Draw time and battery every minute
        	DrawText(vbuffer, g_time, 148, 5);
            DrawText(vbuffer, g_battery, 214, 5);	

            DrawChar(vbuffer, SP_VIDEO_SETTINGS, 40, 38); 
	
    	    // Draw menu
    	    for(i=0,y=70;i < 8;i++,y+=15) {
    	        DrawText(vbuffer, vd_menu[i].name, 60, y);
    	
                g_config->getOption(vd_menu[i].option, &itmp);
                if (!strncmp(vd_menu[i].name, "Video scaling", 5)) {
                    sprintf(tmp, "%s", scale_tag[itmp]);
                } 
                else sprintf(tmp, "%d", itmp);
    
	            DrawText(vbuffer, tmp, 224, y);
            }

	        // Draw info
    	    DrawText(vbuffer, vd_menu[index].info, 16, 225);

	        // Draw selector 
	        DrawChar(vbuffer, SP_SELECTOR, 44, spy);

            g_dirty = 0;
        }

        dingoo_timer_delay(16);
        
        // Update real screen
        memcpy(dingoo_screen15, vbuffer, 320*240*sizeof(unsigned short));
    }    

    g_dirty = 1;
    return 0;
}
