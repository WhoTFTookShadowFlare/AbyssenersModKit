using Godot;
using System;

namespace AbyssenersModKit.Singletons.Data;

public sealed partial class SaveManager : Node
{
	private static SaveManager _instance;
	public static SaveManager Instance {
		get => _instance;
	}

	private SaveManager()
	{
		if(Instance is not null) throw new Exception("Instanced SaveManager twice!");
		_instance = this;
	}
}