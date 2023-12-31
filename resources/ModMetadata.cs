using Godot;

namespace AbyssenersModKit.Resources;

// TODO Mod versions and dependencies

public sealed partial class ModMetadata : Resource
{
	[Export]
	public ModInit Init;
}