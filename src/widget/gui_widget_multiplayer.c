//
//  gui_widget_multiplayer.c
//  gui
//
//  Created by vs on 5/13/19.
//  Copyright © 2019 ruminant. All rights reserved.
//

#include "gui_widget_multiplayer.h"

#include <drw/drw.h>
#include <gui/gui.h>

static void begin(GuiComponent* cmp, double x, double y)
{
	cmp->delegate.holder = r_input_delegate_get();
	printf("CLICK?");
}

static void end(GuiComponent* cmp, double x, double y)
{
	r_input_delegate_pop();
}

void click(void* cmp, double x, double y)
{

	printf("HIIII\n");
}

static void update(GuiComponent* cmp)
{
}

static void draw(GuiComponent* cmp)
{
	//drw_line(cmp->)
	drw_push();
	//	drw_translate(cmp->bounds.pos.x + cmp->bounds.size.x * .5, cmp->bounds.pos.y + cmp->bounds.size.y * .5, 0);
	//drw_translate(cmp->bounds.pos.x, cmp->bounds.pos.y, 0);
	drw_translate(cmp->bounds.pos.x + cmp->bounds.size.x * .5, cmp->bounds.pos.y + cmp->bounds.size.y * .5, 0);

	drw_circle(cmp->bounds.size.x * .5);
	/*double subsize = cmp->bounds.size.x * .333;
	 WashMultiplayerWidget* inf = cmp->data;

	 */

	drw_pop();
	for (int i = 0; i < cmp->num_children; i++) {
		GuiComponent* ch = cmp->children[i];
		drw_line(cmp->bounds.pos.x, cmp->bounds.pos.y, ch->bounds.pos.x, ch->bounds.pos.y);
		//WashRemoteSessionInfo* session = inf->sessions[i];
		//draw_session(session, 0, subsize * i, subsize);
	}

	gui_component_draw_children(cmp);
}
static bool within(GuiComponent* cmp, double x, double y)
{

	return true;
}

static void layout(GuiComponent* cmp)
{
	double sz = gui_ui_unit;
	//cmp->bounds.size.x = cmp->bounds.size.y = sz * 3;
	double w = *gui_fb_w;
	double h = *gui_fb_h;
	gui_component_size(cmp, sz * 2, sz * 2);
	gui_component_set(cmp, 0, 0);
	//gui_component_set(cmp, sz * 2 * -.5, sz * 2 * -.5);
	//gui_component_set(cmp, w * -.25, h * -.333 + sz * 1);
	for (unsigned int i = 0; i < cmp->num_children; i++) {
		GuiComponent* child = cmp->children[i];
		gui_component_set(child, 0, 0);
		//	gui_component_set(child, cmp->bounds.pos.x + cmp->bounds.size.x * .5, cmp->bounds.pos.y + cmp->bounds.size.y);
	}
	//	if ( cmp->num_children == 0 )
	//		return;
	//	if ( cmp->num_children == 1 )
	//	{
	//		GuiComponent* child = cmp->children[0];
	//		gui_component_size( child, sz, sz );
	//	//gui_component_set( child, child->bounds.pos.x + sz * 1, child->bounds.pos.y + sz * 1);
	//	//	gui_component_set( child, cmp->bounds.pos.x * .3333, cmp->bounds.pos.y * .3333);
	//	//	gui_component_set( child, cmp->bounds.pos.x * cmp->bounds.size.x * .5, cmp->bounds.pos.y * cmp->bounds.size.x * .5);
	//		gui_component_set( child, cmp->bounds.pos.x , cmp->bounds.pos.y );
	//		gui_component_set(child, w * -.25, h * -.333 + sz * 1);
	//
	//		return;
	//	}
	//
	//	for ( int i = 0; i < cmp->num_children; i++ )
	//	{
	//		GuiComponent* ch = cmp->children[i];
	//		double u = 1;//+ (int)(i/3);
	//		double m = fmod(i, 3);
	//
	//		double rad = u * sz *.33333;
	//		double x = cos(m * M_PI) * rad;
	//		double y = sin(m * M_PI) * rad;
	//
	////		gui_component_set(ch, (cmp->bounds.pos.x + sz * -.5 ) + x, (cmp->bounds.pos.y + sz * -.5) + y );
	//		gui_component_set(ch, (cmp->bounds.pos.x + cmp->bounds.size.x * .5) + x, (cmp->bounds.pos.y + cmp->bounds.size.y * .5) + y );
	//	}
	//

	//double r = (cmp->num_children > 0 ) 0 : cmp->sz * 1.5;
}

#pragma mark input

#pragma mark desktop

static void mouse_motion(struct InputDelegate* delegate, double x, double y)
{
}

static void mouse_button(struct InputDelegate* delegate, int button, int action,
			 int mods)
{
	if (button > 0)
		return;

	if (action == 0) {
		begin(delegate->parent, -1, -1);
	} else {
		end(delegate->parent, -1, -1);
	}
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
	end(delegate->parent, x, y);
}

static void touch_began(struct InputDelegate* delegate, double x, double y, double r)
{
	begin(delegate->parent, x, y);
}

static void touch_ended(struct InputDelegate* delegate, double x, double y, double r)
{
	end(delegate->parent, x, y);
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
	touch_began(delegate, x, y, -1);
}

static void tablet_up_rich(struct InputDelegate* delegate, double x, double y,
			   int button, double pressure, double rotation,
			   double tilt_x, double tilt_y, double tangential)
{
	touch_ended(delegate, x, y, -1);
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
	del->supports_handoff   = true;
	del->char_cb		= char_cb;
	del->key		= key;
	del->name		= "multiplayer delegate";
}

GuiComponent* wash_widget_multiplayer_create(Gui* gui)
{
	GuiComponent* cmp = gui_component_create(gui);
	cmp->update       = update;
	cmp->draw	 = draw;
	cmp->layout       = layout;
	setup_delegate(&cmp->delegate);
	//cmp->find_focus = within;

	//	WashMultiplayerWidget* info = calloc( 1, sizeof(WashMultiplayerWidget));
	//	info->num = wash_multiplayer_getnpointer();
	//	info->sessions = wash_multiplayer_getinfo(NULL);
	//cmp->data = info;
	cmp->name      = "multiplayer widget";
	cmp->nice_name = "Multiplayer Widget";

	return cmp;
}
