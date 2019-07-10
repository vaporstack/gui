//
//  gui_tooltip.c
//  gui
//
//  Created by vs on 11/12/17.
//  Copyright © 2017 ruminant. All rights reserved.
//

#include "gui_tooltip.h"

static void destroy(GuiComponent* cmp)
{
	GuiTooltip* info = cmp->data;
	free(info);
}

GuiComponent* gui_tooltip_create(Gui* gui)
{
	GuiComponent* cmp = gui_component_create(gui);
	GuiTooltip* info = calloc(1, sizeof(GuiTooltip));
	cmp->data = info;
	cmp->destroy = destroy;
	return cmp;
}

//void	  gui_tooltip_destroy(GuiComponent* comp)
//{
//
//}
