// Fill out your copyright notice in the Description page of Project Settings.


#include "FileToolsModifer.h"

UFileToolsModifer::UFileToolsModifer(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)
{}

void UFileToolsModifer::OnApply()
{
}

UDeleteFile::UDeleteFile(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer),
                                                                       MaxSampleIntervalFrame(0)
{
}

void UDeleteFile::OnApply()
{
	Super::OnApply();
}
