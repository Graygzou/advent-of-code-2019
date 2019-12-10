// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Day4.generated.h"

/**
 * 
 */
UCLASS()
class AOC2019_API UDay4 : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	/*
	UFUNCTION(BlueprintCallable, Category = "day4")
	static TArray<int> splitNumberIntoArray(int number);*/

	UFUNCTION(BlueprintCallable, Category = "day4")
	static int ComputeDay4(int lowerBound, int upperBound);

};
