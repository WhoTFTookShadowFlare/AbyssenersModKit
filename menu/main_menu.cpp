#include "main_menu.h"

#include "scene/gui/scroll_container.h"


MainMenu::MainMenu() {
	set_anchor(Side::SIDE_BOTTOM, 0.125);
	set_anchor(Side::SIDE_RIGHT, 1.0);

	ScrollContainer *scroll = memnew(ScrollContainer);
	scroll->set_h_size_flags(Control::SizeFlags::SIZE_EXPAND_FILL);
	scroll->set_v_size_flags(Control::SizeFlags::SIZE_EXPAND_FILL);
	add_child(scroll);

	content = memnew(HBoxContainer);
	content->set_h_size_flags(Control::SizeFlags::SIZE_EXPAND_FILL);
	content->set_v_size_flags(Control::SizeFlags::SIZE_EXPAND_FILL);
	scroll->add_child(content);

	content->connect("child_entered_tree", Callable(this, "_configure_content_item"));
}

void MainMenu::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_content"), &MainMenu::get_content);

	ClassDB::bind_method(D_METHOD("_configure_content_item", "item"), &MainMenu::_configure_content_item);
}

HBoxContainer *MainMenu::get_content() {
	return content;
}

void MainMenu::_configure_content_item(Control *item) {
	item->set_h_size_flags(SizeFlags::SIZE_EXPAND_FILL);
	item->set_v_size_flags(SizeFlags::SIZE_EXPAND_FILL);
}