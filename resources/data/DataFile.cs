using System.Collections.Generic;
using Godot;

namespace AbyssenersModKit.Resources.Data;

public abstract partial class DataFile : Resource
{
	private Godot.Collections.Dictionary<string, Resource> _data = [];

	public Resource this[string id] {
		get {
			if(_data.ContainsKey(id)) return _data[id];
			return null;
		}
		set {
			_data[id] = value;
		}
	}

	public abstract string GetFileDir();
	public abstract string GetFileName();
	public virtual string GetFileExtension()
	{
		return OS.IsDebugBuild() ? ".tres" : ".res";
	}
}