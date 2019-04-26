//
//  gui_control_colorwell.h
//  gui
//
//  Created by vs on 6/18/17.
//  Copyright © 2017 ruminant. All rights reserved.
//

#ifndef gui_control_colorpicker_h
#define gui_control_colorpicker_h

#include <gui/gui.h>

//	modes are ?
/*
	0 - 1channel luma
	1 - 3channel rgb
	2 - 3channel hsv
	3 - 3channel cmyk
 */

/*
typedef enum {
	G_CONTROL_COLORPICKER_MODE_NONE,
	G_CONTROL_COLORPICKER_MODE_LUMA
} ColorPickerModes;

typedef enum {
	G_CONTROL_COLORPICKER_DEPTH_8,
	G_CONTROL_COLORPICKER_DEPTH_16,
	G_CONTROL_COLORPICKER_DEPTH_32
} ColorPickerDepths;

typedef struct ColorPicker
{
	int mode;
	int depth;
} ColorPickerRec;

GuiComponent* gui_control_colorpicker_create(void);
void	  gui_control_colorpicker_destroy(GuiComponent* picker);
*/

#include <r4/src/core/r_color.h>

#include "../base/gui_component.h"

typedef struct
{
	int       type;
	int       model;
	double    gamma;
	RColor16* color;
	click_func onclick;
} ColorPicker;

GuiComponent* gui_colorwell_create(void* gui, RColor16* color_ref,
				   click_func onclick);
void	  gui_colorwell_destroy(GuiComponent* cmp);

void gui_colorwell_draw(GuiComponent* cmp);
#endif /* gui_control_colorpicker_h */
