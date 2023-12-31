using System;
using System.Net;
using AbyssenersModKit.Resources;
using Godot;
using Godot.Collections;

namespace AbyssenersModKit.Nodes.Singletons;

public sealed partial class LoadedMods : Node
{

	private static LoadedMods _instance;
	public static LoadedMods Instance { get => _instance; }
	private LoadedMods()
	{
		if(Instance is not null) throw new Exception("Instanced LoadedMods twice!");
		_instance = this;
	}

	private Dictionary<string, ModMetadata> _mods = [];

	public ModMetadata this[string ID]
	{
		get
		{
			_mods.TryGetValue(ID, out ModMetadata value);
			return value;
		}
		set
		{
			if (_mods.ContainsKey(ID)) throw new Exception("Duplicate mod ID " + ID);
			_mods[ID] = value;
		}
	}

	public void _LoadLang()
	{
		foreach(ModMetadata mod in _mods.Values)
		{
			mod.Init.LoadLang();
		}
	}

	public void _LoadHooks()
	{
		foreach(ModMetadata mod in _mods.Values)
		{
			mod.Init.LoadHooks();
		}
	}
}