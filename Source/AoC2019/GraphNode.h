// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GraphNode.generated.h"

UCLASS()
class AOC2019_API AGraphNode : public AActor
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	FString value;
	AGraphNode* parent = NULL;
	TArray<AGraphNode*> children;

	// Sets default values for this actor's properties
	AGraphNode();
	AGraphNode(FString value);

	FString DisplayNode(int level);

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	bool operator==(const AGraphNode& rhs) const;

};
