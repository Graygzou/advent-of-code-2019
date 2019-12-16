// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Opcode.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FOpcode
{
	GENERATED_USTRUCT_BODY()

	FOpcode();
	FOpcode(int code, TArray<int> inputs, TArray<int> outputs, TArray<int> modes);
	FOpcode(int code, TArray<int64> inputs, TArray<int64> outputs, TArray<int> modes);
	~FOpcode();

	void Print();

	int code;
	TArray<int64> input;
	TArray<int64> output;
	TArray<int> modes;
};
