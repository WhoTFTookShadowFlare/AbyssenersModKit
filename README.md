A Godot addon for making mods for Abysseners.

## Requirements

1. C# knowledge
1. Latest stable Godot mono

## Setup

Use ```git submodule add https://github.com/WhoTFTookShadowFlare/AbyssenersModKit.git addons/abysseners_mod_kit```
to add the addon.
It must be placed in there otherwise it will have errors!

It is recomended to use C# to make Abysseners mods.

Add the following to your .csproj file
```
<ItemGroup>
	<Content Remove="addons/abysseners_mod_kit" />
</ItemGroup>
<ItemGroup>
	<ProjectReference Include="addons/abysseners_mod_kit/AbyssenersModKit.csproj" />
</ItemGroup>
```
That makes it a dependency while still functioning as a Godot addon.