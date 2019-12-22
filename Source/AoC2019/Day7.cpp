// Fill out your copyright notice in the Description page of Project Settings.


#include "Day7.h"
#include "Amplifier.h"

#pragma region Helpers
void swap(TArray<int>& combinaison, int index1, int index2)
{
	int tmp = combinaison[index1];
	combinaison[index1] = combinaison[index2];
	combinaison[index2] = tmp;

}
#pragma endregion

#pragma region Part 1
int UDay7::ComputeOneCycle(UPARAM(ref) TArray<FString>& programArray, TArray<int> currentCombinaison, int programInput)
{
	int result = 0;
	for (int i = 0; i < currentCombinaison.Num(); ++i)
	{
		// Reset everything back to normal
		TArray<int> outputs;
		TArray<FString> program = programArray;

		// Call the program
		// TODO Adapt this !
		//Compute(program, TArray<int> { currentCombinaison[i], programInput }, outputs);

		// Update the values
		if (outputs.Num() > 0)
		{
			result = outputs[0];
			// assign the new input 
			programInput = outputs[0];
		}
	}

	return result;
}

// See https://en.wikipedia.org/wiki/Heap%27s_algorithm for more info
int UDay7::FindRightCombinaison(UPARAM(ref) TArray<FString>& programArray, int input, TArray<int> currentCombinaison = TArray<int>{ 0, 1, 2, 3, 4 })
{
	int currentOutput = 0;
	int finalOutput = currentOutput;

	//TArray<int> currentCombinaison = TArray<int>{ 0, 1, 2, 3, 4 };
	//TArray<int> currentCombinaison = combinaison;
	TArray<int> finalCombinaison;

	// Init the stack
	TArray<int> stackState;
	stackState.Init(0, currentCombinaison.Num());

	int stackPointer = 0;
	while (stackPointer < currentCombinaison.Num())
	{
		if (stackState[stackPointer] < stackPointer)
		{
			if (stackPointer % 2 == 0)
			{
				swap(currentCombinaison, 0, stackPointer);
			}
			else
			{
				swap(currentCombinaison, stackState[stackPointer], stackPointer);
			}
			stackState[stackPointer]++;
			stackPointer = 0;

			// Custom execution the program with the current input
			int result = ComputeOneCycle(programArray, currentCombinaison, input);

			if (result > finalOutput)
			{
				finalCombinaison = currentCombinaison;
				finalOutput = result;
			}
			// End Custom
		}
		else
		{
			stackState[stackPointer] = 0;
			stackPointer++;
		}
	}

	FString t;
	for (int i = 0; i < finalCombinaison.Num(); ++i)
	{
		t += FString::FromInt(finalCombinaison[i]);
	}

	UE_LOG(LogTemp, Log, TEXT("DEJA VU %s"), *t);
	return finalOutput;
}
#pragma endregion

#pragma region Part2
int UDay7::ComputeNCycle(UPARAM(ref) TArray<FString> programArray, TArray<int> currentCombinaison, int programInput)
{
	bool done = false;
	int result = 0;

	TArray<FAmplifier> amplifiers;

	// Create 5 Amplifiers
	for (int i = 0; i < currentCombinaison.Num(); ++i)
	{
		amplifiers.Add(FAmplifier(programArray, currentCombinaison[i]));
	}

	int currentAmplifierIndex = 0;
	do
	{
		// Reset everything back to normal
		TArray<int64> outputs;

		// Call the program
		amplifiers[currentAmplifierIndex].Compute(TArray<int64>{programInput}, outputs, 1);

		// Update the values
		if (outputs.Num() > 0)
		{
			result = outputs[0];
			// assign the new input 
			programInput = outputs[0];
		}
		currentAmplifierIndex = ++currentAmplifierIndex % 5;
	} while (!amplifiers[amplifiers.Num() - 1].IsDone());

	return result;
}

int UDay7::FindRightCombinaisonPart2(UPARAM(ref) TArray<FString>& programArray, int input, TArray<int> currentCombinaison = TArray<int>{ 5, 6, 7, 8, 9 })
{
	int currentOutput = 0;
	int finalOutput = currentOutput;
	TArray<int> finalCombinaison;

	// Init the stack
	TArray<int> stackState;
	stackState.Init(0, currentCombinaison.Num());

	FString t;
	for (int i = 0; i < finalCombinaison.Num(); ++i)
	{
		t += FString::FromInt(finalCombinaison[i]);
	}
	UE_LOG(LogTemp, Log, TEXT("========================"));
	UE_LOG(LogTemp, Log, TEXT("Test Combinaison %s"), *t);
	// Custom execution the program with the current input
	int result = ComputeNCycle(programArray, currentCombinaison, input);
	if (result > finalOutput)
	{
		finalCombinaison = currentCombinaison;
		finalOutput = result;
	}
	UE_LOG(LogTemp, Log, TEXT("========================"));
	// End Custom

	int stackPointer = 0;
	while (stackPointer < currentCombinaison.Num())
	{
		if (stackState[stackPointer] < stackPointer)
		{
			if (stackPointer % 2 == 0)
			{
				swap(currentCombinaison, 0, stackPointer);
			}
			else
			{
				swap(currentCombinaison, stackState[stackPointer], stackPointer);
			}
			stackState[stackPointer]++;
			stackPointer = 0;

			t = "";
			for (int i = 0; i < finalCombinaison.Num(); ++i)
			{
				t += FString::FromInt(finalCombinaison[i]);
			}
			UE_LOG(LogTemp, Log, TEXT("========================"));
			UE_LOG(LogTemp, Log, TEXT("Test Combinaison %s"), *t);
			// Custom execution the program with the current input
			int result = ComputeNCycle(programArray, currentCombinaison, input);
			if (result > finalOutput)
			{
				finalCombinaison = currentCombinaison;
				finalOutput = result;
			}
			UE_LOG(LogTemp, Log, TEXT("========================"));
			// End Custom
		}
		else
		{
			stackState[stackPointer] = 0;
			stackPointer++;
		}
	}

	t = "";
	for (int i = 0; i < finalCombinaison.Num(); ++i)
	{
		t += FString::FromInt(finalCombinaison[i]);
	}

	UE_LOG(LogTemp, Log, TEXT("DEJA VU %s"), *t);
	return finalOutput;
}
#pragma endregion