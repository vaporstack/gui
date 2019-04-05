//
//  gui_notifications.c
//  gui
//
//  Created by Andrew Macfarlane on 4/12/17.
//  Copyright © 2017 ruminant. All rights reserved.
//

#include "gui_notifications.h"

#include "../anim/gui_anim_mgr.h"
#include "../control/gui_control_label.h"
#include "gui_notification.h"
#include <drw/drw.h>
#include <gui/src/base/g_gui.h>
#include <r4/r4.h>

/*
static GuiComponent* notif_center = NULL;
static void	  update(GuiComponent* cmp)
{
}

static void draw(struct GuiComponent* comp)
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
*/

static void update(GuiComponent* cmp)
{
	Gui*   g    = cmp->root;
	double sz   = gui_default_ui(g);
	double w    = g->root->bounds.size.x;
	double h    = g->root->bounds.size.y;
	double prev = 0;
	double x    = sz * -3;
	;
	double y = h * .5;
	y -= sz;
	double pad = sz * PHI_I * .5;
	y -= pad;
	//x += pad;
	for (unsigned i = 0; i < cmp->num_children; i++)
	{

		GuiComponent* child = cmp->children[i];

		GNotification* info = child->data;

		if (!info)
			continue;
		child->bounds.pos.x = x;
		child->bounds.pos.y = y;
		gui_component_set(info->sub, x, y);
		prev = child->bounds.size.y;
		y -= pad;
		y -= prev;
	}
}

static void draw(GuiComponent* cmp)
{
	for (unsigned i = 0; i < cmp->num_children; i++)
	{
		GuiComponent* child = cmp->children[i];
		(child->draw) ? child->draw(child) : gui_component_draw(child);
	}
}

GuiComponent* gui_notifications_create(Gui* gui)
{
	GuiComponent* cmp = gui_component_create(gui);
	cmp->container    = true;
	cmp->bypass       = true;
	//cmp->enabled = false;
	cmp->name   = "notification_center";
	cmp->draw   = draw;
	cmp->update = update;
	//cmp->bounds.pos.x = gui->root->bounds.size.x * -.5;
	//cmp->bounds.pos.y = gui->root->bounds.size.y * -.5;
	cmp->bounds.pos.x = cmp->bounds.pos.y = cmp->bounds.size.x = cmp->bounds.size.y = 0;
	//cmp->bounds.pos.y += 64;
	gui_component_child_add(gui->root, cmp);

	return cmp;
}

GuiComponent* gui_notifications_post(Gui* gui, const char* text)
{
	if (!gui->notifications)
		gui->notifications = gui_notifications_create(gui);

	GuiComponent* notif = gui_notification_create(gui, text);
	gui_component_child_add(gui->notifications, notif );
	return notif;
	
}

GuiComponent*  gui_notifications_post_custom(Gui* gui, GuiComponent* cmp)
{
	if (!gui->notifications)
		gui->notifications = gui_notifications_create(gui);

	GuiComponent* notif = gui_notification_create_custom(gui, cmp);
	gui_component_child_add(gui->notifications, notif );
	return notif;
}
