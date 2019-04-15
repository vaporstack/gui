//
//  gui_control_colorwell.c
//  gui
//
//  Created by vs on 6/18/17.
//  Copyright © 2017 ruminant. All rights reserved.
//

#include "gui_control_colorwell.h"

/*
static void update(GuiComponent* cmp) {}

static void draw(struct GuiComponent* comp, struct GuiComponent* gui)
{}

GuiComponent* gui_control_colorpicker_create()
{
	GuiComponent* cmp = malloc(sizeof(GuiComponent));
	cmp->update       = &update;
	cmp->draw	 = &draw;
	return cmp;
}

void gui_control_colorpicker_destroy(GuiComponent* picker) {}
*/


#include <drw/drw.h>


//#define COLORPICKER_SIZE 32
/*
 
 static void _click(struct InputDelegate *delegate, double x, double y, double
 foo) { printf("CLACK\n"); GuiComponent *cmp = delegate->parent; ColorPicker
 *pick = cmp->data; WColor *tar = pick->color;
 
 tar->a = r_rand_double(NULL);
 tar->g = r_rand_double(NULL);
 tar->b = r_rand_double(NULL);
 tar->r = r_rand_double(NULL);
 }
 */

//#define GUI_ARBITRARY_NUMBER_FOR_BUTTON_SIZE 32

static void _scroll(struct InputDelegate* delegate, double x, double y,
		    double z)
{
	
	printf("scroll: %f\n", x);
}
#include <gui/gui.h>

void gui_colorwell_draw(GuiComponent* cmp)
{
	
	ColorPicker* pik = (ColorPicker*)cmp->data;
	RColor16*    c   = pik->color;
	drw_color_push();
	drw_color(c->r, c->g, c->b, c->a * *gui_alpha_mult);
	drw_fill_set(true);
	drw_push();
	
	drw_translate2f(cmp->bounds.pos.x + cmp->bounds.size.x * .5, cmp->bounds.pos.y + cmp->bounds.size.y * .5);
	drw_circle_precision_set(32);
	
	//	this is horrible and I hate it but I'm in a hurry for results dammit
	double v = gui_default_ui(cmp->root) * PHI * .25;
	
	drw_circle(v);
	
	drw_fill_pop();
	drw_color_pop();
	
	drw_pop();
	return;
}

GuiComponent* gui_colorwell_create(void* gui, RColor16* color_ref, click_func onclick)
{
	GuiComponent* cmp  = gui_component_create(gui);
	ColorPicker*  pick = calloc(1, sizeof(ColorPicker));
	pick->color	= color_ref;
	
	cmp->data		 = pick;
	cmp->draw		 = gui_colorwell_draw;
	cmp->name		 = "gui_colorpicker";
	cmp->type = GUI_TYPE_PUSHBUTTON;
	cmp->delegate.touch_move = &_scroll;
	// cmp->delegate.click = &_click;
	if (onclick == NULL)
	{
		printf("Did not provide function\n");
		// cmp->delegate.tablet_down_rich = &_click;
		// cmp->delegate.touch_began = &_click;
		// cmp->activate = _click;
	}
	else
	{
		cmp->delegate.tablet_down_rich = onclick;
		cmp->delegate.touch_began      = onclick;
		cmp->delegate.mouse_button     = onclick;
		
		//cmp->activate		       = onclick;
	}
	return cmp;
}

void gui_colorwell_destroy(GuiComponent* cmp)
{
	free(cmp);
}
