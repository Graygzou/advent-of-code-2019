// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Amplifier.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FAmplifier
{
	GENERATED_USTRUCT_BODY()

public:
	FAmplifier();
	FAmplifier(TArray<FString> instructions, int inputSetting);
	~FAmplifier();

	int inputSetting;
	int InstructionPointer;
	TMap<int64, FString> instructions;
	//TArray<FString> instructions;
	bool isDone = false;
	bool hasReadSettings = false;
	int initProgramSize;
	int currentBase;

	void Compute(TArray<int64> input, TArray<int64>& outputs, int maxOutput);
	bool IsDone();
	void Print();
};
