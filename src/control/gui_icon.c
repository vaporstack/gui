
//  gui_icon.c
//  gui_icon
//
//  Created by Andrew Macfarlane on 20/03/17.
//  Copyright © 2017 vaporstack. All rights reserved.

#include "gui_icon.h"

//#include "../../../wsh/wsh.h"
//#include "../render/r_render.h"
#include <stdlib.h>

static void draw(struct GuiComponent* data, GuiComponent* gui)
{
}

static void update(struct GuiComponent* data)
{
}

GuiComponent* gui_icon_create(void* data)
{
	GuiComponent* cmp = gui_component_create(data);
	cmp->draw	 = &draw;
	cmp->update       = &update;
	cmp->target       = NULL;

	return cmp;
}

void gui_icon_destroy(GuiComponent* cmp)
{
	free(cmp);
}
