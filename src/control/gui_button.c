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
	ButtonAttrs* attr = btn->data;
	if ( attr )
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
	if (btn->name && !btn->art)
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

GuiComponent* gui_button_create(void* gui, const char* label, click_func func)
{
	GuiComponent* cmp = gui_component_create(gui);

	cmp->name	 = label;
	ButtonAttrs* attr = malloc(sizeof(ButtonAttrs));
	//attr->value =
	attr->click = func;
	cmp->data   = attr;
	cmp->type   = GUI_TYPE_PUSHBUTTON;
	cmp->draw   = gui_button_draw;
	return cmp;
}
