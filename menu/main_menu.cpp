#include "main_menu.h"

#include "scene/gui/scroll_container.h"

#include "scene/gui/base_button.h"


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

	connect("became_top_layer", Callable(this, "_enable_entries"));
	connect("no_longer_top_layer", Callable(this, "_disable_entries"));
}

void MainMenu::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_content"), &MainMenu::get_content);

	ClassDB::bind_method(D_METHOD("_configure_content_item", "item"), &MainMenu::_configure_content_item);
	ClassDB::bind_method(D_METHOD("_enable_entries"), &MainMenu::_enable_entries);
	ClassDB::bind_method(D_METHOD("_disable_entries"), &MainMenu::_disable_entries);
}

HBoxContainer *MainMenu::get_content() {
	return content;
}

void MainMenu::_configure_content_item(Control *item) {
	item->set_h_size_flags(SizeFlags::SIZE_EXPAND_FILL);
	item->set_v_size_flags(SizeFlags::SIZE_EXPAND_FILL);
}

void MainMenu::_enable_entries() {
	for(int c_idx = 0; c_idx < content->get_child_count(); c_idx++) {
		Node *entry_node = content->get_child(c_idx);
		ERR_CONTINUE(!entry_node->is_class(BaseButton::get_class_static()));
		BaseButton *entry = cast_to<BaseButton>(entry_node);
		entry->set_disabled(false);
	}

	if(content->get_child_count() > 0) {
		Node *first_entry = content->get_child(0);
		ERR_FAIL_COND(!first_entry->is_class(BaseButton::get_class_static()));
		BaseButton *entry = cast_to<BaseButton>(first_entry);
		entry->call_deferred("grab_focus");
	}
}

void MainMenu::_disable_entries() {
	for(int c_idx = 0; c_idx < content->get_child_count(); c_idx++) {
		Node *entry_node = content->get_child(c_idx);
		ERR_CONTINUE(!entry_node->is_class(BaseButton::get_class_static()));
		BaseButton *entry = cast_to<BaseButton>(entry_node);
		entry->set_disabled(true);
	}
}