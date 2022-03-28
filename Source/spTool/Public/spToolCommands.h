// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "spToolStyle.h"

class FspToolCommands : public TCommands<FspToolCommands>
{
public:

	FspToolCommands()
		: TCommands<FspToolCommands>(TEXT("spTool"), NSLOCTEXT("Contexts", "spTool", "spTool Plugin"), NAME_None, FspToolStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > PluginAction;
};
