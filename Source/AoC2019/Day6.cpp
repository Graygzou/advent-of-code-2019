// Fill out your copyright notice in the Description page of Project Settings.


#include "Day6.h"

int UDay6::ComputeDay6(TArray<FString> inputsDependencies)
{
	// We might have many roots
	TArray<AGraphNode*> roots;
	TMap<FString, AGraphNode*> dictionnary;

	for (FString currentOrbit : inputsDependencies)
	{
		FString center;
		FString orbit;
		if(!currentOrbit.Split(")", &center, &orbit))
		{
			UE_LOG(LogTemp, Log, TEXT("Fail parsing the line. Can't find ')' character."));
			return 0;
		}

		// Sanitize both string
		center = center.ReplaceEscapedCharWithChar().Replace((TCHAR*)"\\r", (TCHAR*)"");
		center.TrimEndInline();

		orbit = orbit.ReplaceEscapedCharWithChar().Replace((TCHAR*)"\\r", (TCHAR*)"");
		orbit.TrimEndInline();

		// Debug
		//UE_LOG(LogTemp, Log, TEXT("center  %s"), *center);
		//UE_LOG(LogTemp, Log, TEXT("orbit  %s"), *orbit);
		// end debug

		if (!dictionnary.Contains(center))
		{
			// Add the center if needed
			AGraphNode* node = UDay6::CreateNode(center);
			dictionnary.Add(center, node);

			/*
			if (roots.Num() <= 0)
			{
				UE_LOG(LogTemp, Log, TEXT("dude !"));
				roots.Add(node);
			}*/
		}
		// The center node exist now

		// Create the orbit node
		if (!dictionnary.Contains(orbit))
		{
			// Add the center if needed
			AGraphNode* node = UDay6::CreateNode(orbit);
			dictionnary.Add(orbit, node);
		}
		// The orbtit node exist now

		// Make a relation between the two
		UDay6::AddChildIfNecessary(dictionnary, orbit, center);
	}

	/*
	if (root.Num() > 0)
	{
		DisplayGraph(root[0]);
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("ooops"));
	}*/

	// Find the root element
	TArray<FString> keys;
	dictionnary.GetKeys(keys);
	for(FString key : keys)
	{
		if (dictionnary[key]->parent == NULL)
		{
			roots.Add(dictionnary[key]);
		}
	}

	// Run the computation to find the final result
	int resultPart1 = 0;
	for (AGraphNode* node : roots)
	{
		resultPart1 += ResultPart1(roots[0]);
	}

	int resultPart2 = ResultPart2(dictionnary, "YOU", "SAN");

	return resultPart2;
}

AGraphNode* UDay6::CreateNode(FString name)
{
	// Create a new node for the orbit object
	AGraphNode* currentNode = NewObject<AGraphNode>();
	currentNode->value = name;

	return currentNode;
}


void UDay6::AddChildIfNecessary(TMap<FString, AGraphNode*>& dict, FString orbitName, FString centerName)
{
	// Both node exist now. just need to add one to child of the other
	// Add it to the children of the existing node
	dict[orbitName]->parent = dict[centerName];
	dict[centerName]->children.Add(dict[orbitName]);
}



void UDay6::DisplayGraph(AGraphNode* root)
{
	int currentLevel = 0;
	AGraphNode* currentNode = root;

	TArray<AGraphNode*> nextNodes;
	TArray<int> levels;
	while (currentNode != 0)
	{		
		UE_LOG(LogTemp, Log, TEXT("%s"), *currentNode->DisplayNode(currentLevel));

		// Store the children of the nodes
		if (currentNode->children.Num() > 0)
		{
			nextNodes.Append(currentNode->children);
			for (int i = 0; i < currentNode->children.Num(); ++i)
			{
				levels.Add(currentLevel + 1);
			}
		}

		// Move to the next node
		if (nextNodes.Num() > 0)
		{
			currentNode = nextNodes.Pop();
			currentLevel = levels.Pop();
		}
		else
		{
			currentNode = NULL;
		}
	}
}


int UDay6::ResultPart1(AGraphNode* root)
{
	int total = 0;

	int currentLevel = 0;
	AGraphNode* currentNode = root;

	TArray<AGraphNode*> nextNodes;
	TArray<int> levels;
	while (currentNode != 0)
	{
		total += currentLevel;

		// Store the children of the nodes
		if (currentNode->children.Num() > 0)
		{
			nextNodes.Append(currentNode->children);
			for (int i = 0; i < currentNode->children.Num(); ++i)
			{
				levels.Add(currentLevel + 1);
			}
		}

		// Move to the next node
		if (nextNodes.Num() > 0)
		{
			currentNode = nextNodes.Pop();
			currentLevel = levels.Pop();
		}
		else
		{
			currentNode = NULL;
		}
	}

	return total;
}


/* We just want to find a commun parent from the two nodes */
int UDay6::ResultPart2(TMap<FString, AGraphNode*>& dict, FString starting, FString arrival)
{
	int result;
	TMap<FString, int> nodesChecked;

	int lengthFromStartingPath = 0;
	int lengthFromEndingPathLength = 0;

	AGraphNode* startingPts = dict[starting]->parent;
	AGraphNode* endingPts = dict[arrival]->parent;

	while (startingPts != NULL || endingPts != NULL)
	{
		// Continue the research from the starting point if possible
		if (startingPts != NULL)
		{
			if (nodesChecked.Contains(startingPts->value))
			{
				// DONE !
				result = lengthFromStartingPath + nodesChecked[startingPts->value] - 1;
				break;
			}
			else
			{
				nodesChecked.Add(startingPts->value, ++lengthFromStartingPath);
				startingPts = startingPts->parent;
			}
		}

		// Continue the research from the ending point if possible
		if (endingPts != NULL)
		{
			if (nodesChecked.Contains(endingPts->value))
			{
				// DONE !
				result = lengthFromEndingPathLength + nodesChecked[endingPts->value] - 1;
				break;
			}
			else
			{
				nodesChecked.Add(endingPts->value, ++lengthFromEndingPathLength);
				endingPts = endingPts->parent;
			}
		}
	}

	return result;
}