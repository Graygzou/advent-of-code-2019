// Fill out your copyright notice in the Description page of Project Settings.

#include "Day2.h"


#pragma region Opcodes operations
void UDay2::ComputeIfShouldJump(FOpcode opcode, TArray<FString>& programArray, int& index, bool isPositive)
{
	// Simple check to avoid crashes
	if (opcode.input.Num() < 2)
	{
		UE_LOG(LogTemp, Log, TEXT("can't execute multiplication because the number of inputs or output is not suffisant."));
		return;
	}

	// Use the mode here
	int input1 = opcode.modes.Num() > 0 && opcode.modes[0] ? opcode.input[0] : FCString::Atoi(*programArray[opcode.input[0]]);
	int input2 = opcode.modes.Num() > 1 && opcode.modes[1] ? opcode.input[1] : FCString::Atoi(*programArray[opcode.input[1]]);

	if (isPositive && input1 != 0 || !isPositive && !input1)
	{
		index = input2;
	}
	else
	{
		index += 3;
	}
}

void UDay2::JumpIfTrue(FOpcode opcode, TArray<FString>& programArray, int& index)
{
	ComputeIfShouldJump(opcode, programArray, index, true);
}

void UDay2::JumpIfFalse(FOpcode opcode, TArray<FString>& programArray, int& index)
{
	ComputeIfShouldJump(opcode, programArray, index, false);
}

void UDay2::ComputeIsLessThan(FOpcode opcode, TArray<FString>& programArray)
{
	// Use the mode here
	int input1 = opcode.modes.Num() > 0 && opcode.modes[0] ? opcode.input[0] : FCString::Atoi(*programArray[opcode.input[0]]);
	int input2 = opcode.modes.Num() > 1 && opcode.modes[1] ? opcode.input[1] : FCString::Atoi(*programArray[opcode.input[1]]);

	// Right now "Parameters that an instruction writes to will never be in immediate mode"
	programArray[opcode.output[0]] = input1 < input2 ? FString::FromInt(1) : FString::FromInt(0);
}

void UDay2::ComputeIsEquals(FOpcode opcode, TArray<FString>& programArray)
{
	// Use the mode here
	int input1 = opcode.modes.Num() > 0 && opcode.modes[0] ? opcode.input[0] : FCString::Atoi(*programArray[opcode.input[0]]);
	int input2 = opcode.modes.Num() > 1 && opcode.modes[1] ? opcode.input[1] : FCString::Atoi(*programArray[opcode.input[1]]);

	// Right now "Parameters that an instruction writes to will never be in immediate mode"
	programArray[opcode.output[0]] = input1 == input2 ? FString::FromInt(1) : FString::FromInt(0);
}


void UDay2::StoreInputValue(FOpcode opcode, TArray<FString>& programArray)
{
	//int value = opcode.modes.Num() > 0 && opcode.modes[0] ? opcode.input[0] : FCString::Atoi(*programArray[opcode.input[0]]);

	// Right now "Parameters that an instruction wri	tes to will never be in immediate mode"
	programArray[opcode.output[0]] = FString::FromInt(opcode.input[0]);
}

void UDay2::OutputValue(FOpcode opcode, TArray<FString>& programArray, TArray<int>& outputs)
{
	int value = opcode.modes.Num() > 0 && opcode.modes[0] ? opcode.input[0] : FCString::Atoi(*programArray[opcode.input[0]]);

	// Add the value to the outputs array
	outputs.Add(value);

	UE_LOG(LogTemp, Log, TEXT("OUTPUT = %d"), value);
}


// Day 2		
FOpcode UDay2::CreateOpcode(int code, TArray<int> inputs, TArray<int> outputs, TArray<int> modes)
{
	return FOpcode(code, inputs, outputs, modes);
}


void UDay2::ComputeMultiplication(FOpcode opcode, TArray<FString>& programArray)
{
	// Simple check to avoid crashes
	if (opcode.input.Num() < 2 || opcode.output.Num() < 1)
	{
		UE_LOG(LogTemp, Log, TEXT("can't execute multiplication because the number of inputs or output is not suffisant."));
		return;
	}

	// Use the mode here
	int input1 = opcode.modes.Num() > 0 && opcode.modes[0] ? opcode.input[0] : FCString::Atoi(*programArray[opcode.input[0]]);
	int input2 = opcode.modes.Num() > 1 && opcode.modes[1] ? opcode.input[1] : FCString::Atoi(*programArray[opcode.input[1]]);
	int result = input1 * input2;

	// Right now "Parameters that an instruction writes to will never be in immediate mode"
	programArray[opcode.output[0]] = FString::FromInt(result);
}


void UDay2::ComputeAddition(FOpcode opcode, TArray<FString>& programArray)
{
	// Simple check to avoid crashes
	if (opcode.input.Num() < 2 || opcode.output.Num() < 1)
	{
		UE_LOG(LogTemp, Log, TEXT("can't execute addition because the number of inputs or output is not suffisant."));
		return;
	}

	// Use the mode here
	int input1 = opcode.modes.Num() > 0 && opcode.modes[0] ? opcode.input[0] : FCString::Atoi(*programArray[opcode.input[0]]);
	int input2 = opcode.modes.Num() > 1 && opcode.modes[1] ? opcode.input[1] : FCString::Atoi(*programArray[opcode.input[1]]);
	int result = input1 + input2;

	// Right now "Parameters that an instruction writes to will never be in immediate mode"
	programArray[opcode.output[0]] = FString::FromInt(result);
}
#pragma endregion

