// Fill out your copyright notice in the Description page of Project Settings.


#include "FileToolsModifer.h"
#include "DebugHeader.h"
#include "FileToolsBPLibrary.h"

UFileToolsModifer::UFileToolsModifer(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)
{}

void UFileToolsModifer::OnApply_Implementation()
{
	// DebugHeader::ShowNotifyInfo(TEXT("Base Modifer Is Run"));
}


void UDeleteFile::OnApply_Implementation()
{
	DebugHeader::ShowNotifyInfo(TEXT("Delete Modifer Is Run"));
	// Super::OnApply();
}

void UCreateFolder::OnApply_Implementation()
{
	FString path = CreateDirectoryPath.Path;
	if(UFileToolsBPLibrary::CheckPath(path) && (CreateFolderName.Num() > 0 ))
	{
		// for (auto& i  : *FileSettings->CreateFolderName.CreateIterator())
		// {
		// 	UE_LOG(LogTemp, Warning, TEXT("Hello World %s"),i);
		// }
			
		for (int32 i = 0; i < CreateFolderName.Num(); i++)
		{
			FString TempName = CreateFolderName[i];
			FString FinalPath = path + "\\"+TempName;
			// UE_LOG(LogTemp, Log, TEXT("%s"),*FinalPath);
			bool isSuccess = FPlatformFileManager::Get().GetPlatformFile().CreateDirectory(*FinalPath);
			UE_LOG(LogTemp, Log, TEXT("Create %s"),*FinalPath);
		}
		auto Result = FMessageDialog::Open(EAppMsgType::Ok, FText::FromString(FString::Printf(TEXT("Create Success"))));
	
	}
	// Super::OnApply_Implementation();
}

void UCreateContentFolder::OnApply_Implementation()
{
	// Super::OnApply_Implementation();
	IFileManager& FileManager = IFileManager::Get();
	FString FinalPath = TEXT("/Game/MyNewFolder");
	FileManager.MakeDirectory(*FinalPath, true);
	// if(*CreateContentPath.Path && (CreateFolderName.Num() > 0 ))
	// {
	// 	for (int32 i = 0; i < CreateFolderName.Num(); i++)
	// 	{
	// 		FString TempName = CreateFolderName[i];
	// 		FString ContentPath = *CreateContentPath.Path ;
	// 		FString FinalPath = ContentPath + "/"+TempName  ;
	// 		// UE_LOG(LogTemp, Log, TEXT("%s"),*FinalPath);
	// 		// 检查文件夹是否已经存在
	// 		if (!FileManager.DirectoryExists(*FinalPath))
	// 		{
	// 			// 创建文件夹
	// 			if (FileManager.MakeDirectory(*FinalPath, true))
	// 			{
	// 				UE_LOG(LogTemp, Log, TEXT("Folder created successfully: %s"), *CreateContentPath.Path);
	// 			}
	// 			else
	// 			{
	// 				UE_LOG(LogTemp, Error, TEXT("Failed to create folder: %s"), *CreateContentPath.Path);
	// 			}
	// 			UE_LOG(LogTemp, Log, TEXT("Create %s"),*FinalPath);
	// 		}
	// 		else
	// 		{
	// 			UE_LOG(LogTemp, Warning, TEXT("Folder already exists: %s"), *CreateContentPath.Path);
	// 		}
	// 	}
	// 	auto Result = FMessageDialog::Open(EAppMsgType::Ok, FText::FromString(FString::Printf(TEXT("Create Success"))));
	//
	// }

}


UDeleteFile::UDeleteFile(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)
{
}

UCreateFolder::UCreateFolder(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)
{}

UCreateContentFolder::UCreateContentFolder(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)
{}
