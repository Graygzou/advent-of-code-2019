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

	/*UOpcode();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = data)
	float opcode;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = data)
	float firstInput;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = data)
	float secondInput;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = data)
	float outputIndex;*/

	/* Day 5 */
	UFUNCTION(BlueprintCallable, Category = "day5")
	static void StoreInputValue(FOpcode opcode, TArray<FString>& programArray);

	UFUNCTION(BlueprintCallable, Category = "day5")
	static void OutputValue(FOpcode opcode, TArray<FString>& programArray);

	UFUNCTION(BlueprintCallable, Category = "day5")
	static void JumpIfTrue(FOpcode opcode, TArray<FString>& programArray, int& index);

	UFUNCTION(BlueprintCallable, Category = "day5")
	static void JumpIfFalse(FOpcode opcode, TArray<FString>& programArray, int& index);

	UFUNCTION(BlueprintCallable, Category = "day5")
	static void ComputeIsLessThan(FOpcode opcode, TArray<FString>& programArray);

	UFUNCTION(BlueprintCallable, Category = "day5")
	static void ComputeIsEquals(FOpcode opcode, TArray<FString>& programArray);

	/* Day 2 */
	static FOpcode CreateOpcode(int code, TArray<int> inputs, TArray<int> outputs, TArray<int> modes);

	UFUNCTION(BlueprintCallable, Category = "day2")
	static void ComputeAddition(FOpcode opcode, TArray<FString>& programArray);

	UFUNCTION(BlueprintCallable, Category = "day2")
	static void ComputeMultiplication(FOpcode opcode, TArray<FString>& programArray);

	/* Main */
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "day 2 main function"), Category = "day2")
	static void Compute( UPARAM(ref) TArray<FString>& programArray, int input);

	/*UFUNCTION(BlueprintPure, meta = (HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject", DisplayName = "Create Object From Blueprint", CompactNodeTitle = "Create", Keywords = "new create blueprint"), Category = Game)
	static UObject* NewObjectFromBlueprint(UObject* WorldContextObject, UClass* UC);*/
};
