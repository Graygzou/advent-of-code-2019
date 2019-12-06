// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ReadWriteFile.generated.h"

/**
 * 
 */
UCLASS()
class AOC2019_API UReadWriteFile : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "IOFiles")
	static bool FileSaveString(FString SaveTextB, FString FileNameB);

	UFUNCTION(BlueprintPure, Category = "IOFiles")
	static bool FileLoadString(FString FileNameA, FString& SaveTextA);

	UFUNCTION(BlueprintPure, Category = "IOFiles")
	static TArray<FString> SplitString(FString txt, const FString delimiter);
	
};
