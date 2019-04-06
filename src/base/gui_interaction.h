//
//  gui_interaction.h
//  gui
//
//  Created by vs on 4/5/19.
//  Copyright © 2019 ruminant. All rights reserved.
//

#ifndef gui_interaction_h
#define gui_interaction_h

#include <coer/coer.h>

typedef struct
{
	double begin;
	double trigger;
	double timeout;
	CPoint start;
}GInteraction;

GInteraction* gui_interaction_create(void);
void gui_interaction_destroy(GInteraction* in);

#endif /* gui_interaction_h */
