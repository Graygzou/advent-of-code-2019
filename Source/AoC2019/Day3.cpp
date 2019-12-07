// Fill out your copyright notice in the Description page of Project Settings.


#include "Day3.h"

Point2D UDay3::CreateNewPoint(Point2D previousPoint, FString nextDirection)
{
	Point2D newPoint = previousPoint;
	switch (nextDirection[0])
	{
	case 'D':
		nextDirection.RemoveAt(0);
		newPoint.y -= FCString::Atoi(*nextDirection);
		break;
	case 'R':
		nextDirection.RemoveAt(0);
		newPoint.x += FCString::Atoi(*nextDirection);
		break;
	case 'U':
		nextDirection.RemoveAt(0);
		newPoint.y += FCString::Atoi(*nextDirection);
		break;
	case 'L':
		nextDirection.RemoveAt(0);
		newPoint.x -= FCString::Atoi(*nextDirection);
		break;
	default:
		break;
	}
	newPoint.cumulatedSteps += FCString::Atoi(*nextDirection);
	return newPoint;
}

bool UDay3::IntersectExistingLine(Point2D newPoint, Polygon currentPolygone, Point2D& intersectionPts)
{
	// TODO
	return false;
}

//bool intersect(int minX, int maxX, int minY, int maxY, Point2D pt1, Point2D pt2, Point2D& intersection)
bool intersect(Point2D pt1Wire1, Point2D pt2Wire1, Point2D pt1Wire2, Point2D pt2Wire2, Point2D& intersection)
{
	int minY = FMath::Min(pt1Wire1.y, pt2Wire1.y);
	int maxY = FMath::Max(pt1Wire1.y, pt2Wire1.y);
	int minX = FMath::Min(pt1Wire1.x, pt2Wire1.x);
	int maxX = FMath::Max(pt1Wire1.x, pt2Wire1.x);

	// Study a horizontal line made by pt1 and pt2 crossing with a vertical one made by Xs and Ys
	bool intersectVert = pt1Wire2.y == pt2Wire2.y && minX == maxX && pt1Wire2.y > minY && pt1Wire2.y < maxY && ((pt1Wire2.x < minX && pt2Wire2.x > minX) || (pt1Wire2.x > minX && pt2Wire2.x < minX));
	// Study a vertical line made by pt1 and pt2 crossing with a horizontal one made by Xs and Ys
	bool intersectHoriz = pt1Wire2.x == pt2Wire2.x && minY == maxY && pt1Wire2.x > minX && pt1Wire2.x < maxX && ((pt1Wire2.y < minY && pt2Wire2.y > minY) || (pt1Wire2.y > minY && pt2Wire2.y < minY));

	if (intersectHoriz)
	{
		//UE_LOG(LogTemp, Log, TEXT("Horizontal"));
		intersection = Point2D(pt1Wire2.x, maxY);
		intersection.cumulatedSteps = pt1Wire2.cumulatedSteps + FMath::Abs(pt1Wire2.y - maxY);

		// Add the first wire TODO
		if (pt1Wire1.cumulatedSteps < pt2Wire1.cumulatedSteps)
		{
			intersection.cumulatedSteps += pt1Wire1.cumulatedSteps + FMath::Abs(pt1Wire1.x - pt1Wire2.x);
		}
		else
		{
			intersection.cumulatedSteps += pt2Wire1.cumulatedSteps + FMath::Abs(pt2Wire1.x - pt1Wire2.x);
		}
		

		UE_LOG(LogTemp, Log, TEXT("Horizontal %s"), *intersection.Print());
	}
	else if(intersectVert)
	{
		//UE_LOG(LogTemp, Log, TEXT("Vertical"));
		intersection = Point2D(minX, pt1Wire2.y);
		// Compute for the second wire
		intersection.cumulatedSteps = pt1Wire2.cumulatedSteps + FMath::Abs(pt1Wire2.x - minX);

		// Add the first wire TODO
		if (pt1Wire1.cumulatedSteps < pt2Wire1.cumulatedSteps)
		{
			intersection.cumulatedSteps += pt1Wire1.cumulatedSteps + FMath::Abs(pt1Wire1.y - pt1Wire2.y);
		}
		else
		{
			intersection.cumulatedSteps += pt2Wire1.cumulatedSteps + FMath::Abs(pt2Wire1.y - pt1Wire2.y);
		}

		UE_LOG(LogTemp, Log, TEXT("Vertical %s"), *intersection.Print());
	}
	return intersectHoriz || intersectVert;
}

