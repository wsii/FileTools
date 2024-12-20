// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/UnrealType.h"
#include "UObject/NoExportTypes.h"
#include "FileToolsModifer.generated.h"

/**
 * 
 */
UCLASS(Abstract, Blueprintable, EditInlineNew, Config = Slate, DisplayName = "FileToolsModifer")
class FILETOOLS_API UFileToolsModifer : public UObject
{

	GENERATED_UCLASS_BODY()

public:

	/** Trigger implementation */
	virtual void OnApply() ;
	
};


UCLASS(BlueprintType, DisplayName = "DeleteFile")
class FILETOOLS_API UDeleteFile : public UFileToolsModifer
{
	
	GENERATED_UCLASS_BODY()

public:
	/** The number of frames in between to sample two poses  */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings, meta = (ClampMin = "0", UIMin = "0"))
	int32 MaxSampleIntervalFrame;




	/** Trigger implementation */
	virtual void OnApply() override;
};
