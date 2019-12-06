// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Opcode.generated.h"

/**
 * 
 */
UCLASS()
class AOC2019_API UOpcode : public UBlueprintFunctionLibrary
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

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "day 2 main function"), Category = "opcode")
	static void compute( UPARAM(ref) TArray<FString>& programArray);

	/*UFUNCTION(BlueprintPure, meta = (HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject", DisplayName = "Create Object From Blueprint", CompactNodeTitle = "Create", Keywords = "new create blueprint"), Category = Game)
	static UObject* NewObjectFromBlueprint(UObject* WorldContextObject, UClass* UC);*/
};
