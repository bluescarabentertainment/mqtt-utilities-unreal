// Copyright (c) 2019 Nineva Studios

using System.IO;
using UnrealBuildTool;

#if UE_5_0_OR_LATER
using EpicGames.Core;
#else
using Tools.DotNETCommon;
#endif

public class MqttUtilities : ModuleRules
{
	public MqttUtilities(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
			}
		);

		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Projects"
			}
		);

		string PluginPath = Utils.MakePathRelativeTo(ModuleDirectory, Target.RelativeEnginePath);

		// Additional routine for Windows
		if (Target.Platform == UnrealTargetPlatform.Win64)
		{
			string MosquittoLibPath = Path.Combine(ModuleDirectory, "../ThirdParty/", Target.Platform.ToString(), "mosquitto");

			PrivateIncludePaths.Add(Path.Combine(ModuleDirectory, "Private/Windows"));
			PrivateIncludePaths.Add(Path.Combine(MosquittoLibPath, "includes"));
			
			PublicDelayLoadDLLs.Add("mosquitto.dll");
			PublicDelayLoadDLLs.Add("mosquittopp.dll");

			PublicAdditionalLibraries.Add(Path.Combine(MosquittoLibPath, "mosquitto.lib"));
			PublicAdditionalLibraries.Add(Path.Combine(MosquittoLibPath, "mosquittopp.lib"));

			RuntimeDependencies.Add("$(BinaryOutputDir)/mosquitto.dll", Path.Combine(MosquittoLibPath, "mosquitto.dll"));
			RuntimeDependencies.Add("$(BinaryOutputDir)/mosquittopp.dll", Path.Combine(MosquittoLibPath, "mosquittopp.dll"));
			RuntimeDependencies.Add("$(BinaryOutputDir)/libssl-1_1-x64.dll", Path.Combine(MosquittoLibPath, "libssl-1_1-x64.dll"));
			RuntimeDependencies.Add("$(BinaryOutputDir)/libcrypto-1_1-x64.dll", Path.Combine(MosquittoLibPath, "libcrypto-1_1-x64.dll"));
		}

		// Additional routine for Mac
		if (Target.Platform == UnrealTargetPlatform.Mac)
		{
			string MosquittoLibPath = Path.Combine(ModuleDirectory, "../ThirdParty/", Target.Platform.ToString(), "mosquitto");

			PrivateIncludePaths.Add(Path.Combine(ModuleDirectory, "Private/Mac"));
			PrivateIncludePaths.Add(Path.Combine(MosquittoLibPath, "includes"));

			RuntimeDependencies.Add("$(BinaryOutputDir)/mosquitto.dylib", Path.Combine(MosquittoLibPath, "mosquitto.dylib"));
			RuntimeDependencies.Add("$(BinaryOutputDir)/mosquittopp.dylib", Path.Combine(MosquittoLibPath, "mosquittopp.dylib"));
		}

		// Additional routine for iOS
		if (Target.Platform == UnrealTargetPlatform.IOS)
		{
			PrivateIncludePaths.Add(Path.Combine(ModuleDirectory, "Private/IOS"));

			PublicAdditionalFrameworks.Add(new Framework("MQTTClient", "../ThirdParty/IOS/MQTTClient.embeddedframework.zip"));
			PublicAdditionalFrameworks.Add(new Framework("SocketRocket", "../ThirdParty/IOS/SocketRocket.embeddedframework.zip"));

			PublicFrameworks.AddRange(
				new string[]
				{
					"Foundation",
					"Security",
					"CFNetwork",
					"CoreData"
				}
			);

			PrivateDependencyModuleNames.AddRange(new string[] { "Launch" });
			AdditionalPropertiesForReceipt.Add("IOSPlugin", Path.Combine(PluginPath, "MqttUtilities_IOS_UPL.xml"));
		}

		// Additional routine for Android
		if (Target.Platform == UnrealTargetPlatform.Android)
		{
			PrivateIncludePaths.Add(Path.Combine(ModuleDirectory, "Private/Android"));

			PrivateDependencyModuleNames.AddRange(new string[] { "Launch" });
			AdditionalPropertiesForReceipt.Add("AndroidPlugin", Path.Combine(PluginPath, "MqttUtilities_Android_UPL.xml"));
		}
	}
}
