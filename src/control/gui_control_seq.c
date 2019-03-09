
//  gui_control_seq.c
//  gui_control_seq
//
//  Created by Andrew Macfarlane on 17/03/17.
//  Copyright © 2017 vaporstack. All rights reserved.

#include "gui_control_seq.h"
#include <vbl/vbl.h>

#include <drw/drw.h>
#include <stdio.h>
#include <stdlib.h>

static void draw(struct GuiComponent* comp, struct GuiComponent* gui)
{
	GuiComponent* cmp = (GuiComponent*)comp;
	// printf("target: %p\n", cmp->target);
	VSeq* seq = (VSeq*)cmp->target;

	// float pos = seq->time_cur;
	float x1 = cmp->bounds.pos.x;
	// float x2 = cmp->bounds.pos.x + cmp->bounds.size.x;
	float y1 = cmp->bounds.pos.y;
	float y2 = cmp->bounds.pos.y + cmp->bounds.size.y;

	// float npos = pos / seq->time_duration;
	// float npos = seq->pos;
	float x = x1 + seq->pos * cmp->bounds.size.x;

	printf("pos: %f\n", seq->pos);

	drw_rect(cmp->bounds.pos.x, cmp->bounds.pos.y,
		 cmp->bounds.pos.x + cmp->bounds.size.x,
		 cmp->bounds.pos.y + cmp->bounds.size.y);

	// drw_rect_r(cmp->bounds);
	drw_push();
	drw_rotate_z(seq->pos * 360);
	drw_line(x, y1, x, y2);

	drw_line(0, 0, x1, y1);

	drw_pop();
}

static void update(struct GuiComponent* comp)
{
}

GuiComponent* gui_control_seq_create(void* data)
{
	GuiComponent* comp = gui_component_create(data);
	comp->name	 = "Sequence viewer";
	comp->draw	 = &draw;
	comp->update       = &update;

	return comp;
}

void gui_control_seq_destroy(GuiComponent* comp)
{
	free(comp);
}
