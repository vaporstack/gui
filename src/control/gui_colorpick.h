
//  gui_colorpick.c
//  gui_colorpick
//
//  Created by Andrew Macfarlane on 17/07/17.
//  Copyright © 2017 vaporstack. All rights reserved.

#ifndef gui_colorpick_h_
#define gui_colorpick_h_

#include <r4/src/core/r_color.h>

#include "../base/gui_component.h"

typedef struct
{
	int       type;
	int       model;
	double    gamma;
	RColor16* color;
} ColorPicker;

GuiComponent* gui_colorpick_create(void* gui, RColor16* color_ref,
				   click_func onclick);
void	  gui_colorpick_destroy(GuiComponent* cmp);

void gui_colorpick_draw(GuiComponent* cmp, GuiComponent* gui);

#endif
