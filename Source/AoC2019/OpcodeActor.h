// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "OpcodeActor.generated.h"

UCLASS()
class AOC2019_API AOpcodeActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AOpcodeActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = data)
	float opcode;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = data)
	float firstInput;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = data)
	float secondInput;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = data)
	float outputIndex;

	/*UFUNCTION(BlueprintPure, meta = (DisplayName = "Compute opcode", CompactNodeTitle = "Compute", Keywords = "compute"), Category = "opcode")
	int compute();*/

};