TArray<Point2D> UDay3::FindIntersectionPoints(Point2D previousPts, Point2D pointInside, FString nextDirection, Polygon intersectedPolygon)
{
	TArray<Point2D> intersectionPts;
	Point2D nextPts;
	if (!nextDirection.IsEmpty())
	{
		nextPts = CreateNewPoint(pointInside, nextDirection);
		UE_LOG(LogTemp, Log, TEXT("next Point %s"), *nextPts.Print());
	}

	// For all the polygon side
	for (int i = 0, j = intersectedPolygon.points.Num() - 1; i < intersectedPolygon.points.Num(); j = i++)
	{
		/*int minY = FMath::Min(intersectedPolygon.points[i].y, intersectedPolygon.points[j].y);
		int maxY = FMath::Max(intersectedPolygon.points[i].y, intersectedPolygon.points[j].y);
		int minX = FMath::Min(intersectedPolygon.points[i].x, intersectedPolygon.points[j].x);
		int maxX = FMath::Max(intersectedPolygon.points[i].x, intersectedPolygon.points[j].x);*/

		// Compute next direction intersection
		Point2D intersectionPt;
		if (!nextDirection.IsEmpty() && intersect(intersectedPolygon.points[i], intersectedPolygon.points[j], pointInside, nextPts, intersectionPt))
		{
			UE_LOG(LogTemp, Log, TEXT("INTERSECT NEXT PTS (pts = %s , %s )"), *pointInside.Print(), *nextPts.Print());
			intersectionPts.Add(intersectionPt);
		}
		if (intersect(intersectedPolygon.points[i], intersectedPolygon.points[j], previousPts, pointInside, intersectionPt))
		{
			UE_LOG(LogTemp, Log, TEXT("INTESECT PREVIOUS PTS (pts = %s , %s )"), *pointInside.Print(), *previousPts.Print());
			intersectionPts.Add(intersectionPt);
		}
	}

	//DEBUG
	for (Point2D p : intersectionPts)
	{
		UE_LOG(LogTemp, Log, TEXT("FINAL COUNTDOWN %s"), *p.Print());
	}
	// END DEBUG

	return intersectionPts;
}

// taken from https://wrf.ecse.rpi.edu//Research/Short_Notes/pnpoly.html
bool UDay3::InsideShape(Point2D point, TArray<Polygon> polygones, Polygon& intersectedPolygon)
{
	bool result = false;
	for (int p = 0; p < polygones.Num() && !result; ++p)
	{
		for (int i = 0, j = polygones[p].points.Num() - 1; i < polygones[p].points.Num(); j = i++)
		{
			if ((polygones[p].points[i].y > point.y) != (polygones[p].points[j].y > point.y) &&
				(point.x < (polygones[p].points[j].x - polygones[p].points[i].x) * (point.y - polygones[p].points[i].y) / 
				(polygones[p].points[j].y - polygones[p].points[i].y) + polygones[p].points[i].x))
			{
				result = !result;
			}
		}
		if (result)
		{
			intersectedPolygon = polygones[p];
		}
	}
	return result;
}

