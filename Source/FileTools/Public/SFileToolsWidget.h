// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

class UModiferSettings;
/**
 * 
 */
class FILETOOLS_API SFileToolsWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SFileToolsWidget)
	{}
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);
	TSharedPtr<IDetailsView> SettingsView;
	TSharedPtr<UModiferSettings> ModiferSetting;
	
	FReply Run();
	
	UModiferSettings* ToolInstance ;
};
