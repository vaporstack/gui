
//  gui_control_progress.c
//  gui_control_progress
//
//  Created by Andrew Macfarlane on 22/03/17.
//  Copyright © 2017 vaporstack. All rights reserved.

#include "gui_control_progress.h"

static void  cmp_update(GuiComponent* cmp)
{
	
}

static void   draw(GuiComponent* cmp)
{
	gui_component_draw(cmp);
}

static void layout(GuiComponent* cmp)
{
	printf("asdf\n");
}

static void setup_delegate(GuiComponent* cmp)
{

}

GuiComponent* gui_control_progress_create(Gui* gui, gui_progress_update_fn update, gui_progress_complete_fn complete)
{
	GuiComponent* cmp = gui_component_create(gui);
	GuiProgress* pb = calloc(1, sizeof(GuiProgress));
	pb->update = update;
	pb->complete = complete;
	cmp->draw = draw;
	cmp->layout = layout;
	cmp->update = cmp_update;
	setup_delegate(cmp);
	return cmp;
}

GuiComponent* gui_control_progress_create_raw(Gui* gui)
{
	return NULL;
}

void	  gui_control_progress_destroy(GuiComponent* comp)
{
	
}
