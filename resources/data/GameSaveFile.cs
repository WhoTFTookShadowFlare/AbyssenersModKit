namespace AbyssenersModKit.Resources.Data;

public sealed partial class GameSaveFile : DataFile
{
	private string _fileName = "";

	public override string GetFileDir()
	{
		return "user://saves";
	}

	public override string GetFileName()
	{
		return _fileName;
	}
}