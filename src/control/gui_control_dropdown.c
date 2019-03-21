//
//  gui_control_dropdown.c
//  gui
//
//  Created by vs on 3/20/19.
//  Copyright © 2019 ruminant. All rights reserved.
//

#include "gui_control_dropdown.h"

static void draw(GuiComponent* cmp, GuiComponent* gui)
{
	
}

GuiComponent* gui_control_dropdown_create(Gui* gui, const char** fields, unsigned num)
{
	GuiComponent* cmp = gui_component_create(gui);
	cmp->draw = draw;
	
	return cmp;
}
