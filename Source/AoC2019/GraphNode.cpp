// Fill out your copyright notice in the Description page of Project Settings.


#include "GraphNode.h"

AGraphNode::AGraphNode() : AGraphNode("")
{
}

// Sets default values
AGraphNode::AGraphNode(FString name) : value(name)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGraphNode::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGraphNode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FString AGraphNode::DisplayNode(int level)
{
	FString spaces = "";
	for (int i = 0; i < level; ++i)
	{
		spaces += " ";
	}
	return spaces + value;
}

bool AGraphNode::operator==(const AGraphNode& rhs) const
{
	return value == rhs.value;
}

