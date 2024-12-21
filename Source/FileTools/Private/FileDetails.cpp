// Fill out your copyright notice in the Description page of Project Settings.


#include "FileDetails.h"

#include "DetailCategoryBuilder.h"
#include "DetailLayoutBuilder.h"
#include "HAL/FileManagerGeneric.h"
#include "HAL/FileManager.h"
#include "Misc/MessageDialog.h"
#include "Slate/Public/Widgets/Input/SButton.h"

void FFileDetails::CustomizeDetails(IDetailLayoutBuilder& DetailBuilder)
{
	TArray<TWeakObjectPtr<UObject>> ObjectsBeingCustomized;
	DetailBuilder.GetObjectsBeingCustomized(ObjectsBeingCustomized);
	for (int32 ObjectIndex = 0; !ModiferSettings.IsValid() &&ObjectIndex < ObjectsBeingCustomized.Num(); ++ObjectIndex)
	{
		const TWeakObjectPtr<UObject>& CurrentObject = ObjectsBeingCustomized[ObjectIndex];
		if (CurrentObject.IsValid())
		{
			ModiferSettings = Cast<UModiferSettings>(CurrentObject.Get());
		}
	}
	const FText FilterString = FText::FromString("File Tools");
	IDetailCategoryBuilder& Category = DetailBuilder.EditCategory("Folder Create");
	TSharedPtr<IPropertyHandle> CreateFilePathInput = Category.AddProperty("CreateFilePath").GetPropertyHandle();
	TSharedPtr<IPropertyHandle> CreateFolderNameInput = Category.AddProperty("CreateFolderName").GetPropertyHandle();

	// CreateFilePathInput.Get()->SetOnPropertyValueChanged(FSimpleDelegate::CreateRaw(this,&FFileDetails::CheckPath));
	
	Category.AddCustomRow(FilterString)
		.WholeRowContent()
		[
			SNew(SSpacer)
		];
		
	Category.AddCustomRow(FilterString)
		.WholeRowContent()
		[
			SNew(SButton)
			// .ButtonStyle(FAppStyle::Get(),"FlatButton.Success")
			.Text(FText::FromString("Folder Create")).HAlign(HAlign_Center)
			.OnClicked_Raw(this, &FFileDetails::PrintFileName)
		];
	
}

TSharedRef<IDetailCustomization> FFileDetails::MakeInstance()
{
	return MakeShareable(new FFileDetails);
}

