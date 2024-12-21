// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "IDetailCustomization.h"

#include "DetailWidgetRow.h"
#include "FileToolsModifer.h"

/**
 * 
 */

class FILETOOLS_API FFileDetails : public IDetailCustomization
{
public:
	virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;
	static TSharedRef<IDetailCustomization> MakeInstance();

	//Ref to the current tool instance
	TWeakObjectPtr<UModiferSettings> ModiferSettings;

	FReply PrintFileName() const;
	
};
