using Godot;

namespace AbyssenersModKit.Resources;

public abstract partial class ModInit : Resource
{
	public abstract void LoadLang();
	public abstract void LoadHooks();
}