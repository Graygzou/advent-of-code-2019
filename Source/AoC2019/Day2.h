// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Opcode.h"
#include "Day2.generated.h"

/**
 * 
 */
UCLASS()
class AOC2019_API UDay2 : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	// Day 9
	UFUNCTION(BlueprintCallable, Category = "day9")
	static void RelativeBaseOffset(FOpcode opcode, TMap<int64, FString>& programMap, int& relativeBase);

	// Day 5 
	static void ComputeIfShouldJump(FOpcode opcode, TMap<int64, FString>& programMap, int& index, bool isPositive, int currentBase);

	UFUNCTION(BlueprintCallable, Category = "day5")
	static void StoreInputValue(FOpcode opcode, TMap<int64, FString>& programMap, int currentBase);

	UFUNCTION(BlueprintCallable, Category = "day5")
	static void OutputValue(FOpcode opcode, TMap<int64, FString>& programMap, TArray<int64>& outputs, int currentBase);

	UFUNCTION(BlueprintCallable, Category = "day5")
	static void JumpIfTrue(FOpcode opcode, TMap<int64, FString>& programMap, int& index, int currentBase);

	UFUNCTION(BlueprintCallable, Category = "day5")
	static void JumpIfFalse(FOpcode opcode, TMap<int64, FString>& programMap, int& index, int currentBase);

	UFUNCTION(BlueprintCallable, Category = "day5")
	static void ComputeIsLessThan(FOpcode opcode, TMap<int64, FString>& programMap, int currentBase);

	UFUNCTION(BlueprintCallable, Category = "day5")
	static void ComputeIsEquals(FOpcode opcode, TMap<int64, FString>& programMap, int currentBase);

	// Day 2 
	static FOpcode CreateOpcode(int code, TArray<int64> inputs, TArray<int64> outputs, TArray<int> modes);

	UFUNCTION(BlueprintCallable, Category = "day2")
	static void ComputeAddition(FOpcode opcode, TMap<int64, FString>& programMap, int currentBase);

	UFUNCTION(BlueprintCallable, Category = "day2")
	static void ComputeMultiplication(FOpcode opcode, TMap<int64, FString>& programMap, int currentBase);

	// Main
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "day 2 main function"), Category = "day2")
	static void Compute( UPARAM(ref) TArray<FString>& programArray, TArray<int64> input, TArray<int64>& outputs);

	/*UFUNCTION(BlueprintPure, meta = (HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject", DisplayName = "Create Object From Blueprint", CompactNodeTitle = "Create", Keywords = "new create blueprint"), Category = Game)
	static UObject* NewObjectFromBlueprint(UObject* WorldContextObject, UClass* UC);*/
};
