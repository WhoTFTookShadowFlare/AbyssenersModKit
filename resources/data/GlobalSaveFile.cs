namespace AbyssenersModKit.Resources.Data;

public sealed partial class GlobalSaveFile : DataFile
{
	public override string GetFileDir()
	{
		return "user://";
	}

	public override string GetFileName()
	{
		return "GlobalSave";
	}
}