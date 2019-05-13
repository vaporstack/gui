//
//  gui_ios_dpad_nav.c
//  gui
//
//  Created by vs on 5/13/19.
//  Copyright © 2019 ruminant. All rights reserved.
//

#include "gui_ios_dpad_nav.h"


static void begin(GuiComponent* cmp)
{
	cmp->interacting = true;
	//	if ( info->on_begin)
	//		info->on_begin(cmp, -1);
}

static void end(GuiComponent* cmp)
{
	
	cmp->interacting = false;
	r_input_delegate_pop();
}

static void touch_cancel(struct InputDelegate* del, double x, double y, double r, void* ptr)
{
	end(del->parent);
}

static void touch_began(struct InputDelegate* del, double x, double y, double r, void* ptr)
{
	begin(del->parent);
}

static void touch_move(struct InputDelegate* del, double x, double y, double r, void* ptr)
{
}

static void touch_ended(struct InputDelegate* del, double x, double y, double r, void* ptr)
{
	
	end(del->parent);
}

static void mouse_button(InputDelegate* del, int btn, int action, int mods)
{
}

static void mouse_motion(InputDelegate* del, double xEVer, double y)
{
}


static void setup_delegate(InputDelegate* del)
{
	del->mouse_button     = mouse_button;
	del->mouse_motion     = mouse_motion;
	del->touch_move       = touch_move;
	del->touch_began      = touch_began;
	del->touch_cancel     = touch_cancel;
	del->touch_ended      = touch_ended;
	//	del->tablet_down_rich = tablet_down_rich;
	//	del->tablet_up_rich   = tablet_up_rich;
	//	del->tablet_drag_rich = tablet_drag_rich;
	del->supports_handoff = false;
	del->name	     = "dpad nav";
	
}

GuiComponent* gui_ios_dpad_nav_create(Gui* gui)
{
	GuiComponent* cmp = gui_component_create(gui);
	setup_delegate(&cmp->delegate);
	
	return cmp;
	
}
