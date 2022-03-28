// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "spToolCommands.h"

#define LOCTEXT_NAMESPACE "FspToolModule"

void FspToolCommands::RegisterCommands()
{
	UI_COMMAND(PluginAction, "spTool", "Execute spTool action", EUserInterfaceActionType::Button, FInputGesture());
}

#undef LOCTEXT_NAMESPACE
