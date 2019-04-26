
//  gui_panel.c
//  gui_panel
//
//  Created by Andrew Macfarlane on 04/08/17.
//  Copyright © 2017 vaporstack. All rights reserved.

#include "gui_panel.h"
#include <drw/drw.h>

#pragma mark logic

static void begin(GuiComponent* cmp, double x, double y)
{
}

static void update(GuiComponent* cmp, double x, double y)
{
}

static void end(GuiComponent* cmp, double x, double y)
{
}

static void draw_panel(GuiComponent* cmp)
{

	double		 u = gui_ui_unit;
	//double		 w = cmp->bounds.size.x;
	GTabbedPanelTab* t = cmp->data;

	GuiComponent* par   = cmp->parent;
	GTabbedPanel* pal   = par->data;
	
	int num = pal->num;
	int idx = t->idx;
	
	double x = cmp->bounds.pos.x;
	double y = cmp->bounds.pos.y;
	double w = cmp->bounds.size.x;
	double h = cmp->bounds.size.y;
	
	double sx = w / num;
	double left = sx * idx;
	double right = sx * idx + 1;
	
	/*
	 
	 drw_fill_set(true);
	drw_color_c16(r_app_color_get_fm());
	drw_alpha(.125);
	
	//drw_rect(x, y, w, h);
	//drw_rect(x + left, y + h, sx, u * .5);
	
	drw_fill_pop();
	drw_color_pop();
	drw_alpha_pop();
	
	*/
	
	drw_push();
	drw_translate(x + left + sx * .5, y + h + u * -.5, 0);
	drw_alpha(1);
	char* text = pal->tabs[idx]->src;
	drw_alpha_pop();
	drw_type_set_align(DRW_TYPE_ALIGN_H_CENTER, DRW_TYPE_ALIGN_V_CENTER);
	drw_type_draw(text);
	drw_pop();
	/*int	   idx   = t->idx;
	 
	double	xw    = w / pal->num;
	double	left  = idx * xw;
	double	right = 1 + idx * xw;
	double	h     = par->bounds.size.y - par->bounds.pos.y;
	double	ay    = cmp->bounds.pos.y;
	double	by    = h - u * .5;
	double	x     = cmp->bounds.pos.x;
	double	y     = cmp->bounds.pos.y;
	/*
	 if (!t->geo)
	{
		RLine* line = r_line_create();

		r_line_add_point2f(line, x, ay);
		r_line_add_point2f(line, x, by);
		r_line_add_point2f(line, x + left, by);
		r_line_add_point2f(line, x + left, h);
		r_line_add_point2f(line, x + right, h);
		r_line_add_point2f(line, x + right, by);
		r_line_add_point2f(line, x + w, by);
		r_line_add_point2f(line, x + w, ay);
		line->closed = true;
		t->geo       = line;
	}
	 
	
	drw_fill_set(true);
	drw_color_c16(r_app_color_get_fm());
	drw_alpha(.125);
	drw_rect(x, y, w, by);
	drw_rect(x + left, by, xw, u * .5);
	
	//drw_rline(t->geo);
	drw_color_pop();
	drw_fill_pop();
	drw_alpha_pop();
	drw_rect(x, y, w, by);
	drw_rect(x + left, by, xw, u * .5);
	//drw_rline(t->geo);
	 */
}

static void draw(GuiComponent* cmp)
{

	//gui_component_draw(cmp);

	drw_fill_set(true);
	drw_color_c16(r_app_color_get_bg());
	drw_alpha(.75);
	drw_rect(cmp->bounds.pos.x, cmp->bounds.pos.y, cmp->bounds.size.x, cmp->bounds.size.y);
	
	drw_alpha_pop();
	drw_fill_pop();
	drw_color_pop();
	drw_rect(cmp->bounds.pos.x, cmp->bounds.pos.y, cmp->bounds.size.x, cmp->bounds.size.y);
	
	//gui_component_draw(cmp);
	GTabbedPanel* pal = cmp->data;
	for (int i = 0; i < cmp->num_children; i++)
	{
		if ( i != pal->cur )
			cmp->children[i]->draw(cmp->children[i]);
		//	draw_panel(cmp, pal, i);
	}
	cmp->children[pal->cur]->draw(cmp->children[pal->cur]);
	
	/*
	for ( int i = 0; i < pal->num; i++ )
	{
		if ( i != pal->cur )
		{
			draw_panel(cmp, pal);
		}
	}
	*/
}

