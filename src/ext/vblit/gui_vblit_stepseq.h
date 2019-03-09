//
//  gui_vbl_stepseq.h
//  gui
//
//  Created by vs on 4/24/18.
//  Copyright © 2018 ruminant. All rights reserved.
//

#ifndef gui_vbl_stepseq_h
#define gui_vbl_stepseq_h

#ifdef gui_EXT_ENABLE_VBLIT

#include <gui/gui.h>

GuiComponent* gui_vbl_stepseq_create(void* data);
void	  gui_vbl_stepseq_destroy(GuiComponent* stepseq);

#endif

#endif /* gui_vbl_stepseq_h */
