#ifndef FONT_H
#define FONT_H

enum {
    SP_SELECTOR = 95,
    SP_ROM,
    SP_SETTINGS,
    SP_NOPREVIEW,
    SP_LEFTARROW,
    SP_RIGHTARROW,
    SP_UPARROW,
    SP_DOWNARROW,
    SP_MAIN_SETTINGS,
    SP_VIDEO_SETTINGS,
    SP_SOUND_SETTINGS,
    SP_BROWSER
};


int InitFont();
void KillFont();
int DrawChar(unsigned short *dest, uint8 c, int x, int y);
void DrawText(unsigned short *dest, const char *textmsg, int x, int y);

#endif