int UDay3::ComputeDay3(TArray<FString> directionOfFirstWire, TArray<FString> directionOfSecondWire, int& stepNumber)
{
	int currentStepNumber = -1;
	Point2D closestIntersectionPts;

	//UE_LOG(LogTemp, Log, TEXT("Test right, %d"), directionOfFirstWire.Num());
	//UE_LOG(LogTemp, Log, TEXT("Test right, %d"), directionOfSecondWire.Num());

	TArray<Line> linesFirstWire;
	linesFirstWire.Reserve(directionOfFirstWire.Num());

	// We assume we only have ONE WIRE per line of text. So we cannot have Up and Down following each other (or Right and Left).

	// Create all the points and the convexes polygones of one of the first wire
	TArray<Polygon> polygons;
	Polygon currentPoly = Polygon();
	Point2D currentPts;
	Point2D previousPts = Point2D(0, 0);
	currentPoly.points.Add(previousPts);
	for (int32 i = 0; i < directionOfFirstWire.Num(); ++i)
	{
		// Create the new point
		currentPts = CreateNewPoint(previousPts, directionOfFirstWire[i]);
		UE_LOG(LogTemp, Log, TEXT("Point %s"), *currentPts.Print());

		// Check if we need to create another Polygone
		Point2D* intersectionPts = NULL;
		// /!\ Maybe osef de ça...
		bool needAnotherShape = IntersectExistingLine(currentPts, currentPoly, *intersectionPts);
		if (needAnotherShape)
		{
			// Remove the last point and insert the intersection one instead
			Point2D lastPts = currentPoly.points.Pop();
			currentPoly.points.Add(*intersectionPts);
			polygons.Add(currentPoly);

			// Create a new Polygone and insert the points
			currentPoly = Polygon();
			currentPoly.points.Add(*intersectionPts);
			currentPoly.points.Add(lastPts);
		}
		else
		{
			// just insert the new point in the current polygone
			currentPoly.points.Add(currentPts);
		}
		previousPts = currentPts;
	}
	polygons.Add(currentPoly);

	// DEBUG
	for (Polygon p : polygons)
	{
		for (Point2D pts : p.points)
		{
			UE_LOG(LogTemp, Log, TEXT("Point of the polygones %s"), *pts.Print());
		}
		UE_LOG(LogTemp, Log, TEXT("======="));
	}
	// END DEBUG


	// For the second wire, create the points and check if it is contained in on of the previous shape
	currentPts = Point2D(0, 0);
	previousPts = Point2D(0, 0);
	int closestLength = -1;
	for (int32 i = 0; i < directionOfSecondWire.Num(); ++i)
	{
		// Create the point
		currentPts = CreateNewPoint(previousPts, directionOfSecondWire[i]);
		UE_LOG(LogTemp, Log, TEXT("Point %s"), *currentPts.Print());

		// Check if it lies inside one of the shape
		Polygon intersectPolygon;
		bool isInShape = InsideShape(currentPts, polygons, intersectPolygon);

		// DEBUG
		/*for (Point2D pts : intersectPolygon.points)
		{
			UE_LOG(LogTemp, Log, TEXT("Point of the final polygones %s"), *pts.Print());
		}
		UE_LOG(LogTemp, Log, TEXT("======="));*/
		// END DEBUG

		UE_LOG(LogTemp, Log, TEXT("isInShape, %d"), isInShape);
		if (isInShape)
		{
			// Compute the intersectionPoint
			FString nextDirection = i < directionOfSecondWire.Num() - 1 ? directionOfSecondWire[i + 1] : "";
			TArray<Point2D> intersectionPts = FindIntersectionPoints(previousPts, currentPts, nextDirection, intersectPolygon);

			for (Point2D pts : intersectionPts)
			{
				UE_LOG(LogTemp, Log, TEXT("intersection %s"), *pts.Print());
			}

			for (Point2D pts : intersectionPts)
			{
				// Find the closest point to return his length
				int newLength = FMath::Abs(pts.x) + FMath::Abs(pts.y);
				if (closestLength == -1 || (closestLength > newLength))
				{
					closestIntersectionPts = pts;
					closestLength = newLength;
				}

				if (currentStepNumber == -1 || pts.cumulatedSteps < currentStepNumber)
				{
					UE_LOG(LogTemp, Log, TEXT("=========== number of step = %d"), pts.cumulatedSteps);
					currentStepNumber = pts.cumulatedSteps;
				}
			}
		}
		previousPts = currentPts;
	}

	stepNumber = currentStepNumber;

	// Compute the length of this point from the origin
	return closestLength;

	//return 0;
}