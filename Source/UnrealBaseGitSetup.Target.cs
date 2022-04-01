// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class UnrealBaseGitSetupTarget : TargetRules
{
	public UnrealBaseGitSetupTarget( TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		ExtraModuleNames.AddRange( new string[]
		{
			"UnrealBaseGitSetup",
			"DMGSystem",
			"TurretSystem",
			"EnemySystem",
			"StatusSystem",
			"ImplementedStatuses"
		} );
	}
}