void UDay2::Compute(UPARAM(ref) TArray<FString>& programArray, TArray<int> input, TArray<int>& outputs)
{
	bool done = false;
	int currentIndex = 0;
	int currentInputIndex = 0;

	while(currentIndex < programArray.Num() && !done)
	{
		FString operationCodeStr = programArray[currentIndex].Reverse(); //FCString::Atoi(*programArray[currentIndex]);
		
		// Real opcode in a string (2 first numbers because we reversed the string)
		FString o("");
		for (int i = 0; i < operationCodeStr.Len() && i < 2; ++i)
		{
			o += operationCodeStr[i];
		}
		int operationCode = FCString::Atoi(*o.Reverse());

		// Gather all the modes available (The rest of the string
		TArray<int> modes;
		for (int i = 2; i < operationCodeStr.Len(); ++i)
		{
			modes.Add(FChar::ConvertCharDigitToInt(operationCodeStr[i]));
		}

		FOpcode opcode;
		if (operationCode != 99)
		{
			switch (operationCode)
			{
				case 1:	// Addition
				case 2:	// Multiplication
					opcode = CreateOpcode(operationCode, TArray<int> {
						FCString::Atoi(*programArray[currentIndex+1]),
						FCString::Atoi(*programArray[currentIndex+2]),
					}, TArray<int> {
						FCString::Atoi(*programArray[currentIndex+3]),
					}, modes);
					if (operationCode == 1)
					{
						ComputeAddition(opcode, programArray);
					}
					else
					{
						ComputeMultiplication(opcode, programArray);
					}
					// Skip next 4 numbers
					currentIndex += 4;
					break;
				case 3:	// Read Input
					opcode = CreateOpcode(operationCode, TArray<int> {
						input[currentInputIndex],
					}, TArray<int> {
						FCString::Atoi(*programArray[currentIndex + 1]),
					}, modes);

					StoreInputValue(opcode, programArray);

					if (currentInputIndex < input.Num() - 1)
					{
						currentInputIndex++;
					}

					// Skip next 2 numbers
					currentIndex += 2;
					break;
				case 4: // Output
					opcode = CreateOpcode(operationCode, TArray<int> {
						FCString::Atoi(*programArray[currentIndex + 1]),
					}, TArray<int>(), modes);

					OutputValue(opcode, programArray, outputs);

					// Skip next 2 numbers
					currentIndex += 2;
					break;
				case 5: // jump if true
				case 6: // jump if false
					opcode = CreateOpcode(operationCode, TArray<int> {
						FCString::Atoi(*programArray[currentIndex + 1]),
						FCString::Atoi(*programArray[currentIndex + 2]),
					}, TArray<int>(), modes);

					if (operationCode == 5)
					{
						JumpIfTrue(opcode, programArray, currentIndex);
					}
					else
					{
						JumpIfFalse(opcode, programArray, currentIndex);
					}

					break;
				case 7: // less then
				case 8: // equals
					opcode = CreateOpcode(operationCode, TArray<int> {
						FCString::Atoi(*programArray[currentIndex + 1]),
						FCString::Atoi(*programArray[currentIndex + 2]),
					}, TArray<int> {
						FCString::Atoi(*programArray[currentIndex + 3]),
					}, modes);

					if (operationCode == 7)
					{
						ComputeIsLessThan(opcode, programArray);
					}
					else
					{
						ComputeIsEquals(opcode, programArray);
					}

					// Skip next 4 numbers
					currentIndex += 4;
					break;
				case 99:
					// HALT
					done = true;
					break;
				default:
					UE_LOG(LogTemp, Log, TEXT("wtf is that = %d ?"), operationCode);
					currentIndex++;
					break;
			}
			opcode.Print();
		}
		else
		{
			// just leave the result unchanged
			done = true;
		}
	}
}

/*
void swap(TArray<int>& combinaison, int index1, int index2)
{
	int tmp = combinaison[index1];
	combinaison[index1] = combinaison[index2];
	combinaison[index2] = tmp;

}

int UDay2::ComputeOneCycle(UPARAM(ref) TArray<FString>& programArray, TArray<int> currentCombinaison, int programInput)
{
	int result = 0;
	for (int i = 0; i < currentCombinaison.Num(); ++i)
	{
		// Reset everything back to normal
		TArray<int> outputs;
		TArray<FString> program = programArray;

		// Call the program
		Compute(program, TArray<int> { currentCombinaison[i], programInput }, outputs);

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

int UDay2::ComputeNCycle(UPARAM(ref) TArray<FString>& programArray, TArray<int> currentCombinaison, int programInput)
{
	bool done = false;
	int result = 0;

	TArray<FAmplifier> amplifiers;

	// Create 5 Amplifiers
	for (int i = 0; i < currentCombinaison.Num(); ++i)
	{
		amplifiers.Add(FAmplifier(programArray, i));
	}

	int currentAmplifierIndex = 0;
	do
	{
		// Reset everything back to normal
		TArray<int> outputs;

		// Call the program
		amplifiers[currentAmplifierIndex].Compute(programInput, outputs);

		// Update the values
		if (outputs.Num() > 0)
		{
			result = outputs[0];
			// assign the new input 
			programInput = outputs[0];
			currentAmplifierIndex++;
		}
	} while (!amplifiers[amplifiers.Num() - 1].IsDone());

	return result;
}

// See https://en.wikipedia.org/wiki/Heap%27s_algorithm for more info
int UDay2::FindRightCombinaison(UPARAM(ref) TArray<FString>& programArray, int input, TArray<int> currentCombinaison = TArray<int>{ 0, 1, 2, 3, 4 })
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
			
			//int programInput = input;

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

int UDay2::FindRightCombinaisonPart2(UPARAM(ref) TArray<FString>& programArray, int input, TArray<int> currentCombinaison = TArray<int>{ 5, 6, 7, 8, 9 })
{
	int currentOutput = 0;
	int finalOutput = currentOutput;
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
			int result = ComputeNCycle(programArray, currentCombinaison, input);
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
}*/