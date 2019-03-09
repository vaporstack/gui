//
//  gui_tooltip.h
//  gui
//
//  Created by vs on 11/12/17.
//  Copyright © 2017 ruminant. All rights reserved.
//

#ifndef gui_tooltip_h
#define gui_tooltip_h

#include "../base/gui_component.h"

typedef struct GuiTooltip
{
	const char* name;
	const char* tip;
} GuiTooltip;

GuiComponent* gui_tooltip_create(void);
void	  gui_tooltip_destroy(GuiComponent* comp);

#endif /* gui_tooltip_h */
