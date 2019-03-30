//
//  g_debug_visualizer.c
//  gui
//
//  Created by vs on 3/25/19.
//  Copyright © 2019 ruminant. All rights reserved.
//

#include "g_debug_visualizer.h"

#ifdef DEBUG
#include <drw/drw.h>

#define PAD 16
#include <gui/gui.h>

static void recurse(GuiComponent* cmp )
{
	
	if ( 0 == strcmp(kGuiUnnamedComponent, cmp->name))
	{
		printf("Naughty!\n");
	}
	
	
	
	RRect r = cmp->bounds;
	r.pos.x -= PAD * .5;
	r.pos.y -= PAD * .5;
	r.size.x += PAD;
	r.size.y += PAD;
	drw_rect_r(r);
	drw_push();
	drw_translate2f( r.pos.x + r.size.x * .5, r.pos.y + r.size.y * .5);
	
	drw_type_draw(cmp->name);
	drw_pop();
	for ( unsigned int i = 0; i < cmp->num_children; i++ )
	{
		GuiComponent* child = cmp->children[i];
		recurse(child);
	}
}

void g_debug_visualizer_draw(Gui* gui)
{
	GuiComponent* cmp = gui->root;
	recurse(cmp);
}


#endif

