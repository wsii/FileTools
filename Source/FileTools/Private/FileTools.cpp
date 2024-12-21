// Copyright Epic Games, Inc. All Rights Reserved.

#include "FileTools.h"

#include "DebugHeader.h"
#include "FileDetails.h"
#include "FileToolsStyle.h"
#include "FileToolsCommands.h"

#include "LevelEditor.h"
#include "SFileToolsWidget.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "ToolMenus.h"
#include "Widgets/Layout/SScrollBox.h"

static const FName FileToolsTabName("FileTools");

#define LOCTEXT_NAMESPACE "FFileToolsModule"

void FFileToolsModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FFileToolsStyle::Initialize();
	FFileToolsStyle::ReloadTextures();

	FFileToolsCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);
	// add tab
	PluginCommands->MapAction(
		FFileToolsCommands::Get().OpenPluginWindow,
		FExecuteAction::CreateRaw(this, &FFileToolsModule::PluginButtonClicked),
		FCanExecuteAction());
	
	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FFileToolsModule::RegisterMenus));
	
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(FileToolsTabName, FOnSpawnTab::CreateRaw(this, &FFileToolsModule::OnSpawnPluginTab))
		.SetDisplayName(LOCTEXT("FFileToolsTabTitle", "FileTools"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);

	//Register Custom Details for tool 自定义细节面板
	// FPropertyEditorModule& PM = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
	// PM.RegisterCustomClassLayout("ModiferSettings", FOnGetDetailCustomizationInstance::CreateStatic(FFileDetails::MakeInstance));
	// PM.NotifyCustomizationModuleChanged();
	//
}

void FFileToolsModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FFileToolsStyle::Shutdown();
	
	FPropertyEditorModule& PM = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
	PM.UnregisterCustomClassLayout("ModiferSettings");
	
	FFileToolsCommands::Unregister();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(FileToolsTabName);
}

TSharedRef<SDockTab> FFileToolsModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
	
	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			// Put your tab content here!
			SNew(SFileToolsWidget)
		];
}

void FFileToolsModule::PluginButtonClicked()
{
	FGlobalTabmanager::Get()->TryInvokeTab(FileToolsTabName);
}

void FFileToolsModule::Run()
{
	DebugHeader::ShowNotifyInfo(TEXT("Tab is launched"));
}


void FFileToolsModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
			Section.AddMenuEntryWithCommandList(FFileToolsCommands::Get().OpenPluginWindow, PluginCommands);
		}
	}

	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar.PlayToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("PluginTools");
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FFileToolsCommands::Get().OpenPluginWindow));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FFileToolsModule, FileTools)