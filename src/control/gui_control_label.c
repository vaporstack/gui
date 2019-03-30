
//  gui_label.c
//  gui_label
//
//  Created by Andrew Macfarlane on 04/08/17.
//  Copyright © 2017 vaporstack. All rights reserved.

#include "gui_control_label.h"

#include <drw/drw.h>

static void draw(GuiComponent* cmp)
{
	Gui*   g  = cmp->root;
	double sz = gui_default_ui(g);
	drw_push();
	drw_translate2f(cmp->bounds.pos.x, cmp->bounds.pos.y);
	gui_component_draw(cmp);
	GLabel* info = cmp->data;
	drw_type_set_align(DRW_TYPE_ALIGN_H_RIGHT, DRW_TYPE_ALIGN_V_CENTER);
	//drw_push();
	drw_translate(sz * .5, sz * .5, 0);
	drw_type_draw(info->text);
	drw_pop();
}

static void destroy(GuiComponent* cmp)
{
	GLabel* label = cmp->data;
	free(label);
}

static void click(InputDelegate* del, int button, int action, int mods)
{
	printf("%d %d %d\n", button, action, mods);
}

GuiComponent* gui_control_label_create(Gui* gui, const char* label)
{

	GuiComponent* cmp  = gui_component_create(gui);
	GLabel*       info = calloc(1, sizeof(GLabel));
	double	sz   = gui_default_ui(gui);
	gui_component_size(cmp, sz * 4, sz);
	info->text		   = label;
	cmp->name		   = "label";
	cmp->data		   = info;
	cmp->draw		   = draw;
	cmp->destroy		   = destroy;
	cmp->delegate.mouse_button = click;
	return cmp;
}
