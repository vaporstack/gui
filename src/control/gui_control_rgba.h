//
//  gui_control_rgba.h
//  gui
//
//  Created by vs on 3/24/19.
//  Copyright © 2019 ruminant. All rights reserved.
//

#ifndef gui_control_rgba_h
#define gui_control_rgba_h

#include "../base/gui_component.h"
#include "../base/g_gui.h"
#include <r4/src/core/r_color.h>

typedef struct
{
	
	char* hexfield;
	RColor16* color_ptr;
}GRGBAAdjustor;

GuiComponent* gui_control_rgba_create(Gui* gui, WColor16* color);


#endif /* gui_control_rgba_h */
