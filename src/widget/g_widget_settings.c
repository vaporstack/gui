//
//  g_widget_settings.c
//  gui
//
//  Created by Andrew Macfarlane on 8/22/17.
//  Copyright © 2017 ruminant. All rights reserved.
//

#include "g_widget_settings.h"

GuiComponent* g_widget_settings_create(void* gui)
{

	return gui_component_create(gui);
}

void g_widget_settings_destroy(GuiComponent* comp)
{
	free(comp);
}