static void layout(GuiComponent* cmp)
{
	double w = *gui_fb_w;
	double h = *gui_fb_h;
	
	double sz = gui_ui_unit;
	gui_component_size(cmp, w * .5, h * .5);
	gui_component_set(cmp, w * -.25, h * -.25);
	gui_component_size(cmp, sz * 5, sz * 5);
	for (int i = 0; i < cmp->num_children; i++)
	{
		GuiComponent* ch = cmp->children[i];
		gui_component_size(ch, cmp->bounds.size.x, cmp->bounds.size.y);
		gui_component_set(ch, cmp->bounds.pos.x, cmp->bounds.pos.y);
		GTabbedPanelTab* t = ch->data;
		//r_line_destroy(t->geo);
		//t->geo = NULL;
	}
}

#pragma mark input

#pragma mark desktop

static void mouse_motion(struct InputDelegate* delegate, double x, double y)
{
}

static void mouse_button(struct InputDelegate* delegate, int button, int action,
			 int mods)
{
}

static void key(struct InputDelegate* delegate, int key, int scan, int action, int mods)
{
}

static void char_cb(struct InputDelegate* delegate, unsigned c)
{
}

#pragma mark touch

static void touch_cancel(struct InputDelegate* delegate, double x, double y, double r)
{
}

static void touch_began(struct InputDelegate* delegate, double x, double y, double r)
{
}

static void touch_ended(struct InputDelegate* delegate, double x, double y, double r)
{
}

static void touch_move(struct InputDelegate* delegate, double x, double y,
		       double r)
{
}

#pragma mark tablet

static void tablet_proximity(bool v)
{
}

static void tablet_motion_rich(struct InputDelegate* delegate, double x,
			       double y, int button, double pressure,
			       double rotation, double tilt_x, double tilt_y,
			       double tangential)
{
}

static void tablet_drag_rich(struct InputDelegate* delegate, double x, double y,
			     int button, double pressure, double rotation,
			     double tilt_x, double tilt_y, double tangential)
{
}

static void tablet_down_rich(struct InputDelegate* delegate, double x, double y,
			     int button, double pressure, double rotation,
			     double tilt_x, double tilt_y, double tangential)
{
}

static void tablet_up_rich(struct InputDelegate* delegate, double x, double y,
			   int button, double pressure, double rotation,
			   double tilt_x, double tilt_y, double tangential)
{
}

#pragma mark core

static void setup_delegate(InputDelegate* del)
{
	del->mouse_button       = mouse_button;
	del->mouse_motion       = mouse_motion;
	del->touch_move		= touch_move;
	del->touch_began	= touch_began;
	del->touch_cancel       = touch_cancel;
	del->touch_ended	= touch_ended;
	del->tablet_motion_rich = tablet_motion_rich;
	del->tablet_proximity   = tablet_proximity;
	del->tablet_down_rich   = tablet_down_rich;
	del->tablet_up_rich     = tablet_up_rich;
	del->tablet_drag_rich   = tablet_drag_rich;
	//del->supports_handoff   = true;
	del->char_cb = char_cb;
	del->key     = key;
	del->name    = "a manipulator delegate";
}

GuiComponent* gui_tabbed_panel_create(Gui* gui, char** labels, int num)
{

	GuiComponent* cmp = gui_component_create(gui);
	cmp->draw	 = draw;
	cmp->layout       = layout;
	setup_delegate(&cmp->delegate);
	GTabbedPanel* info = calloc(1, sizeof(GTabbedPanel));
	info->tabs	 = calloc(num, sizeof(GuiStringHandle));
	info->num	  = num;
	info->cur	  = 0;
	for (int i = 0; i < num; i++)
	{
		info->tabs[i]      = malloc(sizeof(GuiStringHandle));
		info->tabs[i]->src = labels[i];
		printf("created tab: %s\n", labels[i]);
		GuiComponent*    tab = gui_component_create(gui);
		GTabbedPanelTab* t   = malloc(sizeof(GTabbedPanelTab));
		t->idx		     = i;
		t->geo		     = NULL;
		tab->data	    = t;
		tab->draw	    = draw_panel;
		gui_component_child_add(cmp, tab);
	}
	cmp->data = info;

	return cmp;
}
