// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "FileToolsStyle.h"

class FFileToolsCommands : public TCommands<FFileToolsCommands>
{
public:

	FFileToolsCommands()
		: TCommands<FFileToolsCommands>(TEXT("FileTools"), NSLOCTEXT("Contexts", "FileTools", "FileTools Plugin"), NAME_None, FFileToolsStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > OpenPluginWindow;
};