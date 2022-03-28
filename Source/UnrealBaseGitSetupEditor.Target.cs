// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class UnrealBaseGitSetupEditorTarget : TargetRules
{
	public UnrealBaseGitSetupEditorTarget( TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		ExtraModuleNames.AddRange( new string[]
		{
			"UnrealBaseGitSetup",
			"DMGSystem",
			"TurretSystem",
			"EnemySystem",
			"StatusSystem"
		} );
	}
}
