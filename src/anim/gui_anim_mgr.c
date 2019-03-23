//
//  gui_anim_mgr.c
//  gui
//
//  Created by vs on 12/1/18.
//  Copyright © 2018 ruminant. All rights reserved.
//

#include "gui_anim_mgr.h"

#include <r4/src/anim/r_animation_mgr.h>

static bool check_any_animating(GuiComponent* cmp)
{

	//	me?
	if (cmp->animating)
		return true;

	//	any of my kids?
	for (int i = 0; i < cmp->num_children; i++)
	{
		if (check_any_animating(cmp->children[i]))
			return true;
	}
	return false;
}

//	void data here should be an animator function
//	WRONG data here should be a guicomponent wrappeda s a void*
static void r_update_comp(void* data)
{
	if (!data)
	{
		printf("passed me some NULL bullshit\n");
		return;
	}
	GuiComponent* cmp = data;

	if (!cmp->container)
		return;

	//bool any_animating = false;
	for (int i = 0; i < cmp->num_children; i++)
	{
		GuiComponent* child = cmp->children[i];
		if (!child)
		{
			printf("NULL child\n");
			continue;
		}
		//if (child->animating )

		r_update_comp(child);
	}
	/*
#ifdef DEBUG
	if (check_any_animating(cmp))
	{
		printf("Some children are animating.\n");
		//	todo do something
	}
	else
	{
		printf("No children are animating.\n");
	}
#endif
	*/
}

void gui_anim_mgr_update(void* data)
{
	GuiAnimMgr* mgr = data;
	r_update_comp(mgr->root);
}

GuiAnimMgr* gui_anim_mgr_create(GuiComponent* root)
{
	GuiAnimMgr* mgr = calloc(1, sizeof(GuiAnimMgr));

	RAnimator* anim = calloc(1, sizeof(RAnimator));
	anim->animate   = r_update_comp;
	anim->data      = root;
	anim->active    = false;
	mgr->animator   = anim;

	mgr->root = root;

	RAnimationMgr* query = r_animation_mgr_query();
	if (!query)
	{
		printf("Failed to query animation manager\n");
	}
	else
	{
		r_animation_mgr_register(query, anim);
	}

	return mgr;
}

void gui_anim_mgr_destroy(GuiAnimMgr* mgr)
{
	free(mgr);
}
