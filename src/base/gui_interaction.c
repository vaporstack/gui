//
//  gui_interaction.c
//  gui
//
//  Created by vs on 4/5/19.
//  Copyright © 2019 ruminant. All rights reserved.
//

#include "gui_interaction.h"

#include <stdlib.h>


GInteraction* gui_interaction_create(void)
{
	return calloc(1, sizeof(GInteraction));
}

void gui_interaction_destroy(GInteraction* in)
{
	free(in);
}

