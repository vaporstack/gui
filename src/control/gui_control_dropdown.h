//
//  gui_control_dropdown.h
//  gui
//
//  Created by vs on 3/20/19.
//  Copyright © 2019 ruminant. All rights reserved.
//

#ifndef gui_control_dropdown_h
#define gui_control_dropdown_h

#include "../base/gui_component.h"
#include "../base/g_gui.h"

typedef struct GDropdown
{
	signed num;
	char** fields;
}GDropdown;

GuiComponent* gui_control_dropdown_create(Gui* gui, const char** fields, unsigned num);


#endif /* gui_control_dropdown_h */
