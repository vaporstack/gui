
//  gui_checkbox.c
//  gui_checkbox
//
//  Created by Andrew Macfarlane on 23/04/17.
//  Copyright © 2017 vaporstack. All rights reserved.

#include "gui_control_checkbox.h"
#include <drw/drw.h>

static void move_cursor(GuiComponent* cmp, int pos);
static void update(GuiComponent* cmp);

static void toggle(GuiComponent* cmp)
{
	GCheckbox* info = cmp->data;
	if (!info->value)
	{
		printf("Can't toggle NULL data\n");
		return;
	}
	*(info->value) = !*(info->value);

	if (info->callback)
		info->callback(cmp);
}

static void start(GuiComponent* cmp)
{
}

static void end(GuiComponent* cmp)
{

	r_input_delegate_pop();
}

static void touch_cancel(struct InputDelegate* del, double x, double y, double r)
{

	end(del->parent);
}

static void touch_began(struct InputDelegate* del, double x, double y, double r)
{
}

static void touch_move(struct InputDelegate* del, double x, double y, double r)
{
}

static void touch_ended(struct InputDelegate* del, double x, double y, double r)
{
	GuiComponent* cmp = del->parent;
	if (r_rect_within(cmp->bounds, x, y))
	{
		toggle(cmp);
	}
	end(del->parent);
}

static void tablet_down_rich(struct InputDelegate* del, double x, double y, int button, double pressure, double rotation, double tilt_x, double tilt_y, double tangential)
{
	touch_began(del, x, y, -1);
}

static void tablet_up_rich(struct InputDelegate* del, double x, double y, int button, double pressure, double rotation, double tilt_x, double tilt_y, double tangential)
{
	touch_ended(del, x, y, -1);
}

static void tablet_drag_rich(struct InputDelegate* del, double x, double y, int button, double pressure, double rotation, double tilt_x, double tilt_y, double tangential)
{
	touch_move(del, x, y, -1);
}

static void draw(GuiComponent* cmp)
{
	//gui_component_draw(cmp);
	GCheckbox* info = cmp->data;
	drw_push();
	Gui* gui = cmp->root;
	
	double sz = gui_default_ui(gui);
	
	
	drw_translate(cmp->bounds.pos.x + sz * .5, cmp->bounds.pos.y + cmp->bounds.size.y * .5, 0);

	drw_square(cmp->bounds.size.y * .5);
	if (info->value)
	{
		if (*info->value)
		{
			drw_fill_set(*info->value);
			drw_square(cmp->bounds.size.y * .5 * PHI_I);
			drw_fill_pop();
		}
	}
	drw_translate(cmp->bounds.size.y * PHI_I, 0, 0);
	drw_type_draw(info->label);
	drw_pop();
}


static void mouse_button(InputDelegate* delegate, int button, int action, int mods)
{
	printf("%d %d %d\n", button, action, mods);
	if (button != 0)
		return;
	if (action != 0)
		return;

	GuiComponent* cmp = delegate->parent;
	toggle(cmp);
	end(cmp);
}

static void layout(GuiComponent* cmp )
{
	Gui* gui = cmp->root;
	
	double sz = gui_default_ui(gui);
	
	RRect par = cmp->parent->bounds;
	cmp->bounds.size.x = par.size.x - sz;
	
}

static void setup_delegate(InputDelegate* del)
{
	del->mouse_button = mouse_button;
	//del->mouse_motion = mouse_motion;
	del->touch_move       = touch_move;
	del->touch_began      = touch_began;
	del->touch_cancel     = touch_cancel;
	del->touch_ended      = touch_ended;
	del->tablet_down_rich = tablet_down_rich;
	del->tablet_up_rich   = tablet_up_rich;
	del->tablet_drag_rich = tablet_drag_rich;
	del->supports_handoff = true;
	//del->char_cb = charcb;
	//del->key = key;
	del->name = "a checkbox delegate";
}

GuiComponent* gui_control_checkbox_create(const char* label, bool* data, Gui* gui)
{

	GuiComponent* cmp  = gui_component_create(gui);
	GCheckbox*    info = calloc(1, sizeof(GCheckbox));
	cmp->name = "unnamed checkbox";
	
	info->label = label;
	info->value = data;
	cmp->data   = info;
	cmp->draw   = draw;
	cmp->layout = layout;
	
	setup_delegate(&cmp->delegate);
	return cmp;
}
