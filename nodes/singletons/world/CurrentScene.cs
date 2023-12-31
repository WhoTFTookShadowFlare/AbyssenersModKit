using System;
using Godot;

namespace AbyssenersModKit.Nodes.Singletons.World;

public sealed partial class CurrentScene : Node, IDataDir
{
	[Signal]
	public delegate void SceneChangedEventHandler();

	private static CurrentScene _instance;
	public static CurrentScene Instance { get => _instance; }
	private CurrentScene()
	{
		if(Instance is not null) throw new Exception("Instanced CurrentScene twice!");
		_instance = this;
	}

	private Node _sceneRoot;
	public Node SceneRoot { get => _sceneRoot; }

	private PackedScene _scene;

	[Export]
	public PackedScene Scene { get => _scene; set {
		_sceneRoot?.QueueFree();
		_sceneRoot = value?.Instantiate();
		AddChild(_sceneRoot);
		_scene = value;
		EmitSignal(SignalName.SceneChanged);
	}}

	[Export]
	public string SceneID {
		get {
			if(_scene is null) return "";
			return _scene.ResourcePath.TrimPrefix("res://data/" + GetDataDirName() + '/');
		}
		set {
			if(GD.Load("res://data/" + GetDataDirName() + '/' + value) is PackedScene scn) Scene = scn;
		}
	}

	public string GetDataDirName()
	{
		return "scenes";
	}
}