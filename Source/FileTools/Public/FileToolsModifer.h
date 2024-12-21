// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/UnrealType.h"
#include "UObject/NoExportTypes.h"
#include "FileToolsModifer.generated.h"

/**
 * 
 */
UCLASS(Abstract,Blueprintable, EditInlineNew,BlueprintType,DisplayName = "FileToolsModifer")
class FILETOOLS_API UFileToolsModifer : public UObject
{

	GENERATED_UCLASS_BODY()

public:
	/** Trigger implementation */
	// virtual void OnApply() ;
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "FileToolsModifer")
	void OnApply() ;
	
	
	
};


UCLASS()
class FILETOOLS_API UModiferSettings : public UObject
{
	GENERATED_BODY()
public:
	/** The name of file */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced,Category = "Modifers" , meta = (DisplayPriority = 2))
	TArray<UFileToolsModifer*> ModiferArray ;

};

UCLASS(BlueprintType, DisplayName = "DeleteFile")
class FILETOOLS_API UDeleteFile : public UFileToolsModifer
{
	
	GENERATED_UCLASS_BODY()

public:
	/** The number of frames in between to sample two poses  */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings)
	FDirectoryPath DeleteFilePath ;

	UPROPERTY(EditAnywhere, Category = Settings, meta=(ToolTip = "*.FileExtension"))
	TArray<FString> DeleteKeyWords;
	
	UPROPERTY(EditAnywhere, Category= Settings)
	bool DeleteFolder = false;
	
	UPROPERTY(EditAnywhere, Category= Settings)
	bool DeleteFile = true;
	/** Trigger implementation */
	// virtual void OnApply() override;
	
	void OnApply_Implementation() ;

};

UCLASS(BlueprintType, DisplayName = "CreateFolder")
class FILETOOLS_API UCreateFolder : public UFileToolsModifer
{
	
	GENERATED_UCLASS_BODY()

public:
	/** The number of frames in between to sample two poses  */
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings)
	FDirectoryPath CreateDirectoryPath;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings)
	TArray<FString> CreateFolderName ;
	
	/** Trigger implementation */
	// virtual void OnApply() override;
	
	void OnApply_Implementation() ;

};

UCLASS(BlueprintType, DisplayName = "CreateContentFolder")
class FILETOOLS_API UCreateContentFolder : public UFileToolsModifer
{

	GENERATED_UCLASS_BODY()

public:
	/** The number of frames in between to sample two poses  */
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings,meta = (ContentDir))
	FDirectoryPath CreateContentPath;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings)
	TArray<FString> CreateFolderName ;
	
	/** Trigger implementation */
	// virtual void OnApply() override;
	
	void OnApply_Implementation() ;

};

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