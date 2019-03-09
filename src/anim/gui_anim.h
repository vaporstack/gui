//
//  gui_anim.h
//  gui
//
//  Created by vs on 11/12/17.
//  Copyright © 2017 ruminant. All rights reserved.
//

#ifndef gui_anim_h
#define gui_anim_h

#include <vector/vector.h>

typedef struct GuiAnimBlock
{
	int    type;
	double time;
} GuiAnimBlock;

typedef struct GuiAnimationChain
{
	struct vector_t chain;
} GuiAnimationChain;

#endif /* gui_anim_h */
