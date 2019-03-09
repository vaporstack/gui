
//  gui_aviewer.c
//  gui_aviewer
//
//  Created by Andrew Macfarlane on 19/03/17.
//  Copyright © 2017 vaporstack. All rights reserved.

#include "gui_aviewer.h"

#include <stdio.h>
#include <stdlib.h>

#include <r4/r4.h>
//#include <wsh/wsh.h>
//#include "gui_component.h"

#include <drw/drw.h>
//#include <gui.h>

static void draw(struct GuiComponent* comp, struct GuiComponent* gui)
{
	/*
	//GuiComponent* cmp = (GuiComponent*)data;
	WObject* obj = cmp->target;

	//r_rect_r(cmp->bounds);

	drw_rect(cmp->bounds.pos.x, cmp->bounds.pos.y, cmp->bounds.pos.x +
	cmp->bounds.size.x, cmp->bounds.pos.y + cmp->bounds.size.y); if ( obj )
	{
		drw_push();
		//printf("obj: %p\n", obj);

		drw_translate_x(64);
		drw_wobject(obj);


		drw_pop();

		WObject* copy = wsh_object_copy(obj);
		wsh_object_normalize(copy);
		drw_wobject(copy);
		drw_rect_w(copy->bounds);
		//leaking
		wsh_object_destroy(copy);
	}
	*/
}

static void update(struct GuiComponent* data)
{
}

GuiComponent* gui_aviewer_create(void* gui)
{
	GuiComponent* cmp  = gui_component_create(gui);
	cmp->draw	  = &draw;
	cmp->update	= &update;
	cmp->bounds.pos.x  = 0;
	cmp->bounds.pos.y  = 0;
	cmp->bounds.size.x = 200;
	cmp->bounds.size.y = 400;
	cmp->target	= NULL;

	return cmp;
}

void gui_aviewer_destroy(GuiComponent* cmp)
{
	free(cmp);
}
