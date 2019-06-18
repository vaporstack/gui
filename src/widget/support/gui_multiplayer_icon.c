//
//  gui_widget_multiplayer_icon.c
//  gui
//
//  Created by vs on 5/13/19.
//  Copyright © 2019 ruminant. All rights reserved.
//

#include "gui_multiplayer_icon.h"


static void begin(GuiComponent* cmp, double x, double y)
{
	
	
}

static void update(GuiComponent* cmp, double x, double y)
{
	
}


static void end(GuiComponent* cmp, double x, double y)
{
	
	
	//printf("EEEEEEEND\n");
	r_input_delegate_pop();
}

static void draw(GuiComponent* cmp)
{
	
}

static void layout(GuiComponent* cmp)
{
	
}

#pragma mark input

#pragma mark desktop

static void mouse_motion(struct InputDelegate* delegate, double x, double y)
{
}

static void mouse_button(struct InputDelegate* delegate, int button, int action,
			 int mods)
{
	if ( button > 0)
		return;
	
	//	click
	if ( action == 1 )
	{
		//begin(delegate->parent, app_settings.framebuffer_width, app_settings.framebuffer_height);
	}else{
		
		//end(delegate->parent, app_settings.framebuffer_width, app_settings.framebuffer_height);
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
	del->name		= "a multiplayer session control delegate";
}

GuiComponent* control_multiplayer_session_create(Gui* gui)
{
	GuiComponent* cmp = gui_component_create(gui);
	
	setup_delegate(&cmp->delegate);
	//todo fillll this out
	
	return cmp;
	
}
