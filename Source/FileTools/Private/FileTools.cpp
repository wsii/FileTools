// Copyright Epic Games, Inc. All Rights Reserved.

#include "FileTools.h"
#include "FileSettings.h"
#include "FileDetails.h"
#include "FileToolsStyle.h"
#include "FileToolsCommands.h"

#include "LevelEditor.h"
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

	//Register Custom Details for tool
	FPropertyEditorModule& PM = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
	PM.RegisterCustomClassLayout("FileSettings", FOnGetDetailCustomizationInstance::CreateStatic(FFileDetails::MakeInstance));
	PM.NotifyCustomizationModuleChanged();
	
}

void FFileToolsModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FFileToolsStyle::Shutdown();
	
	FPropertyEditorModule& PM = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
	PM.UnregisterCustomClassLayout("FileSettings");
	
	FFileToolsCommands::Unregister();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(FileToolsTabName);
}

TSharedRef<SDockTab> FFileToolsModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
	FText WidgetText = FText::Format(
		LOCTEXT("WindowWidgetText", "Add code to {0} in {1} to override this window's contents"),
		FText::FromString(TEXT("FFileToolsModule::OnSpawnPluginTab")),
		FText::FromString(TEXT("FileTools.cpp"))
		);
	
	// Create a property view
	FPropertyEditorModule& EditModule = FModuleManager::Get().GetModuleChecked<FPropertyEditorModule>("PropertyEditor");

	FDetailsViewArgs DetailsViewArgs;
	{
		DetailsViewArgs.bAllowSearch = true;
		DetailsViewArgs.bHideSelectionTip = true;
		DetailsViewArgs.bLockable = false;
		DetailsViewArgs.bSearchInitialKeyFocus = true;
		DetailsViewArgs.bUpdatesFromSelection = false;
		DetailsViewArgs.NotifyHook = nullptr;
		DetailsViewArgs.bShowOptions = true;
		DetailsViewArgs.bShowModifiedPropertiesOption = false;
		DetailsViewArgs.bShowScrollBar = false;
		DetailsViewArgs.bShowOptions = true;
	}

	// FStructureDetailsViewArgs StructureViewArgs;
	// {
	// 	StructureViewArgs.bShowObjects = true;
	// 	StructureViewArgs.bShowAssets = true;
	// 	StructureViewArgs.bShowClasses = true;
	// 	StructureViewArgs.bShowInterfaces = true;
	// }
	
	SettingsView = EditModule.CreateDetailView(DetailsViewArgs);
	UFileSettings* ToolInstance = NewObject<UFileSettings>(GetTransientPackage(), UFileSettings::StaticClass());
	SettingsView->SetObject(ToolInstance);
	
	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			// Put your tab content here!
			SNew(SBox)
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			[
				SNew(SScrollBox)
				+SScrollBox::Slot()
				[
					SettingsView.ToSharedRef()
				]
			]
		];
}

void FFileToolsModule::PluginButtonClicked()
{
	FGlobalTabmanager::Get()->TryInvokeTab(FileToolsTabName);
}

void FFileToolsModule::OnOpenTool()
{
	if(!WindowCreated)
	{
		UFileSettings* ToolInstance = NewObject<UFileSettings>(GetTransientPackage(), UFileSettings::StaticClass());
		ToolInstance->AddToRoot();

		FPropertyEditorModule& PM = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");

		TArray<UObject*> ObjectsToView;
		ObjectsToView.Add(ToolInstance);
		TSharedRef<SWindow> Window = PM.CreateFloatingDetailsView(ObjectsToView, false);
		Window->SetTitle(FText::FromString("File Tools"));
		Window->SetOnWindowClosed(FOnWindowClosed::CreateRaw(this, &FFileToolsModule::ToolWindowClosed));
		WindowCreated = true;
	}
}

void FFileToolsModule::ToolWindowClosed(const TSharedRef<SWindow>&)
{
	WindowCreated = false;
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