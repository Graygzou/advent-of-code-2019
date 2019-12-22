// Fill out your copyright notice in the Description page of Project Settings.


#include "Day11.h"
#include "Amplifier.h"
#include <Runtime\Engine\Classes\Engine\World.h>

static bool init = false;
static FVector2D robotPosition;
static FVector2D robotHeading;
static TMap<FVector2D, int> visitedPosition;	// Position (X,Y) and color attached to it
static int defaultColor;

static FAmplifier amplifier;

void ADay11::Init(TArray<FString> instructions, int inputSetting)
{
	amplifier = FAmplifier(instructions, inputSetting);
	visitedPosition.Empty();
	visitedPosition.Reset();
}

void ADay11::InitRobot(FVector2D startHeading, FVector2D startPosition, int color)
{
	defaultColor = color;
	robotPosition = startPosition;
	robotHeading = startHeading; // FVector2D(0, 1);
	init = true;
}

bool ADay11::ComputeOneStep(TArray<int64>& outputs, int maxOutput)
{
	int currentInput = defaultColor;
	if (visitedPosition.Contains(robotPosition))
	{
		UE_LOG(LogTemp, Log, TEXT("ALREADY VISITED = %d"), visitedPosition[robotPosition])
		currentInput = visitedPosition[robotPosition];
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("New..."))
	}

	amplifier.Compute(TArray<int64>{ currentInput }, outputs, maxOutput);
	return amplifier.IsDone();
}

bool ADay11::ComputeOneStepWithInputs(TArray<int64> inputs, TArray<int64>& outputs, int maxOutput)
{
	amplifier.Compute(inputs, outputs, maxOutput);
	return amplifier.IsDone();
}

void ADay11::MoveRobot(TArray<int64> outputs)
{
	if (!init)
	{
		InitRobot(FVector2D(0, 1), FVector2D::ZeroVector, 0);
	}

	int colorCurrentPanel = outputs[0];
	int nextDirection = outputs[1];

	// Add the current color to the TMAP at the robot position
	visitedPosition.Add(robotPosition, colorCurrentPanel);

	// Update the robot position and heading
	float angle = nextDirection ? 270 : 90;
	//FVector::rotat
	robotHeading = robotHeading.GetRotated(angle);
	//robotHeading = nextDirection ? FVector2D(robotHeading.Y, robotHeading.X) : -FVector2D(robotHeading.Y, robotHeading.X);

	// Make sure the heading is normalized (it should always be in theory..)
	robotHeading.Normalize();

	// Update the robot position and make sure it's rounded properly
	robotPosition += robotHeading;
	robotPosition = robotPosition.RoundToVector();
}

int ADay11::GetNumberPanelsPainted(TArray<FVector2D>& keys, TArray<int>& values)
{
	visitedPosition.GenerateValueArray(values);
	return visitedPosition.GetKeys(keys);
}

void ADay11::DisplayRegistrationIdentifier()
{
	TArray<FVector2D> positions;
	visitedPosition.GetKeys(positions);
	UWorld* world = GetWorld();
	if (world)
	{
		for (int i = 0; i < positions.Num(); ++i)
		{
			FActorSpawnParameters spawnParams;
			FRotator rotator;

			FVector spawnLocation = FVector(positions[i].X * 150, positions[i].Y * 150, 0);

			if (visitedPosition[positions[i]])
			{
				// Spawn object at the position
				world->SpawnActor<ASimpleSquare>(ToSpawnWhite, spawnLocation, rotator, spawnParams);
			}
			else
			{
				world->SpawnActor<ASimpleSquare>(ToSpawnBlack, spawnLocation, rotator, spawnParams);
			}
			
		}
	}
}