
//  gui_settings.c
//  gui_settings
//
//  Created by Andrew Macfarlane on 29/06/17.
//  Copyright © 2017 vaporstack. All rights reserved.

#include "gui_settings.h"

GuiComponent* gui_settings_create(void* gui)
{
	GuiComponent* cmp = gui_component_create(gui);
	cmp->name	 = "gui settings";
	cmp->enabled      = false;
	cmp->visible      = false;
	cmp->container = true;
	return cmp;
}

void gui_settings_destroy(GuiComponent* cmp)
{
}
