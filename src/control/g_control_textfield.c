
//  g_control_textfield.c
//  g_control_textfield
//
//  Created by Andrew Macfarlane on 04/08/17.
//  Copyright © 2017 vaporstack. All rights reserved.

#include "g_control_textfield.h"


GuiComponent* g_control_textfield_create(void* gui)
{
	GuiComponent* cmp = gui_component_create(gui);
	
	GTextField* field = calloc(1, sizeof(GTextField));
	cmp->data = field;
	
	
	return cmp;
}
