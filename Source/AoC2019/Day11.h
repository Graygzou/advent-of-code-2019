// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SimpleSquare.h"
#include "Day11.generated.h"

/**
 * 
 */
UCLASS()
class AOC2019_API ADay11 : public AActor
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AActor> ToSpawnWhite;
	UPROPERTY(EditAnywhere)
	TSubclassOf<class AActor> ToSpawnBlack;

	UFUNCTION(BlueprintCallable, Category = "Day11")
	static void Init(TArray<FString> instructions, int inputSetting);

	UFUNCTION(BlueprintCallable, Category = "Day11")
	static void InitRobot(FVector2D startHeading, FVector2D startPosition, int color);

	UFUNCTION(BlueprintCallable, Category = "Day11")
	static bool ComputeOneStep(TArray<int64>& outputs, int maxOutput);

	UFUNCTION(BlueprintCallable, Category = "Day11")
	static bool ComputeOneStepWithInputs(TArray<int64> inputs, TArray<int64>& outputs, int maxOutput);

	UFUNCTION(BlueprintCallable, Category = "Day11")
	static void MoveRobot(TArray<int64> outputs);

	UFUNCTION(BlueprintCallable, Category = "Day11")
	static int GetNumberPanelsPainted(TArray<FVector2D>& keys, TArray<int>& values);

	UFUNCTION(BlueprintCallable, Category = "Day11")
	void DisplayRegistrationIdentifier();
};
