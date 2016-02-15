// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

using System.IO;
using UnrealBuildTool;

public class BlutenUndLeveln : ModuleRules
{
    private string ModulePath
    {
        get { return Path.GetDirectoryName( RulesCompiler.GetModuleFilename( this.GetType().Name ) ); }
    }

    private string ThirdPartyPath
    {
        get { return Path.GetFullPath(Path.Combine(ModulePath, "../../ThirdParty/")); }
    }

	public BlutenUndLeveln(TargetInfo Target)
	{
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });
	    LoadLibNoise(Target);
	    LoadLibnoiseDLL();
	}

    public bool LoadLibNoise(TargetInfo Target)
    {
        bool isLibrarySupported = false;

        if ((Target.Platform == UnrealTargetPlatform.Win64) || (Target.Platform == UnrealTargetPlatform.Win32))
        {
            isLibrarySupported = true;

            string PlatformString = (Target.Platform == UnrealTargetPlatform.Win64) ? "x64" : "x86";
            string LibrariesPath = Path.Combine(ThirdPartyPath, "Libnoise", "Libraries");

            PublicAdditionalLibraries.Add(Path.Combine(LibrariesPath, "libnoise." + PlatformString + ".lib"));
        }

        if (isLibrarySupported)
        {
            // Include path
            PublicIncludePaths.Add(Path.Combine(ThirdPartyPath, "Libnoise", "Includes"));
        }

        Definitions.Add(string.Format("WITH_LIBNOISE_BINDING={0}", isLibrarySupported ? 1 : 0));

        return isLibrarySupported;
    }

    public bool LoadLibnoiseDLL()
    {
        string LibrariesPath = Path.Combine(ThirdPartyPath, "Libnoise", "Libraries");
        RuntimeDependencies.Add(new RuntimeDependency(Path.Combine(LibrariesPath, "LibnoiseDLL.dll")));
        PublicAdditionalLibraries.Add(Path.Combine(LibrariesPath, "LibnoiseDLL.lib"));
        return true;
    }

}
