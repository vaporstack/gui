
//  gui_comp_rline.c
//  gui_comp_rline
//
//  Created by Andrew Macfarlane on 11/15/17.
//  Copyright © 2017 vaporstack. All rights reserved.

#ifndef gui_comp_rline_h_
#define gui_comp_rline_h_

#include "../base/gui_component.h"
#include <r4/src/geo/r_line.h>

//.#include <r4/r4.h>

typedef struct GuiCompRLine
{
	RLineHnd hnd;
	RPoint   center;
	float    radius;
} GuiCompRLine;

GuiComponent* gui_comp_rline_create(void* gui, RLineHnd hnd);
void	  gui_comp_rline_destroy(GuiComponent* comp);

#endif
