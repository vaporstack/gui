
//  gui_modal.c
//  gui_modal
//
//  Created by Andrew Macfarlane on 18/03/17.
//  Copyright © 2017 vaporstack. All rights reserved.

#include "gui_modal.h"

#include <stdio.h>
#include <stdlib.h>

#include "../control/gui_button.h"
#include <gui/src/etc/gui_log.h> // entirely for gui_log oops

//	probably don't need these then huh
//#include "g_gui.h"
//#include "gui_component.h"

#include <r4/src/app/r_app.h>

#include <drw/drw.h>

//#include "../render/r_render.h"
//#include "../render/r_render.h"

extern AppSettings app_settings;
// extern double _gui_scale_retina;
// extern double _gui_w;
// extern double _gui_h;

static void draw(GuiComponent* cmp)
{
	// GuiComponent* comp = (GuiComponent*) data;

	gui_component_draw(cmp);

	GuiModalExtra* ext = (GuiModalExtra*)cmp->data;

	// printf
	//("0");
	// static float r = 0;
	// r += .1;

	// drw_rect_r(comp->bounds);
	// drw_color(1,0,1,1);

	drw_push();
	drw_rect(cmp->bounds.pos.x, cmp->bounds.pos.y,
		 cmp->bounds.pos.x + cmp->bounds.size.x,
		 cmp->bounds.pos.y + cmp->bounds.size.y);

	// drw_translate_vec2(&cmp->bounds.pos);
	drw_type_draw(ext->label);
	// drw_rotate_z(r);
	drw_pop();
}

static void update(struct GuiComponent* data)
{
	// printf(",");
}

void gui_modal_prompt(Gui* gui, const char* label, function_ptr ok,
		      function_ptr cancel)
{

	printf("Creating modal dialog.\n");
	r_app_show_cursor();

	GuiComponent* modal = gui_modal_create(gui);

	GuiModalExtra* extra = (GuiModalExtra*)modal->data;
	extra->cb_ok	 = &ok;
	extra->cb_cancel     = &cancel;
	extra->label	 = label;

	InputDelegate* cur	  = r_input_delegate_get();
	modal->data		    = extra;
	modal->delegate.holder      = cur;
	modal->delegate.name	= "modal delegate";
	modal->delegate.gui_element = modal;

	modal->name = "Friendly modal greeting";

	modal->bounds.size.x = app_settings.framebuffer_width * .5;
	modal->bounds.size.y = app_settings.framebuffer_height * .5;

	modal->bounds.pos.x = modal->bounds.size.x * -.5;
	modal->bounds.pos.y = modal->bounds.size.y * -.5;

	modal->container	= true;
	GuiComponent* okbtn     = gui_button_create(gui, "ok", ok);
	GuiComponent* cancelbtn = gui_button_create(gui, "cancel", cancel);
	okbtn->parent		= modal;
	cancelbtn->parent       = modal;
	//modal->alignment.h      = 0;
	//modal->alignment.v      = 0;
	//okbtn->alignment.h      = 1;
	//cancelbtn->alignment.h  = -1;
	gui_component_child_add(modal, okbtn);
	gui_component_child_add(modal, cancelbtn);

	//gui_component_layout(modal);

	modal->draw   = &draw;
	modal->update = &update;
	gui_component_add(gui, modal);
}

#include <gui/gui.h>

// static void mouse
static void click(struct InputDelegate* sender, int button, int action,
		  int mods)
{
	printf("Cliikkck %d %d %d\n", button, action, mods);
	printf("cursor is %f %f\n", app_settings.primary_cursor_x,
	       app_settings.primary_cursor_y);

	InputDelegate* del = (InputDelegate*)sender;

	GuiComponent* cmp = del->parent;

	GuiComponent* elem = gui_component_find_pointerfocus(
	    cmp, app_settings.primary_cursor_x, app_settings.primary_cursor_y);
	if (!elem)
	{
		gui_log("no!\n");
	}
	else
	{
		printf("elem: %s\n", elem->name);
		if (elem->type == GUI_TYPE_PUSHBUTTON)
		{
			if (button == 1)
				return;
			//todo I hate this
			ButtonAttrs* attr = (ButtonAttrs*)elem->data;
			if (attr->click)
				attr->click(NULL, *gui_cursor_x, *gui_cursor_y);
		}
	}
}
static void mouse_motion(struct InputDelegate* sender, double x,
			 double y)
{

	InputDelegate* del = (InputDelegate*)sender;
	GuiComponent*  par = del->parent;

	// printf("%p %s %f %f\n", sender, par->name, x, y);
	//GuiComponent* foc = gui_find_pointerfocus(gui, x, y);
	//if (foc)
	//	printf(" f : %s\n", foc->name);
}

static void key(struct InputDelegate* sender, int key, int scan, int action,
		int mods)
{
#ifndef RPLATFORM_IOS
	if (action == 1 && key == GLFW_KEY_ESCAPE)
	{
		printf("Dismissing modal!\n");
		r_input_delegate_pop();

		return;
	}

	printf("KEEYYYY %d %d %d %d\n", key, scan, action, mods);

#endif
}

GuiComponent* gui_modal_create(Gui* gui)
{
	GuiComponent* cmp	  = gui_component_create(gui);
	cmp->container		   = true;
	GuiModalExtra* extra       = malloc(sizeof(GuiModalExtra));
	cmp->data		   = extra;
	cmp->update		   = &update;
	cmp->draw		   = &draw;
	cmp->delegate.mouse_motion = &mouse_motion;
	cmp->delegate.mouse_button = &click;
	cmp->delegate.key	  = &key;
	cmp->delegate.name	 = "Modal input delegate";
	gui_component_add(gui, cmp);
	//r_input_delegate_push(&cmp->delegate);
	return cmp;
}

void gui_modal_destroy(GuiComponent* cmp)
{
	free(cmp);
}
