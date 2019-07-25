//
//  gui_control_encoder.c
//  gui
//
//  Created by vs on 7/25/19.
//  Copyright © 2019 ruminant. All rights reserved.
//

#include "gui_control_encoder.h"

#include <drw/drw.h>
#include <gui/gui.h>

static void draw(GuiComponent* cmp)
{
	
	gui_component_draw(cmp);
	drw_push();
	drw_translate2f(cmp->bounds.pos.x + cmp->bounds.size.y * .5, cmp->bounds.pos.y + cmp->bounds.size.y * .5);
	drw_circle(cmp->bounds.size.x * PHI_I * .5);
	drw_pop();
	
	
}

GuiComponent* gui_control_encoder_create(Gui* gui)
{
	GuiComponent* cmp = gui_component_create(gui);
	
	cmp->draw = draw;
	return cmp;
}
