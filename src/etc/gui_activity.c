//
//  gui_activity.c
//  gui
//
//  Created by vs on 11/12/17.
//  Copyright © 2017 ruminant. All rights reserved.
//

#include "gui_activity.h"

#include <r4/src/core/r_time.h>
#include <drw/drw.h>

extern AppSettings app_settings;
static void layout(GuiComponent* cmp)
{
	gui_component_set(cmp, -cmp->bounds.size.x, (app_settings.framebuffer_height * .5 ) - cmp->bounds.size.y);

}

static void draw(GuiComponent* cmp)
{
	gui_component_draw(cmp);
	double r = r_time_peek();
	
	drw_push();
	drw_translate2f(cmp->bounds.pos.x + cmp->bounds.size.x * .5, cmp->bounds.pos.y + cmp->bounds.size.y * .5);
	drw_axis_living();
	drw_pop();
}

GuiComponent* gui_activity_create(Gui* gui)
{
	GuiComponent* cmp = gui_component_create(gui);
	
	cmp->layout = layout;
	cmp->draw = draw;

	return cmp;
	
}
void	  gui_activity_destroy(GuiComponent* comp)
{
	
}
