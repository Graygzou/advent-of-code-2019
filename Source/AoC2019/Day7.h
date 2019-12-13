// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Day7.generated.h"

/**
 * 
 */
UCLASS()
class AOC2019_API UDay7 : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "day7")
	static int ComputeOneCycle(UPARAM(ref) TArray<FString>& programArray, TArray<int> currentCombinaison, int programInput);

	UFUNCTION(BlueprintCallable, Category = "day7")
	static int ComputeNCycle(UPARAM(ref) TArray<FString> programArray, TArray<int> currentCombinaison, int programInput);

	UFUNCTION(BlueprintCallable, Category = "day7")
	static int FindRightCombinaison(UPARAM(ref) TArray<FString>& programArray, int input, TArray<int> currentCombinaison);

	UFUNCTION(BlueprintCallable, Category = "day7")
	static int FindRightCombinaisonPart2(UPARAM(ref) TArray<FString>& programArray, int input, TArray<int> currentCombinaison);

};
