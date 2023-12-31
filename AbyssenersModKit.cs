#if TOOLS
using Godot;
using System;

namespace AbyssenersModKit;

[Tool]
public partial class AbyssenersModKit : EditorPlugin
{
	private Control ModMetaGeneratorDock;

	public override void _EnterTree()
	{
		AddCustomType("ModMetadata", "Resource", GD.Load<Script>("res://addons/abysseners_mod_kit/resources/ModMetadata.cs"), GD.Load<Texture2D>("res://icon.svg"));
		AddCustomType("ModInit", "Resource", GD.Load<Script>("res://addons/abysseners_mod_kit/resources/ModInit.cs"), GD.Load<Texture2D>("res://icon.svg"));

		AddCustomType("TitleSection", "AspectRatioContainer", GD.Load<Script>("res://addons/abysseners_mod_kit/nodes/instanced/TitleSection.cs"), GD.Load<Texture2D>("res://icon.svg"));

		AddAutoloadSingleton("LoadedMods", "res://addons/abysseners_mod_kit/nodes/singletons/LoadedMods.cs");
		AddAutoloadSingleton("CurrentScene", "res://addons/abysseners_mod_kit/nodes/singletons/world/CurrentScene.cs");
		AddAutoloadSingleton("SaveManager", "res://addons/abysseners_mod_kit/nodes/singletons/data/SaveManager.cs");

		ModMetaGeneratorDock = GD.Load<PackedScene>("res://addons/abysseners_mod_kit/docks/mod_meta_generator.tscn").Instantiate<Control>();
		AddControlToDock(DockSlot.LeftBr, ModMetaGeneratorDock);
	}

	public override void _ExitTree()
	{
		RemoveCustomType("ModMetadata");
		RemoveCustomType("ModInit");

		RemoveCustomType("TitleSection");

		RemoveAutoloadSingleton("LoadedMods");
		RemoveAutoloadSingleton("CurrentScene");

		RemoveControlFromDocks(ModMetaGeneratorDock);
		ModMetaGeneratorDock.QueueFree();
	}
}
#endif // TOOLS
