// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Day3.h"
#include "Day10.generated.h"

USTRUCT(BlueprintType)
struct FPoint
{
	GENERATED_USTRUCT_BODY()

	float x;
	float y;
	FString name;

	FPoint() : x(0), y(0), name("")
	{
	}

	FPoint(float x, float y) : x(x), y(y)
	{
		this->x = FCString::Atof(*FString::SanitizeFloat(x));
		this->y = FCString::Atof(*FString::SanitizeFloat(y));
		this->name = FString::SanitizeFloat(this->x, 5) + ", " + FString::SanitizeFloat(this->y, 5);
	}

	FString Print()
	{
		return FString::SanitizeFloat(x) + ", " + FString::SanitizeFloat(y);
	}

	bool operator==(const FPoint& rhs) const
	{
		return (FMath::Abs(this->x - rhs.x) < 0.001) && (FMath::Abs(this->y - rhs.y) < 0.001);
		//return this->x == rhs.x && this->y == rhs.y;
	}

	FORCEINLINE friend uint32 GetTypeHash(const FPoint& pts) { return ::GetTypeHash(pts.name); }
};

/**
 * 
 */
UCLASS()
class AOC2019_API UDay10 : public UDay3
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable, Category = "Day10")
	static void ComputeDay10(TArray<FString> lines);

	UFUNCTION(BlueprintCallable, Category = "Day10")
	static void ComputePart2(FPoint stationPosition, TArray<FPoint> finalDirectionsComputed, TArray<FPoint> positions);

};
