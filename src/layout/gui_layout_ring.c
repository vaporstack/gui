//
//  gui_layout_ring.c
//  gui
//
//  Created by vs on 9/20/19.
//  Copyright © 2019 ruminant. All rights reserved.
//

#include "gui_layout_ring.h"

#include <math.h>

void gui_layout_ring(GuiComponent* cmp)
{

	/*
	 if( total == 0 )
	 return;

	 double amt = M_PI / total * 2;


	 cJSON *current_element = NULL;
	 char *current_key = NULL;

	 cJSON_ArrayForEach(current_element, cleanmap)
	 {
	 current_key = current_element->string;

	 if (current_key != NULL)
	 {

	 double r = amt * pos;
	 drw_push();
	 double dx = cos(r) * w * .5;
	 double dy = sin(r) * w * .5;
	 drw_translate(dx, dy, 0);
	 drw_color_u(1);
	 drw_circle(64);
	 drw_type_draw("%s", current_key);
	 drw_pop();
	 pos++;
	 if ( pos >= nclean )
	 break;

	 }
	 }


	 */

	unsigned n   = cmp->num_children;
	double   amt = M_PI / n * 2;
	double   w   = cmp->bounds.size.x;
	double h = cmp->bounds.size.y;
	
	double bigger = (w > h) ? w : h;
	
	for (unsigned i = 0; i < n; i++)
	{
		GuiComponent* child = cmp->children[i];
		double	r     = amt * i;
		double	dx    = cos(r) * bigger * .5;
		double	dy    = sin(r) * bigger * .5;

		gui_component_set(child, dx, dy);
	}
}
