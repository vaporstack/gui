//
//  gui_control_dropdown.c
//  gui
//
//  Created by vs on 3/20/19.
//  Copyright © 2019 ruminant. All rights reserved.
//

#include "gui_control_dropdown.h"

#include <gui/gui.h>


#pragma mark centralized

static void update(GuiComponent* cmp, double x, double y)
{
	printf("dropdown UPDATE\n");
	
}




static void start(GuiComponent* cmp)
{
	cmp->interacting = true;
	
}

static void end(GuiComponent* cmp)
{
	
	cmp->interacting = false;
	r_input_delegate_pop();
}

static void touch_cancel(struct InputDelegate* del, double x, double y)
{
	end(del->parent);
}

static void touch_began(struct InputDelegate* del, double x, double y)
{
	update(del->parent, x, y);
}

static void touch_move(struct InputDelegate* del, double x, double y)
{
	update(del->parent, x, y);
}

static void touch_ended(struct InputDelegate* del, double x, double y)
{
	update(del->parent, x, y);
	end(del->parent);
}

static void tablet_down_rich(struct InputDelegate* del, double x, double y, int button, double pressure, double rotation, double tilt_x, double tilt_y, double tangential)
{
	touch_began(del->parent, x, y);
}

static void tablet_up_rich(struct InputDelegate* del, double x, double y, int button, double pressure, double rotation, double tilt_x, double tilt_y, double tangential)
{
	touch_ended(del->parent, x, y);
}

static void tablet_drag_rich(struct InputDelegate* del, double x, double y, int button, double pressure, double rotation, double tilt_x, double tilt_y, double tangential)
{
	
	touch_move(del->parent, x, y);
}

static void mouse_button(InputDelegate* del, int btn, int action, int mods)
{
	if (btn > 0)
		return;
	
	if (action == 1)
	{
		update(del->parent, *gui_cursor_x, *gui_cursor_y);
	}
	else
	{
		end(del->parent);
		//do_slider(del, app_settings, <#double y#>, <#double r#>)
	}
}

static void mouse_motion(InputDelegate* del, double x, double y)
{
	update(del->parent, x, y);
}

static int click(GuiComponent* cmp, double d)
{
	
	GuiSliderD* attr   = cmp->data;
	double*     target = attr->target;
	if (!d)
	{
		printf("Can't set, no data!\n");
		return 7;
	}
	*target = d;
	
	return 0;
}

static void layout(struct GuiComponent* cmp)
{
	
	GuiComponent* gui = cmp->parent;
	
	double w = gui->bounds.size.x;
	double h = gui->bounds.size.y;
	
	GuiSliderD* info = cmp->data;
	
	double sz = gui_default_ui(cmp->root);
	double sw, sh;
	if (info->vertical)
	{
		
		sw = sz;
		sh = sz * 3;
	}
	else
	{
		sw = sz * 3;
		sh = sz;
	}
	
	//cmp->bounds.size.x = sw;
	//..cmp->bounds.size.y = sh;
	
	gui_component_size(cmp, sw, sh);
	double x = 0;
	double y = (h * -.5); // + cmp->bounds.size.y;
	
	switch (cmp->orientation.horizontal)
	{
		case -1:
			x = w * -.5;
			break;
		case 0:
			x = 0;
			break;
		case 1:
			x = w * .5 - cmp->bounds.size.x;
			break;
			
		default:
			break;
	}
	x += cmp->offset.x;
	y += cmp->offset.y;
	gui_component_set(cmp, x, y);
}

static void destroy(GuiComponent* cmp)
{
	GuiSliderD* info = cmp->data;
	free(info);
}



static void setup_delegate(InputDelegate* del)
{
	del->mouse_button     = mouse_button;
	del->mouse_motion     = mouse_motion;
	del->touch_move       = touch_move;
	del->touch_began      = touch_began;
	del->touch_cancel     = touch_cancel;
	del->touch_ended      = touch_ended;
	del->tablet_down_rich = tablet_down_rich;
	del->tablet_up_rich   = tablet_up_rich;
	del->tablet_drag_rich = tablet_drag_rich;
	del->supports_handoff = true;
	del->name	     = "a slider delegate";
}


static void draw(GuiComponent* cmp)
{
}

GuiComponent* gui_control_dropdown_create(Gui* gui, const char** fields, unsigned num)
{
	GuiComponent* cmp = gui_component_create(gui);
	cmp->draw	 = draw;
	
	setup_delegate(&cmp->delegate);
	
	return cmp;
}
