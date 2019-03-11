//
//  gui_menu.c
//  gui
//
//  Created by Andrew Macfarlane on 9/18/17.
//  Copyright © 2017 ruminant. All rights reserved.
//

#include "gui_menu.h"
#include "../control/gui_button.h"
#include <gui/gui.h>
//#include <gui/gui_types.h>

#include <drw/drw.h>

#include <r4/r4.h>

//static GuiComponent* target = NULL;

static void key(struct InputDelegate* delegate, int key, int scan, int action,
		int mods)
{
#ifndef RPLATFORM_IOS

	GuiComponent* menu = delegate->gui_element;
	if (!menu)
	{
		gui_log("fuck!");
		return;
	}

	if (action == 1)
	{
		gui_log("return");
		return;
	}

	switch (key)
	{
	case GLFW_KEY_LEFT:
		gui_menu_select_prev(menu);
		break;
	case GLFW_KEY_UP:
		gui_menu_select_prev(menu);
		break;
	case GLFW_KEY_RIGHT:
		gui_menu_select_next(menu);
		break;
	case GLFW_KEY_DOWN:
		gui_menu_select_next(menu);
		break;
	case GLFW_KEY_ENTER:
		gui_menu_activate_selected(menu);
		break;
	case GLFW_KEY_SPACE:
		gui_menu_activate_selected(menu);
		break;
	default:
		break;
	}
	gui_log("menu %p got key %d %d %d %d", delegate, key, scan, action,
	       mods);
#endif
}

void gui_menu_activate_selected(GuiComponent* menu)
{
	GMenu* m_attr = (GMenu*)menu->data;

	GuiComponent* item = menu->children[m_attr->selected_item];
	if (!item)
	{
		gui_log("oh noes");
		return;
	}

	if (item->type == GUI_TYPE_PUSHBUTTON)
	{
		GuiComponent* target = item->target;
		if (!target)
		{
			gui_log("No target!");
			return;
		}
		ButtonAttrs* attr = (ButtonAttrs*)target->data;
		if (attr->click)
		{
			attr->click();
		}
	}
}

void gui_menu_select_prev(GuiComponent* menu)
{
	GMenu* attrs = (GMenu*)menu->data;
	attrs->selected_item--;
	if (attrs->selected_item < 0)
	{
		attrs->selected_item = menu->num_children - 1;
	}
	gui_log("current item is %d", attrs->selected_item);
	GuiComponent* target = menu->children[attrs->selected_item];
	gui_log("selected: %s", target->name);
}

void gui_menu_select_next(GuiComponent* menu)
{
	GMenu* attrs = (GMenu*)menu->data;
	attrs->selected_item++;
	if (attrs->selected_item >= menu->num_children)
	{
		attrs->selected_item = 0;
	}
	gui_log("current item is %d", attrs->selected_item);
	GuiComponent* target = menu->children[attrs->selected_item];
	gui_log("selected: %s", target->name);
}

static void mouse_motion(struct InputDelegate* del, double x, double y)
{
	// InputDelegate* del = (InputDelegate*)delegate;
	//del->cursor_x = x;
	//del->cursor_y = y;

	GuiComponent* target = gui_component_find_pointerfocus(del->parent, x, y);
	if (target)
	{
		//printf("found! %s\n", target->name);
	}
	// target = cmp;
}

static void mouse_button(struct InputDelegate* del, int button, int action,
			 int mods)
{
	//target = gui_component_findrw_pointerfocus(del->parent, del->cursor_x, del->cursor_y);

	GuiComponent* target = del->parent;

	if (!target)
	{
		gui_log("no target");
		return;
	}

	gui_log("%p:  %d %d %d", del, button, action, mods);

	//GuiComponent* target = NULL;// = target;

	if (target->type == GUI_TYPE_PUSHBUTTON)
	{
		ButtonAttrs* attr = (ButtonAttrs*)target->data;
		if (attr->click)
		{
			attr->click();
		}
	}
	else if (target->type == GUI_TYPE_MENU)
	{
		double x, y;
		r_app_cursor_get(&x, &y);

		GuiComponent* cmp = gui_component_find_pointerfocus(target, x, y);
		if (cmp)
		{
			ButtonAttrs* attr = (ButtonAttrs*)cmp->data;
			if (attr->click)
			{
				attr->click();
			}
		}
	}
}

static void draw(GuiComponent* cmp, GuiComponent* gui)
{
	gui_component_draw_bordered(cmp, gui);
	gui_component_draw(cmp, gui);
	GMenu* menu = (GMenu*)cmp->data;
	if ( !cmp->children )
	{
		l_warning("no children, can't draw menu");
		return;
	}
	
		
	GuiComponent* child = cmp->children[menu->selected_item];
	if (!child)
	{
		gui_log("bail");
		return;
	}
	drw_color(1, 0, 1, 1);

	// printf("Menu specific drawin\n");
}

// extern double _gui_scale_retina;
// extern double _gui_w;
// extern double _gui_h;

extern AppSettings app_settings;

GuiComponent* gui_menu_create_with_data(void* gui, GMenuCreationData data)
{
	GuiComponent* menu = gui_menu_create(gui);

	for (int i = 0; i < data.num; i++)
	{

		GuiComponent* btn =
		    gui_button_create(gui, data.names[i], data.funcs[i]);
		gui_component_child_add(menu, btn);
	}

	/*
	 GMenu* attr = calloc(1, sizeof(GMenu));
	attr->items = NULL;
	attr->selected_item = 0;
	menu->data = attr;
	*/
	//attr.parent = menu;
	menu->type = GUI_TYPE_MENU;
	return menu;
}

GuiComponent* gui_menu_create(void* gui)
{
	GuiComponent* cmp = gui_component_create(gui);

	//GuiAlignmentAttrs;
	//cmp->alig
	cmp->container = true;

	cmp->draw		   = draw;
	cmp->delegate.key	  = &key;
	cmp->delegate.mouse_motion = &mouse_motion;
	cmp->delegate.mouse_button = &mouse_button;
	cmp->delegate.parent       = cmp;
	GMenu* menu		   = calloc(1, sizeof(GMenu));
	menu->items		   = NULL;

	cmp->delegate.gui_element = cmp;
	// double sz = app_settings.framebuffer_height;
	// printf("sz is %f %f\n", sz);
	cmp->data		    = menu;
	cmp->name		    = "Unnamed menu";
	cmp->orientation.horizontal = GUI_H_ORIENTATION_FILL;
	cmp->orientation.vertical   = GUI_V_ORIENTATION_FILL;
	return cmp;
}

void gui_menu_destroy(GuiComponent* menu)
{
	if (menu->data)
		free(menu->data);
}
