
//  gui_icon.c
//  gui_icon
//
//  Created by Andrew Macfarlane on 20/03/17.
//  Copyright © 2017 vaporstack. All rights reserved.

#ifndef gui_icon_h_
#define gui_icon_h_

#include "../base/gui_component.h"

GuiComponent* gui_icon_create(void* data);
void	  gui_icon_destroy(GuiComponent*);

#endif
