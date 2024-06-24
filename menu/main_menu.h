#ifndef MAIN_MENU_H
#define MAIN_MENU_H
// IMPORTANT: This is not the title screen.

#include "scene/gui/box_container.h"

#include "base_menu_layer.h"

class MainMenu : public BaseMenuLayer {
	GDCLASS(MainMenu, BaseMenuLayer);
protected:
	static void _bind_methods();

	HBoxContainer *content;

	void _configure_content_item(Control *item);
	void _enable_entries();
	void _disable_entries();
public:
	MainMenu();

	HBoxContainer *get_content();
};

#endif // MAIN_MENU_H