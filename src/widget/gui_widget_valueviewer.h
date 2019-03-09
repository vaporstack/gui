//
//  gui_widget_valueviewer.h
//  gui
//
//  Created by vs on 6/26/18.
//  Copyright © 2018 ruminant. All rights reserved.
//

#ifndef gui_widget_valueviewer_h
#define gui_widget_valueviewer_h

//#include <stdio.h>

#include "../base/gui_component.h"
#define GUI_VIEWER_BUFFERSIZE 256

typedef struct GuiValueViewer
{
	double* addr;
	double  history[GUI_VIEWER_BUFFERSIZE];
} GuiValueViewer;

GuiComponent* gui_widget_valueviewer_create(void* gui, double* addr);
void	  gui_widget_valueviewer_destroy(GuiValueViewer* viewer);

#endif /* gui_widget_valueviewer_h */
