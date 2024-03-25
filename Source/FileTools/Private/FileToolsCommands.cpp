// Copyright Epic Games, Inc. All Rights Reserved.

#include "FileToolsCommands.h"

#define LOCTEXT_NAMESPACE "FFileToolsModule"

void FFileToolsCommands::RegisterCommands()
{
	UI_COMMAND(OpenPluginWindow, "FileTools", "Bring up FileTools window", EUserInterfaceActionType::Button, FInputChord());
}

#undef LOCTEXT_NAMESPACE
