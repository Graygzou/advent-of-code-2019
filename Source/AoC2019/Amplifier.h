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
	TArray<FString> instructions;
	bool isDone = false;
	bool hasReadSettings = false;

	void Compute(int input, TArray<int>& outputs);
	bool IsDone();
	void Print();
};
