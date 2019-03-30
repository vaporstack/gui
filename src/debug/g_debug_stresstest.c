//
//  g_debug_stresstest.c
//  gui
//
//  Created by vs on 3/25/19.
//  Copyright © 2019 ruminant. All rights reserved.
//

#include "g_debug_stresstest.h"


#ifdef DEBUG
#include <gui/src/etc/gui_log.h>

static void recurse_everything(GuiComponent* cmp )
{
	gui_log("poking: %s", cmp->name);
	
	for ( int i = 0 ; i < cmp->num_children; i++ )
	{
		GuiComponent* ch = cmp->children[i];
		recurse_everything(ch);
	}
}

void gui_debug_stresstest(Gui* gui)
{
	gui_log("Beginning stress test.");
	
	recurse_everything(gui->root);
	
}



#endif
