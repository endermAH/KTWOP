using UnrealBuildTool;

public class GameplaySystem : ModuleRules
{
	public GameplaySystem(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core", "CoreUObject", "Engine", "InputCore"
		});

		PrivateDependencyModuleNames.AddRange(new string[] {  });
	}
}