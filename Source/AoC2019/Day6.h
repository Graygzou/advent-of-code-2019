// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GraphNode.h"
#include "Day6.generated.h"

/**
 * 
 */
UCLASS()
class AOC2019_API UDay6 : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "day6")
	static int ComputeDay6(TArray<FString> inputsDependencies);

private:
	UFUNCTION(Category = "day6")
	static AGraphNode* CreateNode(FString name);

	UFUNCTION(Category = "day6")
	static void AddChildIfNecessary(TMap<FString, AGraphNode*>& dict, FString orbitName, FString centerName);


	UFUNCTION(BlueprintCallable, Category = "day6")
	static void DisplayGraph(AGraphNode* root);

	UFUNCTION(BlueprintCallable, Category = "day6")
	static int ResultPart1(AGraphNode* root);

	UFUNCTION(Category = "day6")
	static int ResultPart2(TMap<FString, AGraphNode*>& dict, FString starting, FString arrival);
};
