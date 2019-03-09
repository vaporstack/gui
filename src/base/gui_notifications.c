//
//  gui_notifications.c
//  gui
//
//  Created by Andrew Macfarlane on 4/12/17.
//  Copyright © 2017 ruminant. All rights reserved.
//

#include "gui_notifications.h"

#include <drw/drw.h>
#include <gui/src/base/g_gui.h>
#include <r4/r4.h>

static GuiComponent* notif_center = NULL;
static void	  update(GuiComponent* cmp)
{
}

static void draw(struct GuiComponent* comp, struct GuiComponent* gui)
{
}

GuiComponent* gui_notification_create(void* gui)
{
	return NULL;
}

GuiComponent* gui_notifications_create(void* gui)
{
	GuiComponent* g  = gui_component_create(gui);
	g->bounds.pos.x  = -512;
	g->bounds.pos.y  = -512 - 256;
	g->bounds.size.x = 256;
	g->bounds.size.y = 64;
	g->name		 = "alerts";
	g->update	= &update;
	g->draw		 = &draw;

	return g;
}

void gui_notifications_lazycheck(void* gui)
{

	if (!notif_center)
	{
		// l_notice( "auto creating notification center.\n");
		notif_center = gui_notifications_create(gui);
		gui_component_add(gui, notif_center);
	}
}
