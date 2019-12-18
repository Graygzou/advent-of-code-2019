// Fill out your copyright notice in the Description page of Project Settings.


#include "Day10.h"

void UDay10::ComputeDay10(TArray<FString> lines)
{
	// Array of points
	TArray<FPoint> points;

	// For each line collect all the points
	int currentY = 0;
	
	for (FString line : lines)
	{
		int currentX = 0;
		for (TCHAR character : line.GetCharArray())
		{
			if (character == '#')
			{
				points.Add(FPoint(currentX, currentY));
			}

			currentX++;
		}
		currentY++;
	}

	// Compute the number of visible pts for the current one
	int MaxNbPointVisible = 0;
	FPoint finalPts;
	TArray<FPoint> finalDirectionsComputed;
	TArray<FPoint> finalPositions;
	for (int i = 0; i < points.Num(); ++i)
	{
		int NbPointVisible = 0;
		TArray<FPoint> directionsComputed;
		TMap<FPoint, float> lengths;
		TMap<FPoint, FPoint> positions;

		// Debug
		//UE_LOG(LogTemp, Log, TEXT("%s"), *points[i].Print());

		for (int j = 0; j < points.Num(); ++j)
		{
			if (i != j)
			{
				// Compute the normalized direction between the two points
				FPoint direction = FPoint(points[j].x - points[i].x, points[j].y - points[i].y);

				UE_LOG(LogTemp, Log, TEXT("Direction : %s"), *direction.Print());

				// Normalized the direction
				float length = FMath::Sqrt(FMath::Square(direction.x) + FMath::Square(direction.y));
				FPoint normalizedDirection = FPoint(FMath::FloorToInt((direction.x/length)*1000.0)/1000.0, FMath::FloorToInt((direction.y/length)*1000.0)/1000.0);

				UE_LOG(LogTemp, Log, TEXT("Normalized direction : %s"), *normalizedDirection.Print());

				//FVector2D test = FVector2D(points[j].x - points[i].x, points[j].y - points[i].y);
				//test.Normalize();
				if (!directionsComputed.Contains(normalizedDirection))
				{
					UE_LOG(LogTemp, Log, TEXT(" + 1 for griffondor ! "));
					directionsComputed.Add(normalizedDirection);
					positions.Add(normalizedDirection, points[j]);
					lengths.Add(normalizedDirection, length);
					NbPointVisible++;
				}
				else if (lengths.Contains(normalizedDirection) && lengths[normalizedDirection] > length)
				{
					// Override the previous value
					lengths.Add(normalizedDirection, length);
					// Override the point too <= that's what we want
					positions.Add(normalizedDirection, points[j]);
				}
				else
				{
					UE_LOG(LogTemp, Log, TEXT(" NOP ! "));
				}
			}
		}

		if (NbPointVisible > MaxNbPointVisible)
		{
			UE_LOG(LogTemp, Log, TEXT("New Challenger ! : %s"), *points[i].Print());
			MaxNbPointVisible = NbPointVisible;
			finalPts = points[i];

			finalDirectionsComputed.Empty();
			finalDirectionsComputed.Append(directionsComputed);

			finalPositions.Empty();
			positions.GenerateValueArray(finalPositions);
		}

	}
	UE_LOG(LogTemp, Log, TEXT(" Final Point = %s"), *finalPts.Print());
	UE_LOG(LogTemp, Log, TEXT(" See that many asteroids = %d"), MaxNbPointVisible);

	ComputePart2(finalPts, finalDirectionsComputed, finalPositions);
}


float dotProduct(FPoint pts1, FPoint pts2)
{
	return pts1.x * pts2.x + pts1.y * pts2.y;
}

void UDay10::ComputePart2(FPoint stationPosition, TArray<FPoint> finalDirectionsComputed, TArray<FPoint> positions)
{
	TMap<float, FPoint> asteroidsShot;

	FPoint upVector = FPoint(0, -1);

	for (int i = 0; i < finalDirectionsComputed.Num(); ++i)
	{
		float length1 = FMath::Sqrt(FMath::Square(upVector.x) + FMath::Square(upVector.y));
		float length2 = FMath::Sqrt(FMath::Square(finalDirectionsComputed[i].x) + FMath::Square(finalDirectionsComputed[i].y));

		// Compute the dot product for this point and the up vector
		float angle = FMath::Acos(dotProduct(upVector, finalDirectionsComputed[i]) / (length1 * length2));

		// Allow to create signe angle
		if (positions[i].x > stationPosition.x)
		{
			angle *= -1;
		}

		asteroidsShot.Add(angle, positions[i]);
	}

	// Sort the Map with the key value
	asteroidsShot.KeySort([](float key1, float key2) {
		if (key1 == 0 && key2 != 0)
		{
			return true;
		}
		else if (key1 != 0 && key2 == 0)
		{
			return false;
		}
		else if (key1 < 0 && key2 < 0)
		{
			return key1 > key2;
		}
		else if(key1 > 0 && key2 > 0)
		{
			return key1 > key2;
		}
		else
		{
			return key1 < key2; // sort keys in reverse
		}
	});

	// Read the value 200 (199 since it starts at zero)
	TArray<float> keys;
	asteroidsShot.GetKeys(keys);
	UE_LOG(LogTemp, Log, TEXT("key %f"), keys[199]);
	UE_LOG(LogTemp, Log, TEXT("Point part 2 %s"), *asteroidsShot[keys[199]].Print());
	UE_LOG(LogTemp, Log, TEXT("Final result = %d"), asteroidsShot[keys[199]].x * 100.0 + asteroidsShot[keys[199]].y);


}