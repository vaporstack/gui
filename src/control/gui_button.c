//
//  gui_button.c
//  r4
//
//  Created by Andrew Macfarlane on 1/7/17.
//  Copyright © 2017 vaporstack. All rights reserved.
//

#include "gui_button.h"

#include <stdlib.h>

#include <drw/drw.h>
#include <gui/gui_types.h>

static void gui_button_draw(GuiComponent* btn)
{
	gui_component_draw(btn);
	drw_push();
	drw_translate(btn->bounds.pos.x, btn->bounds.pos.y, 0);
	drw_translate(btn->bounds.size.x * .5, btn->bounds.size.y * .5, 0);
	ButtonAttrs* attr = btn->attr;
	if (attr)
	{
		/*if ( attr->value )
		{
			if ( !*attr->value)
			{
				drw_alpha(.5);
			}else{
				drw_alpha(1.);
			}
		}*/
	}
	if ( btn->art2 )
	{
		drw_robject(btn->art2);
		return;
		
	}
	if ( btn->art )
	{
		drw_wobject(btn->art);
		return;
	}
	if (btn->name && !btn->art && !btn->art2)
		drw_type_draw(btn->name);
	drw_pop();

	//	this is strange, I wonder what it did, and why
	//
	//	if ( attr )
	//	{
	//		if ( attr->value)
	//			drw_alpha_pop();
	//	}
}

static bool find_focus(GuiComponent* cmp, double x, double y)
{
	return ( x >= cmp->bounds.pos.x && y >= cmp->bounds.pos.y && x <= cmp->bounds.pos.x + cmp->bounds.size.x && y <= cmp->bounds.pos.y + cmp->bounds.size.y );
}

GuiComponent* gui_button_create(void* gui, const char* label, click_func func)
{
	GuiComponent* cmp = gui_component_create(gui);
	
	cmp->name	 = label;
	ButtonAttrs* attr = malloc(sizeof(ButtonAttrs));
	//attr->value =
	attr->click = func;
	cmp->find_focus = find_focus;
	cmp->attr   = attr;
	cmp->type   = GUI_TYPE_PUSHBUTTON;
	//cmp->draw   = gui_button_draw;
	return cmp;
}
