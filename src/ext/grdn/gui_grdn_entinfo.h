//
//  gui_grdn_entinfo.h
//  gui
//
//  Created by vs on 3/9/19.
//  Copyright © 2019 ruminant. All rights reserved.
//

#ifndef gui_grdn_entinfo_h
#define gui_grdn_entinfo_h


#define GUI_EXT_ENABLE_GRDN
#ifdef GUI_EXT_ENABLE_GRDN
#include <grdn/grdn.h>
#include "../../base/gui_component.h"

typedef struct
{
	int foo;
	GEntity *  ent;
}GuiGrdnEntInfo;

GuiComponent* gui_grdn_entinto_create(GEntity* ent);

#endif


#endif /* gui_grdn_entinfo_h */
