using Godot;
using System;
using System.Linq;

namespace AbyssenersModKit.Nodes.Instanced;

public partial class TitleSection : ScrollContainer
{
	[Export]
	private VBoxContainer _content;

	public void AddElement(Control button)
	{
		_content.AddChild(button);
	}

	public void Disable()
	{
		foreach(Node elementNode in _content.GetChildren())
		{
			if(elementNode is not Control element) continue;
			element.FocusMode = FocusModeEnum.None;

			if(elementNode is BaseButton btn) btn.Disabled = true;
		}
	}

	public void Enable()
	{
		foreach(Node elementNode in _content.GetChildren())
		{
			if(elementNode is not Control element) continue;
			element.FocusMode = FocusModeEnum.All;

			if(elementNode is BaseButton btn) btn.Disabled = false;
		}

		_content.GetChild<Control>(0).GrabFocus();
	}
}
