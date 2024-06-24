#ifndef BASE_MENU_H
#define BASE_MENU_H

#include "scene/gui/panel_container.h"

class BaseMenuLayer : public PanelContainer {
	GDCLASS(BaseMenuLayer, PanelContainer);
protected:
	static void _bind_methods();
public:
	BaseMenuLayer();
};

#endif // BASE_MENU_H