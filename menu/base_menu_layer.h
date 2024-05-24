#ifndef BASE_MENU_H
#define BASE_MENU_H

#include "scene/gui/panel_container.h"

class BaseMenuLayer : public PanelContainer {
	GDCLASS(BaseMenuLayer, PanelContainer);
protected:
	static void _bind_methods();

	bool pauses = false;
	bool can_close_by_button = true;
public:
	BaseMenuLayer();

	bool should_pause();
	void set_should_pause(bool value);

	bool get_can_close_by_button();
	void set_can_close_by_button(bool value);
};

#endif // BASE_MENU_H