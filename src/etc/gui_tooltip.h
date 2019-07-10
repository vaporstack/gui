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
#include "../base/g_gui.h"

typedef struct GuiTooltip
{
	const char* name;
	const char* tip;
	GuiComponent* target;
} GuiTooltip;


GuiComponent* gui_tooltip_create(Gui* gui);
//void	  gui_tooltip_destroy(GuiComponent* comp);

#endif /* gui_tooltip_h */
