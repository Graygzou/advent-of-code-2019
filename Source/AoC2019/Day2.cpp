// Fill out your copyright notice in the Description page of Project Settings.

#include "Day2.h"


#pragma region Opcodes operations

void UDay2::GetInputBasedOnMode(FOpcode opcode, TMap<int64, FString> programMap, int parameterIndex, int currentBase, int64& res)
{
	res = 0;
	if (opcode.modes.Num() > parameterIndex)
	{
		if (opcode.modes[parameterIndex] == 1)
		{
			res = opcode.input[parameterIndex];
		}
		else if (opcode.modes[parameterIndex] == 2)
		{
			int64 index = currentBase + opcode.input[parameterIndex];
			if (programMap.Contains(index))
			{
				res = FCString::Atoi64(*programMap[index]);
			}
			else
			{
				res = 0;
			}
		}
		else // We assume it's in 0 mode aka position mode
		{
			if (programMap.Contains(opcode.input[parameterIndex]))
			{
				res = FCString::Atoi64(*programMap[opcode.input[parameterIndex]]);
			}
			else
			{
				res = 0;
			}
		}
	}
	else
	{
		if (programMap.Contains(opcode.input[parameterIndex]))
		{
			res = FCString::Atoi64(*programMap[opcode.input[parameterIndex]]);
		}
		else
		{
			res = 0;
		}
	}
}

void UDay2::GetOutputBasedOnMode(FOpcode opcode, int parameterIndex, int currentBase, int64& res)
{
	if (opcode.modes.Num() > parameterIndex && opcode.modes[parameterIndex] == 2)
	{
		res = currentBase + opcode.output[0];
	}
	else
	{
		res = opcode.output[0];
	}
}

void UDay2::RelativeBaseOffset(FOpcode opcode, TMap<int64, FString>& programMap, int& relativeBase)
{
	// Use the mode here
	//int input1 = opcode.modes.Num() > 0 && opcode.modes[0] ? opcode.input[0] : FCString::Atoi64(*programMap[opcode.input[0]]);
	int64 input1;
	GetInputBasedOnMode(opcode, programMap, 0, relativeBase, input1);

	// Apply the operation
	relativeBase += input1;
}


void UDay2::ComputeIfShouldJump(FOpcode opcode, TMap<int64, FString>& programMap, int& index, bool isPositive, int currentBase)
{
	// Simple check to avoid crashes
	if (opcode.input.Num() < 2)
	{
		UE_LOG(LogTemp, Log, TEXT("can't execute multiplication because the number of inputs or output is not suffisant."));
		return;
	}

	// Use the mode here
	int64 input1;
	int64 input2;
	GetInputBasedOnMode(opcode, programMap, 0, currentBase, input1); //opcode.modes.Num() > 0 && opcode.modes[0] ? opcode.input[0] : FCString::Atoi(*programArray[opcode.input[0]]);
	GetInputBasedOnMode(opcode, programMap, 1, currentBase, input2);  //opcode.modes.Num() > 1 && opcode.modes[1] ? opcode.input[1] : FCString::Atoi(*programArray[opcode.input[1]]);

	if (isPositive && input1 != 0 || !isPositive && !input1)
	{
		index = input2;
	}
	else
	{
		index += 3;
	}
}

void UDay2::JumpIfTrue(FOpcode opcode, TMap<int64, FString>& programMap, int& index, int currentBase)
{
	ComputeIfShouldJump(opcode, programMap, index, true, currentBase);
}

void UDay2::JumpIfFalse(FOpcode opcode, TMap<int64, FString>& programMap, int& index, int currentBase)
{
	ComputeIfShouldJump(opcode, programMap, index, false, currentBase);
}

void UDay2::ComputeIsLessThan(FOpcode opcode, TMap<int64, FString>& programMap, int currentBase)
{
	// Use the mode here
	int64 input1;
	int64 input2;
	GetInputBasedOnMode(opcode, programMap, 0, currentBase, input1); //opcode.modes.Num() > 0 && opcode.modes[0] ? opcode.input[0] : FCString::Atoi((opcode.modes.Num() > 0 && opcode.modes[0] == 2 ? *programArray[opcode.input[currentBase]] : *programArray[opcode.input[0]]));
	GetInputBasedOnMode(opcode, programMap, 1, currentBase, input2);

	// Right now "Parameters that an instruction writes to will never be in immediate mode"
	int64 res;
	GetOutputBasedOnMode(opcode, 2, currentBase, res);
	programMap.Add(res, input1 < input2 ? FString::FromInt(1) : FString::FromInt(0));
}

