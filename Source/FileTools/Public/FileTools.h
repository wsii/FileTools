// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FileSettings.h"
#include "IDetailsView.h"
#include "Modules/ModuleManager.h"
#include "Widgets/SWindow.h"

class FToolBarBuilder;
class FMenuBuilder;

class FFileToolsModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	
	/** This function will be bound to Command (by default it will bring up plugin window) */
	void PluginButtonClicked();

private:

	void RegisterMenus();

	TSharedRef<class SDockTab> OnSpawnPluginTab(const class FSpawnTabArgs& SpawnTabArgs);

private:
	TSharedPtr<class FUICommandList> PluginCommands;

	// TSharedPtr<IStructureDetailsView> SettingsView;
	TSharedPtr<IDetailsView> SettingsView;
	TSharedPtr<UFileSettings> FileSetting;
};
