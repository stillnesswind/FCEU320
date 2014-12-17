/* FCE Ultra - NES/Famicom Emulator
 *
 * Copyright notice for this file:
 *  Copyright (C) 2002 Xodnizel
 *  Copyright (C) 2002 Paul Kuliniewicz
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
/// \brief Handles joystick input using the SDL.

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

#include "dingoo.h"

unsigned long dingoo_key = 0;

/**
 * Tests if the given button is active on the joystick.
 */
int
DTestButtonJoy(ButtConfig *bc)
{
    int x;

    for(x = 0; x < bc->NumC; x++)
    {
        if( dingoo_key & (1<<bc->ButtonNum[x]) )
            return(1);
    }
    return(0);
}

/**
 * Shutdown the DINGOO joystick subsystem.
 */
int
KillJoysticks()
{
    return(0);
}

/**
 * Initialize the DINGOO joystick subsystem.
 */
int
InitJoysticks()
{
    return(1);
}