void UDay2::ComputeIsEquals(FOpcode opcode, TMap<int64, FString>& programMap, int currentBase)
{
	// Use the mode here
	int64 input1;
	int64 input2;
	GetInputBasedOnMode(opcode, programMap, 0, currentBase, input1);  //opcode.modes.Num() > 0 && opcode.modes[0] ? opcode.input[0] : FCString::Atoi(*programArray[opcode.input[0]]);
	GetInputBasedOnMode(opcode, programMap, 1, currentBase, input2);  //opcode.modes.Num() > 1 && opcode.modes[1] ? opcode.input[1] : FCString::Atoi(*programArray[opcode.input[1]]);

	// Right now "Parameters that an instruction writes to will never be in immediate mode"
	int64 res;
	GetOutputBasedOnMode(opcode, 2, currentBase, res);
	programMap.Add(res, input1 == input2 ? FString::FromInt(1) : FString::FromInt(0));
}


void UDay2::StoreInputValue(FOpcode opcode, TMap<int64, FString>& programMap, int currentBase)
{

	int64 value;
	GetOutputBasedOnMode(opcode, 0, currentBase, value);
	/*
	if (opcode.modes.Num() > 0 && opcode.modes[0] == 2)
	{
		value = currentBase + opcode.output[0];
	}
	else
	{
		value = opcode.output[0];
	}*/
	/*int64 value;
	GetInputBasedOnMode(opcode, programMap, 0, currentBase, value);*/
	
	// Right now "Parameters that an instruction writes to will never be in immediate mode"
	char* temp[30];
	sprintf(*temp, "%llu", opcode.input[0]);
	programMap.Add(value, FString(*temp));
	
}

void UDay2::OutputValue(FOpcode opcode, TMap<int64, FString>& programMap, TArray<int64>& outputs, int currentBase)
{
	int64 value;
	GetInputBasedOnMode(opcode, programMap, 0, currentBase, value);  //opcode.modes.Num() > 0 && opcode.modes[0] ? opcode.input[0] : FCString::Atoi(*programArray[opcode.input[0]]);

	// Add the value to the outputs array
	outputs.Add(value);

	UE_LOG(LogTemp, Log, TEXT("OUTPUT = %d"), value);
}


// Day 2		
FOpcode UDay2::CreateOpcode(int code, TArray<int64> inputs, TArray<int64> outputs, TArray<int> modes)
{
	return FOpcode(code, inputs, outputs, modes);
}


void UDay2::ComputeMultiplication(FOpcode opcode, TMap<int64, FString>& programMap, int currentBase)
{
	// Simple check to avoid crashes
	if (opcode.input.Num() < 2 || opcode.output.Num() < 1)
	{
		UE_LOG(LogTemp, Log, TEXT("can't execute multiplication because the number of inputs or output is not suffisant."));
		return;
	}

	// Use the mode here
	int64 input1;
	int64 input2;
	GetInputBasedOnMode(opcode, programMap, 0, currentBase, input1);  //opcode.modes.Num() > 0 && opcode.modes[0] ? opcode.input[0] : FCString::Atoi(*programArray[opcode.input[0]]);
	GetInputBasedOnMode(opcode, programMap, 1, currentBase, input2);  //opcode.modes.Num() > 1 && opcode.modes[1] ? opcode.input[1] : FCString::Atoi(*programArray[opcode.input[1]]);
	int64 result = input1 * input2;

	// Right now "Parameters that an instruction writes to will never be in immediate mode"
	char temp[30];
	sprintf(temp, "%llu", result);

	int64 res;
	GetOutputBasedOnMode(opcode, 2, currentBase, res);
	programMap.Add(res, FString(temp));
}


void UDay2::ComputeAddition(FOpcode opcode, TMap<int64, FString>& programMap, int currentBase)
{
	// Simple check to avoid crashes
	if (opcode.input.Num() < 2 || opcode.output.Num() < 1)
	{
		UE_LOG(LogTemp, Log, TEXT("can't execute addition because the number of inputs or output is not suffisant."));
		return;
	}

	// Use the mode here
	int64 input1;
	int64 input2;
	GetInputBasedOnMode(opcode, programMap, 0, currentBase, input1);  //opcode.modes.Num() > 0 && opcode.modes[0] ? opcode.input[0] : FCString::Atoi(*programArray[opcode.input[0]]);
	GetInputBasedOnMode(opcode, programMap, 1, currentBase, input2);  //opcode.modes.Num() > 1 && opcode.modes[1] ? opcode.input[1] : FCString::Atoi(*programArray[opcode.input[1]]);
	int64 result = input1 + input2;

	// Right now "Parameters that an instruction writes to will never be in immediate mode"
	char temp[30];
	sprintf(temp, "%llu", result);
	int64 res;
	GetOutputBasedOnMode(opcode, 2, currentBase, res);
	programMap.Add(res, FString(temp));
	//programMap.Add(opcode.output[0], FString::FromInt(result));
}
#pragma endregion

