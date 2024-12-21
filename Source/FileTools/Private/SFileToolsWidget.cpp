// Fill out your copyright notice in the Description page of Project Settings.


#include "SFileToolsWidget.h"

#include "FileToolsModifer.h"
#include "DebugHeader.h"
#include "SlateOptMacros.h"
#include "Widgets/Layout/SScrollBox.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SFileToolsWidget::Construct(const FArguments& InArgs)
{
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
	

	//设置细节面板的object
	SettingsView = EditModule.CreateDetailView(DetailsViewArgs);
	ToolInstance = NewObject<UModiferSettings>(GetTransientPackage(), UModiferSettings::StaticClass());
	ToolInstance->AddToRoot();//  prevents the object and all its descendants from being deleted during garbage collection.
	SettingsView->SetObject(ToolInstance);
	

	ChildSlot
	[
			SNew(SBox)
			.HAlign(HAlign_Fill)
			// .VAlign(VAlign_Fill)
			[
				SNew(SOverlay)
				+ SOverlay::Slot()
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				[
					SNew(SVerticalBox)
					+ SVerticalBox::Slot()
					[
						SNew(SScrollBox)
						+SScrollBox::Slot()
						[
							SettingsView.ToSharedRef()
						]
						// +SScrollBox::Slot()
						// [
						// 	SNew(SSpacer)
						// 	.Size(FVector2D(100.0f, 50.0f)) 
						// ]
					]
				]
				+ SOverlay::Slot()
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Bottom) // 将按钮固定到底部
				[
					SNew(SBox)
					.HeightOverride(50.0f)
					[
						SNew(SButton)
						.HAlign(HAlign_Center)
						.VAlign(VAlign_Fill)
						.OnClicked(this, &SFileToolsWidget::Run)
						.ButtonStyle(FAppStyle::Get(),"FlatButton.Success")
						.Content()
						[
							SNew(STextBlock)
							.Text(FText::FromString("RUN"))
							.Font(FSlateFontInfo(FPaths::EngineContentDir() / TEXT("Slate/Fonts/Roboto-Regular.ttf"), 24)) // 设置字体大小
						]
						.Text(FText::FromString("RUN"))
				
				
					]
				
				]
			]
	];

}

FReply SFileToolsWidget::Run()
{
	DebugHeader::ShowNotifyInfo(TEXT("Tab is launched"));
	for (auto Element : ToolInstance->ModiferArray)
	{
		Element->OnApply();
	}
	return FReply::Handled();
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
