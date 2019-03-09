//
//  gui_anim_mgr.h
//  gui
//
//  Created by vs on 12/1/18.
//  Copyright © 2018 ruminant. All rights reserved.
//

#ifndef gui_anim_mgr_h
#define gui_anim_mgr_h

#include "../base/gui_component.h"

typedef struct GuiAnimMgr
{
	GuiComponent* root;
	void* animator;
}GuiAnimMgr;

void gui_anim_mgr_update(void* mgr);
GuiAnimMgr* gui_anim_mgr_create(GuiComponent* root);
void gui_anim_mgr_destroy(GuiAnimMgr* mgr);



#endif /* gui_anim_mgr_h */