void UDay2::Compute(UPARAM(ref) TArray<FString>& programArray, TArray<int64> input, TArray<int64>& outputs, bool& finished)
{
	bool done = false;
	int pointerIndex = 0;
	int currentInputIndex = 0;
	int currentBase = 0;

	// Transform array into a map
	int initSize = programArray.Num();
	TMap<int64, FString> programMap;

	for (int i = 0; i < programArray.Num(); i++)
	{
		programMap.Add(i, programArray[i]);
	}

	while(pointerIndex < initSize && !done)
	{
		FString operationCodeStr = programMap[pointerIndex].Reverse(); //FCString::Atoi(*programArray[currentIndex]);
		
		// Real opcode in a string (2 first numbers because we reversed the string)
		FString o("");
		for (int i = 0; i < operationCodeStr.Len() && i < 2; ++i)
		{
			o += operationCodeStr[i];
		}
		int operationCode = FCString::Atoi64(*o.Reverse());

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
					opcode = CreateOpcode(operationCode, TArray<int64> {
						FCString::Atoi64(*programMap[pointerIndex+1]),
						FCString::Atoi64(*programMap[pointerIndex+2]),
					}, TArray<int64> {
						FCString::Atoi64(*programMap[pointerIndex+3]),
					}, modes);
					if (operationCode == 1)
					{
						ComputeAddition(opcode, programMap, currentBase);
					}
					else
					{
						ComputeMultiplication(opcode, programMap, currentBase);
					}
					// Skip next 4 numbers
					pointerIndex += 4;
					break;
				case 3:	// Read Input
					opcode = CreateOpcode(operationCode, TArray<int64> {
						input[currentInputIndex],
					}, TArray<int64> {
						FCString::Atoi64(*programMap[pointerIndex + 1]),
					}, modes);

					StoreInputValue(opcode, programMap, currentBase);

					if (currentInputIndex < input.Num() - 1)
					{
						currentInputIndex++;
					}

					// Skip next 2 numbers
					pointerIndex += 2;
					break;
				case 4: // Output
					opcode = CreateOpcode(operationCode, TArray<int64> {
						FCString::Atoi64(*programMap[pointerIndex + 1]),
					}, TArray<int64>(), modes);

					OutputValue(opcode, programMap, outputs, currentBase);

					// Skip next 2 numbers
					pointerIndex += 2;
					break;
				case 5: // jump if true
				case 6: // jump if false
					opcode = CreateOpcode(operationCode, TArray<int64> {
						FCString::Atoi64(*programMap[pointerIndex + 1]),
						FCString::Atoi64(*programMap[pointerIndex + 2]),
					}, TArray<int64>(), modes);

					if (operationCode == 5)
					{
						JumpIfTrue(opcode, programMap, pointerIndex, currentBase);
					}
					else
					{
						JumpIfFalse(opcode, programMap, pointerIndex, currentBase);
					}

					break;
				case 7: // less then
				case 8: // equals
					opcode = CreateOpcode(operationCode, TArray<int64> {
						FCString::Atoi64(*programMap[pointerIndex + 1]),
						FCString::Atoi64(*programMap[pointerIndex + 2]),
					}, TArray<int64> {
						FCString::Atoi64(*programMap[pointerIndex + 3]),
					}, modes);

					if (operationCode == 7)
					{
						ComputeIsLessThan(opcode, programMap, currentBase);
					}
					else
					{
						ComputeIsEquals(opcode, programMap, currentBase);
					}

					// Skip next 4 numbers
					pointerIndex += 4;
					break;
				case 9:
					opcode = CreateOpcode(operationCode, TArray<int64> {
						FCString::Atoi64(*programMap[pointerIndex + 1]),
					}, TArray<int64>(), modes);

					RelativeBaseOffset(opcode, programMap, currentBase);

					// Skip next 2 numbers
					pointerIndex += 2;
					break;
				case 99:
					// HALT
					done = true;
					break;
				default:
					UE_LOG(LogTemp, Log, TEXT("wtf is that = %d ?"), operationCode);
					done = true;
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
	finished = done;
}