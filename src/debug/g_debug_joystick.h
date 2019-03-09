//
//  g_debug_joystick.h
//  gui
//
//  Created by vs on 11/29/17.
//  Copyright © 2017 ruminant. All rights reserved.
//

#ifndef g_debug_joystick_h
#define g_debug_joystick_h

#include "../base/gui_component.h"

GuiComponent* g_debug_joystick_create(void);
void	  g_debug_joystick_destroy(GuiComponent* comp);

#include <stdio.h>

#endif /* g_debug_joystick_h */
