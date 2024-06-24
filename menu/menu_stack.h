#ifndef MENU_STACK_H
#define MENU_STACK_H

#include "scene/gui/control.h"

#include "base_menu_layer.h"
#include "main_menu.h"

class MenuStack : public Control {
	GDCLASS(MenuStack, Control);
protected:
	static MenuStack *singleton;
	static void _bind_methods();
	
	void _setup();
	void _handle_layer_removal(BaseMenuLayer *layer);
public:
	MenuStack();
	static MenuStack *get_singleton();

	void add_layer(BaseMenuLayer *layer);
	void remove_top_layer();

	MainMenu *add_main_menu();
};

#endif // MENU_STACK_H