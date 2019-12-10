// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Day8.generated.h"

/**
 * 
 */
UCLASS()
class AOC2019_API UDay8 : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable, Category = "day8")
	static int ComputeDay8(FString input, int width, int height);

	UFUNCTION(BlueprintCallable, Category = "day8")
	static void ComputeDay8Part2(FString input, int width, int height);

};