FReply FFileDetails::PrintFileName() const
{
	// UE_LOG(LogTemp, Warning, TEXT("Hello World %s"),*FileSettings->CreateFilePath.Path);
	return FReply::Handled();
}
//
// bool FFileDetails::CheckPath(FString path)
// {
// 	bool const isSuccess = FPlatformFileManager::Get().GetPlatformFile().DirectoryExists(*path);
// 	if (!isSuccess)
// 	{
// 		auto Result = FMessageDialog::Open(EAppMsgType::Ok, FText::FromString(FString::Printf(TEXT("Path is Wrong"))));
// 	}
// 	return isSuccess;
// }
//
// FReply FFileDetails::CreateFolder()
// {
// 	FString path = FString(*FileSettings->CreateFilePath.Path);
// 	if(CheckPath(path) && ((*FileSettings).CreateFolderName.Num() > 0 ))
// 	{
// 		// for (auto& i  : *FileSettings->CreateFolderName.CreateIterator())
// 		// {
// 		// 	UE_LOG(LogTemp, Warning, TEXT("Hello World %s"),i);
// 		// }
// 		
// 		for (int32 i = 0; i < (*FileSettings).CreateFolderName.Num(); i++)
// 		{
// 			FString TempName = *(*FileSettings).CreateFolderName[i];
// 			FString FinalPath = path + "\\"+TempName;
// 			// UE_LOG(LogTemp, Log, TEXT("%s"),*FinalPath);
// 			bool isSuccess = FPlatformFileManager::Get().GetPlatformFile().CreateDirectory(*FinalPath);
// 			UE_LOG(LogTemp, Log, TEXT("Create %s"),*FinalPath);
// 		}
// 		auto Result = FMessageDialog::Open(EAppMsgType::Ok, FText::FromString(FString::Printf(TEXT("Create Success"))));
//
// 	}
// 	return FReply::Handled();
// }
//
// FReply FFileDetails::DeleteFiles()
// {
// 	FString path = FString(*FileSettings->DeleteFilePath.Path);
//
// 	if (CheckPath(path) && (*FileSettings).DeleteFile)
// 	{
// 		for (int32 i = 0; i < (*FileSettings).DeleteKeyWords.Num(); i++)
// 		{
// 			FString DeleteKeyWords = *(*FileSettings).DeleteKeyWords[i];
// 			// UE_LOG(LogTemp, Log, TEXT("Delete File %s"),*DeleteKeyWords);
// 			TArray<FString> FilePathList;
// 			FilePathList.Empty();
// 			if (DeleteKeyWords.IsEmpty())
// 			{
// 				DeleteKeyWords = TEXT("*.*");
// 			}
// 			// FFileManagerGeneric::Get().FindFilesRecursive(FilePathList,*path,*DeleteKeyWords,true,false);
// 			IFileManager::Get().FindFilesRecursive(FilePathList, *path, *DeleteKeyWords, true, false, true);
// 			for (int32 j = 0; j < FilePathList.Num(); j++)
// 			{
// 				FString FinalPath = *FilePathList[j];
//
// 				// bool isSuccess = FPlatformFileManager::Get().GetPlatformFile().DeleteFile(*FinalPath);
// 				UE_LOG(LogTemp, Log, TEXT("Delete File %s"),*FinalPath);
// 			}
// 			
// 			if ((*FileSettings).DeleteFolder)
// 			{
// 				FilePathList.Empty();
// 				// FFileManagerGeneric::Get().FindFilesRecursive(FilePathList,*path,*DeleteKeyWords,false,true);
// 				IFileManager::Get().FindFilesRecursive(FilePathList, *path, *DeleteKeyWords, true, true, true);
// 				for (int32 j = 0; j < FilePathList.Num(); j++)
// 				{
// 					FString FinalPath = *FilePathList[j];
// 					bool isSuccess = FPlatformFileManager::Get().GetPlatformFile().DeleteDirectoryRecursively(*FinalPath);
// 					UE_LOG(LogTemp, Log, TEXT("Delete Folder %s"),*FinalPath);
// 				}
// 			}
//
//
// 		}
// 		auto Result = FMessageDialog::Open(EAppMsgType::Ok, FText::FromString(FString::Printf(TEXT("DeleteFile Success"))));
//
// 	}
// 	else
// 	{
// 		if (CheckPath(path) && (*FileSettings).DeleteFolder)
// 		{
// 			for (int32 i = 0; i < (*FileSettings).DeleteKeyWords.Num(); i++)
// 			{
// 				FString DeleteKeyWords = *(*FileSettings).DeleteKeyWords[i];
// 				TArray<FString> FilePathList;
// 				FilePathList.Empty();
// 				// UE_LOG(LogTemp, Log, TEXT("%s"),*FinalPath);
// 				// FFileManagerGeneric::Get().FindFilesRecursive(FilePathList,*path,*DeleteKeyWords,false,true);
// 				IFileManager::Get().FindFilesRecursive(FilePathList, *path, *DeleteKeyWords, false, true, false);
// 				for (int32 j = 0; j < FilePathList.Num(); j++)
// 				{
// 					FString FinalPath = *FilePathList[j];
// 					bool isSuccess = FPlatformFileManager::Get().GetPlatformFile().DeleteDirectoryRecursively(*FinalPath);
// 					UE_LOG(LogTemp, Log, TEXT("%s"),*FinalPath);
// 				}
// 			}
// 		}
// 		auto Result = FMessageDialog::Open(EAppMsgType::Ok, FText::FromString(FString::Printf(TEXT("DeleteFile Success"))));
//
// 	}
//
// 	return FReply::Handled();
// }
//
// FReply FFileDetails::MoveFiles()
// {
// 	FString SourcePath = FString(*FileSettings->MoveFileSourcePath.Path);
// 	FString TargetPath = FString(*FileSettings->MoveFileTargetPath.Path);
// 	if (CheckPath(SourcePath) && CheckPath(TargetPath) && !(*FileSettings).CopyFiles)
// 	{
// 		for (int32 i = 0; i < (*FileSettings).MoveKeyWords.Num(); i++)
// 		{
// 			FString MoveKeyWord = *(*FileSettings).MoveKeyWords[i];
// 			TArray<FString> FilePathList;
// 			FilePathList.Empty();
// 			// UE_LOG(LogTemp, Log, TEXT("%s"),*FinalPath);
// 			// FFileManagerGeneric::Get().FindFilesRecursive(FilePathList,*path,*DeleteKeyWords,false,true);
// 			IFileManager::Get().FindFilesRecursive(FilePathList, *SourcePath, *MoveKeyWord, true, false, false);
// 			for (int32 j = 0; j < FilePathList.Num(); j++)
// 			{
// 				FString SrcFilePath = *FilePathList[j];
// 				FString FinalPath = *FilePathList[j].Replace(*SourcePath,*TargetPath);
// 				bool isSuccess = FPlatformFileManager::Get().GetPlatformFile().DeleteDirectoryRecursively(*FinalPath);
// 				// bool isSuccess2 = FPlatformFileManager::Get().GetPlatformFile().MoveFile(*FinalPath,*SrcFilePath);
// 				bool isSuccess2 = IFileManager::Get().Move(*FinalPath,*SrcFilePath,true,true);
// 				UE_LOG(LogTemp, Log, TEXT("%s"),*FinalPath);
// 			}
// 		}
// 		auto Result = FMessageDialog::Open(EAppMsgType::Ok, FText::FromString(FString::Printf(TEXT("Move Success"))));
//
// 	}
// 	if (CheckPath(SourcePath) && CheckPath(TargetPath) && (*FileSettings).CopyFiles)
// 	{
// 		for (int32 i = 0; i < (*FileSettings).MoveKeyWords.Num(); i++)
// 		{
// 			FString MoveKeyWord = *(*FileSettings).MoveKeyWords[i];
// 			TArray<FString> FilePathList;
// 			FilePathList.Empty();
// 			// UE_LOG(LogTemp, Log, TEXT("%s"),*FinalPath);
// 			// FFileManagerGeneric::Get().FindFilesRecursive(FilePathList,*path,*DeleteKeyWords,false,true);
// 			IFileManager::Get().FindFilesRecursive(FilePathList, *SourcePath, *MoveKeyWord, true, false, false);
// 			for (int32 j = 0; j < FilePathList.Num(); j++)
// 			{
// 				FString SrcFilePath = *FilePathList[j];
// 				FString FinalPath = *FilePathList[j].Replace(*SourcePath,*TargetPath);
// 				// bool isSuccess2 = FPlatformFileManager::Get().GetPlatformFile().MoveFile(*FinalPath,*SrcFilePath);
// 				IFileManager::Get().Copy(*FinalPath,*SrcFilePath,true,true);
// 				UE_LOG(LogTemp, Log, TEXT("%s"),*FinalPath);
// 			}
// 		}
// 		auto Result = FMessageDialog::Open(EAppMsgType::Ok, FText::FromString(FString::Printf(TEXT("Copy Success"))));
// 	}
// 	return FReply::Handled();
// }
