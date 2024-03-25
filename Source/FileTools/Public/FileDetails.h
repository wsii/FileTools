// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "IDetailCustomization.h"
#include "FileSettings.h"
#include "DetailWidgetRow.h"


/**
 * 
 */

class FILETOOLS_API FFileDetails : public IDetailCustomization
{
public:
	virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;
	static TSharedRef<IDetailCustomization> MakeInstance();

	//Ref to the current tool instance
	TWeakObjectPtr<UFileSettings> FileSettings;

	FReply PrintFileName() const;

	bool CheckPath(FString path);
	
	FReply CreateFolder() ;
	FReply DeleteFiles() ;
	FReply MoveFiles() ;
};
