// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Day3.generated.h"

enum Direction { Vertical, Horizontal };

struct Point2D
{
public:
	int x;
	int y;

	// Constructors
	Point2D() = default;
	Point2D(int x, int y) : x(x), y(y) 
	{}

	FString Print()
	{
		return "(" + FString::FromInt(x) + ", " + FString::FromInt(y) + ")";
	}
};


struct Line
{
	Point2D origin;			// Always the most on the left and bottom point in the line.
	Point2D end;				// Always the further on top and right point of the line.
	Direction direction;
};

struct Polygon
{
	TArray<Point2D> points;
};


/**
 * 
 */
UCLASS()
class AOC2019_API UDay3 : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	static Point2D CreateNewPoint(Point2D previousPoint, FString nextDirection);

	static bool IntersectExistingLine(Point2D newPoint, Polygon currentPolygone, Point2D& intersectionPts);

	static TArray<Point2D> FindIntersectionPoints(Point2D previousPts, Point2D pointInside, FString nextDirection, Polygon intersectedPolygon);

	static bool InsideShape(Point2D point, TArray<Polygon> polygones, Polygon& intersectedPolygon);

	UFUNCTION(BlueprintCallable, Category = "day3")
	static int ComputeDay3(TArray<FString> directionOfFirstLine, TArray<FString> directionOfSecondLine);

};
