
//  gui_checkbox.c
//  gui_checkbox
//
//  Created by Andrew Macfarlane on 23/04/17.
//  Copyright © 2017 vaporstack. All rights reserved.

#include "g_control_checkbox.h"
#include <drw/drw.h>


static void draw(GuiComponent* cmp, GuiComponent* gui)
{
	gui_component_draw(cmp, gui);
	GCheckbox* info = cmp->data;
	drw_push();
	drw_translate(cmp->bounds.pos.x + cmp->bounds.size.x * .5, cmp->bounds.pos.y + cmp->bounds.size.y * .5, 0);
	
	drw_fill_set(*info->value);
	drw_square(cmp->bounds.size.y * .5);
	drw_fill_pop();
	drw_type_draw(info->label);
	drw_pop();
}

static void mouse_button(InputDelegate* delegate, int button, int action, int mods)
{
	printf("%d %d %d\n", button, action, mods);
	if ( button != 0)
		return;
	if ( action != 0)
		return;
	
	GuiComponent* cmp = delegate->parent;
	GCheckbox* info = cmp->data;
	*(info->value) = !*(info->value);
}

GuiComponent* gui_control_checkbox_create(const char* label, bool* data, Gui* gui)
{
	
	GuiComponent* cmp = gui_component_create(gui);
	GCheckbox* info = calloc(1, sizeof(GCheckbox));
	
	info->label = label;
	info->value = data;
	cmp->data = info;
	cmp->draw = draw;
	cmp->delegate.mouse_button = mouse_button;
	return cmp;
}
