#include "menu_stack.h"

#include "scene/main/scene_tree.h"
#include "scene/main/window.h"

#include "base_menu_layer.h"
#include "main_menu.h"

MenuStack *MenuStack::singleton;

void MenuStack::_bind_methods() {
	ClassDB::bind_method(D_METHOD("_setup"), &MenuStack::_setup);
	ClassDB::bind_method(D_METHOD("_handle_layer_removal", "layer"), &MenuStack::_handle_layer_removal);

	ClassDB::bind_method(D_METHOD("add_layer", "layer"), &MenuStack::add_layer);
	ADD_SIGNAL(MethodInfo(Variant::NIL, "layer_added", PropertyInfo(Variant::OBJECT, "layer")));
	ADD_SIGNAL(MethodInfo(Variant::NIL, "layer_removed", PropertyInfo(Variant::OBJECT, "layer")));

	ClassDB::bind_method(D_METHOD("add_main_menu"), &MenuStack::add_main_menu);
	ADD_SIGNAL(MethodInfo(
		Variant::NIL, "main_menu_added", PropertyInfo(
			Variant::OBJECT, "menu", PROPERTY_HINT_OBJECT_ID, MainMenu::get_class_static(),
			PROPERTY_USAGE_DEFAULT, MainMenu::get_class_static()
		)
	));
}

void MenuStack::_setup() {
	SceneTree::get_singleton()->get_root()->add_child(this);

	set_anchors_and_offsets_preset(Control::LayoutPreset::PRESET_FULL_RECT);
	set_mouse_filter(Control::MouseFilter::MOUSE_FILTER_IGNORE);
}

MenuStack::MenuStack() {
	singleton = this;
}

MenuStack *MenuStack::get_singleton() {
	return singleton;
}

void MenuStack::add_layer(BaseMenuLayer *layer) {
	layer->connect("tree_exiting", Callable(this, "_handle_layer_removal").bind(layer));
	emit_signal("layer_added", layer);
	add_child(layer);
}

void MenuStack::_handle_layer_removal(BaseMenuLayer *layer) {
	emit_signal("layer_removed", layer);
}

MainMenu *MenuStack::add_main_menu() {
	MainMenu *menu = memnew(MainMenu);
	add_layer(menu);
	emit_signal("main_menu_added", menu);
	return menu;
}