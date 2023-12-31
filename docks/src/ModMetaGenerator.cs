#if TOOLS
using System;
using AbyssenersModKit.Resources;
using Godot;

namespace AbyssenersModKit.Docks;

[Tool]
public sealed partial class ModMetaGenerator : ScrollContainer
{
	[Export]
	private LineEdit _modIDLine;

	[Export]
	private Button _generateButton;

	public override void _Ready()
	{
		_generateButton.Pressed += GenerateMetadata;
	}

	private void GenerateMetadata()
	{
		string modID = _modIDLine.Text;

		ModMetadata metadata = new();

		if(!DirAccess.DirExistsAbsolute("res://mod_metadata")) DirAccess.MakeDirRecursiveAbsolute("res://mod_metadata");
		Error err = ResourceSaver.Save(metadata, "res://mod_metadata/" + modID + ".tres");
		if(err != Error.Ok) GD.PrintErr("Failed to make mod metadata with error: " + err);
	}
}
#endif // TOOLS