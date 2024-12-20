// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "FileSettings.generated.h"

class UFileToolsModifer;
/**
 * 
 */
UCLASS()
class FILETOOLS_API UFileSettings : public UObject
{
	GENERATED_BODY()
public:
	/** The name of file */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced,Category = "Modifers" , meta = (DisplayPriority = 2))
	TArray<UFileToolsModifer*> FileToolsModiferArray ;
	//
	// /** The name of file */
	// UPROPERTY(EditAnywhere, Category = "Folder Create")
	// FDirectoryPath CreateFilePath ;
	//
	// UPROPERTY(EditAnywhere, Category = "Folder Create")
	// TArray<FString> CreateFolderName ;
	//
	// UPROPERTY(EditAnywhere, Category="File Delete")
	// FDirectoryPath DeleteFilePath ;
	//
	// UPROPERTY(EditAnywhere, Category = "File Delete", meta=(ToolTip = "*.FileExtension"))
	// TArray<FString> DeleteKeyWords;
	//
	// UPROPERTY(EditAnywhere, Category="File Delete")
	// bool DeleteFolder = false;
	//
	// UPROPERTY(EditAnywhere, Category="File Delete")
	// bool DeleteFile = true;
	//
	// // UPROPERTY(EditAnywhere, Category="File Delete")
	// // bool DeleteInvert = false;
	//
	// UPROPERTY(EditAnywhere, Category="File Move")
	// FDirectoryPath MoveFileSourcePath;
	//
	// UPROPERTY(EditAnywhere, Category="File Move")
	// FDirectoryPath MoveFileTargetPath;
	//
	// UPROPERTY(EditAnywhere, Category = "File Move",meta=(ToolTip = "*.FileExtension"))
	// TArray<FString> MoveKeyWords;
	//
	// UPROPERTY(EditAnywhere, Category="File Move",meta=(ToolTip = "Copy File To TargetPath"))
	// bool CopyFiles = true;
	//
	void PrintFileName();
};
