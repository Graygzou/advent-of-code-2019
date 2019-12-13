// Fill out your copyright notice in the Description page of Project Settings.


#include "Amplifier.h"
#include "Opcode.h"


FAmplifier::FAmplifier()
{

}

FAmplifier::FAmplifier(TArray<FString> instructions, int inputSetting) : InstructionPointer(0)
{
	this->inputSetting = inputSetting;
	this->instructions = instructions;
}

FAmplifier::~FAmplifier()
{

}

#pragma region Opcodes operations
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

void JumpIfTrue(FOpcode opcode, TArray<FString>& programArray, int& index)
{
	ComputeIfShouldJump(opcode, programArray, index, true);
}

void JumpIfFalse(FOpcode opcode, TArray<FString>& programArray, int& index)
{
	ComputeIfShouldJump(opcode, programArray, index, false);
}

void ComputeIsLessThan(FOpcode opcode, TArray<FString>& programArray)
{
	// Use the mode here
	int input1 = opcode.modes.Num() > 0 && opcode.modes[0] ? opcode.input[0] : FCString::Atoi(*programArray[opcode.input[0]]);
	int input2 = opcode.modes.Num() > 1 && opcode.modes[1] ? opcode.input[1] : FCString::Atoi(*programArray[opcode.input[1]]);

	// Right now "Parameters that an instruction writes to will never be in immediate mode"
	programArray[opcode.output[0]] = input1 < input2 ? FString::FromInt(1) : FString::FromInt(0);
}

void ComputeIsEquals(FOpcode opcode, TArray<FString>& programArray)
{
	// Use the mode here
	int input1 = opcode.modes.Num() > 0 && opcode.modes[0] ? opcode.input[0] : FCString::Atoi(*programArray[opcode.input[0]]);
	int input2 = opcode.modes.Num() > 1 && opcode.modes[1] ? opcode.input[1] : FCString::Atoi(*programArray[opcode.input[1]]);

	// Right now "Parameters that an instruction writes to will never be in immediate mode"
	programArray[opcode.output[0]] = input1 == input2 ? FString::FromInt(1) : FString::FromInt(0);
}


void StoreInputValue(FOpcode opcode, TArray<FString>& programArray)
{
	//int value = opcode.modes.Num() > 0 && opcode.modes[0] ? opcode.input[0] : FCString::Atoi(*programArray[opcode.input[0]]);

	// Right now "Parameters that an instruction wri	tes to will never be in immediate mode"
	programArray[opcode.output[0]] = FString::FromInt(opcode.input[0]);
}

void OutputValue(FOpcode opcode, TArray<FString>& programArray, TArray<int>& outputs)
{
	int value = opcode.modes.Num() > 0 && opcode.modes[0] ? opcode.input[0] : FCString::Atoi(*programArray[opcode.input[0]]);

	// Add the value to the outputs array
	outputs.Add(value);

	UE_LOG(LogTemp, Log, TEXT("OUTPUT = %d"), value);
}

/*==================*/
/*		Day 2		*/
/*==================*/
FOpcode CreateOpcode(int code, TArray<int> inputs, TArray<int> outputs, TArray<int> modes)
{
	return FOpcode(code, inputs, outputs, modes);
}


void ComputeMultiplication(FOpcode opcode, TArray<FString>& programArray)
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


void ComputeAddition(FOpcode opcode, TArray<FString>& programArray)
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

void FAmplifier::Compute(int currentInput, TArray<int>& outputs)
{
	bool hasOutputs = false;
	int currentInputIndex = 0;

	while (this->InstructionPointer < this->instructions.Num() && !this->isDone && !hasOutputs)
	{
		FString operationCodeStr = instructions[this->InstructionPointer].Reverse(); //FCString::Atoi(*programArray[currentIndex]);

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
					FCString::Atoi(*this->instructions[this->InstructionPointer + 1]),
					FCString::Atoi(*this->instructions[this->InstructionPointer + 2]),
				}, TArray<int> {
					FCString::Atoi(*this->instructions[this->InstructionPointer + 3]),
				}, modes);
				if (operationCode == 1)
				{
					ComputeAddition(opcode, this->instructions);
				}
				else
				{
					ComputeMultiplication(opcode, this->instructions);
				}
				// Skip next 4 numbers
				this->InstructionPointer += 4;
				break;
			case 3:	// Read Input
				if (!hasReadSettings)
				{
					this->hasReadSettings = true;
					opcode = CreateOpcode(operationCode, TArray<int> {
						inputSetting,
					}, TArray<int> {
						FCString::Atoi(*this->instructions[this->InstructionPointer + 1]),
					}, modes);
				}
				else
				{
					opcode = CreateOpcode(operationCode, TArray<int> {
						currentInput,
					}, TArray<int> {
						FCString::Atoi(*this->instructions[this->InstructionPointer + 1]),
					}, modes);
				}

				StoreInputValue(opcode, this->instructions);

				// Skip next 2 numbers
				this->InstructionPointer += 2;
				break;
			case 4: // Output
				opcode = CreateOpcode(operationCode, TArray<int> {
					FCString::Atoi(*this->instructions[this->InstructionPointer + 1]),
				}, TArray<int>(), modes);

				OutputValue(opcode, this->instructions, outputs);

				// SUPSEND FOR NOW
				hasOutputs = true;

				// Skip next 2 numbers
				this->InstructionPointer += 2;
				break;
			case 5: // jump if true
			case 6: // jump if false
				opcode = CreateOpcode(operationCode, TArray<int> {
					FCString::Atoi(*this->instructions[this->InstructionPointer + 1]),
					FCString::Atoi(*this->instructions[this->InstructionPointer + 2]),
				}, TArray<int>(), modes);

				if (operationCode == 5)
				{
					JumpIfTrue(opcode, this->instructions, this->InstructionPointer);
				}
				else
				{
					JumpIfFalse(opcode, this->instructions, this->InstructionPointer);
				}

				break;
			case 7: // less then
			case 8: // equals
				opcode = CreateOpcode(operationCode, TArray<int> {
					FCString::Atoi(*this->instructions[this->InstructionPointer + 1]),
					FCString::Atoi(*this->instructions[this->InstructionPointer + 2]),
				}, TArray<int> {
					FCString::Atoi(*this->instructions[this->InstructionPointer + 3]),
				}, modes);

				if (operationCode == 7)
				{
					ComputeIsLessThan(opcode, this->instructions);
				}
				else
				{
					ComputeIsEquals(opcode, this->instructions);
				}

				// Skip next 4 numbers
				this->InstructionPointer += 4;
				break;
			case 99:
				// HALT
				this->isDone = true;
				break;
			default:
				UE_LOG(LogTemp, Log, TEXT("wtf is that = %d ?"), operationCode);
				this->InstructionPointer++;
				break;
			}
			//opcode.Print();
		}
		else
		{
			// just leave the result unchanged
			this->isDone = true;
		}
	}

	if (this->InstructionPointer >= this->instructions.Num())
	{
		this->isDone = true;
	}
}

bool FAmplifier::IsDone()
{
	return isDone;
}

void FAmplifier::Print()
{
	// TODO ?
	//UE_LOG(LogTemp, Log, TEXT("%s"), *result);
}