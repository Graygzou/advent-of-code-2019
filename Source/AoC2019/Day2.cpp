// Fill out your copyright notice in the Description page of Project Settings.

#include "Day2.h"


void ComputeIfShouldJump(FOpcode opcode, TArray<FString>& programArray, int& index, bool isPositive)
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

void UDay2::OutputValue(FOpcode opcode, TArray<FString>& programArray)
{
	int value = opcode.modes.Num() > 0 && opcode.modes[0] ? opcode.input[0] : FCString::Atoi(*programArray[opcode.input[0]]);
	UE_LOG(LogTemp, Log, TEXT("OUTPUT = %d"), value);
}

/*==================*/
/*		Day 2		*/
/*==================*/
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


void UDay2::Compute(UPARAM(ref) TArray<FString>& programArray, int input)
{
	bool done = false;
	int currentIndex = 0;

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
						input,
					}, TArray<int> {
						FCString::Atoi(*programArray[currentIndex + 1]),
					}, modes);

					StoreInputValue(opcode, programArray);

					// Skip next 2 numbers
					currentIndex += 2;
					break;
				case 4: // Output
					opcode = CreateOpcode(operationCode, TArray<int> {
						FCString::Atoi(*programArray[currentIndex + 1]),
					}, TArray<int>(), modes);

					OutputValue(opcode, programArray);

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

			// Debug
			/*
			UE_LOG(LogTemp, Log, TEXT(", %d"), opcode.code);
			for (int j = 0; j < opcode.input.Num(); j++)
			{
				UE_LOG(LogTemp, Log, TEXT(", %d"), opcode.input[j]);
			}
			for (int j = 0; j < opcode.output.Num(); j++)
			{
				UE_LOG(LogTemp, Log, TEXT(", %d"), opcode.output[j]);
			}
			UE_LOG(LogTemp, Log, TEXT("Array length, %d"), programArray.Num());
			*/
			// End Debug
		}
		else
		{
			// just leave the result unchanged
			done = true;
		}
	}

	//if (currentIndex > 0 && currentIndex < programArray.Num()) {
	//	int operationCode = FCString::Atoi(*programArray[currentIndex]);
	//	if (operationCode != 99) {

	//		Opcode opcode{
	//			operationCode,
	//			FCString::Atoi(*programArray[++currentIndex]),
	//			FCString::Atoi(*programArray[++currentIndex]),
	//			FCString::Atoi(*programArray[++currentIndex]),
	//		};
	//		UE_LOG(LogTemp, Log, TEXT(", %d"), opcode.code);
	//		UE_LOG(LogTemp, Log, TEXT(", %d"), opcode.firstInput);
	//		UE_LOG(LogTemp, Log, TEXT(", %d"), opcode.secondInput);
	//		UE_LOG(LogTemp, Log, TEXT(", %d"), opcode.output);
	//		UE_LOG(LogTemp, Log, TEXT("Array length, %d"), programArray.Num());
	//		if (opcode.code == 1)
	//		{
	//			// Addition
	//			int result = FCString::Atoi(*programArray[opcode.firstInput]) + FCString::Atoi(*programArray[opcode.secondInput]);
	//			programArray[opcode.output] = FString::FromInt(result);
	//		}
	//		else if (opcode.code == 2)
	//		{
	//			// Product
	//			//int result = FCString::Atoi(*programArray[opcode.firstInput]) * FCString::Atoi(*programArray[opcode.secondInput]);
	//			//programArray[opcode.output] = FString::FromInt(result);
	//		}
	//	}
	//}
	//else
	//{
	//	UE_LOG(LogTemp, Log, TEXT("Array length, %d and index %d"), programArray.Num(), currentIndex);
	//}
}
