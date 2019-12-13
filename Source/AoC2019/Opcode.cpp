// Fill out your copyright notice in the Description page of Project Settings.


#include "Opcode.h"


FOpcode::FOpcode()
{

}

FOpcode::FOpcode(int code, TArray<int> inputs, TArray<int> outputs, TArray<int> modes) : code(code)
{
	this->input = inputs;
	this->output = outputs;
	this->modes = modes;
}

FOpcode::~FOpcode()
{
}

FString GetInputStr(FOpcode* opcode, int index)
{
	return ((opcode->modes.Num() > index && opcode->modes[index]) ? "" : "[") + FString::FromInt(opcode->input[index]) + ((opcode->modes.Num() > index&& opcode->modes[index]) ? "" : "]");
}

void FOpcode::Print()
{
	FString result("");
	switch (this->code)
	{
	case 1:
		result = "[" + FString::FromInt(output[0]) + "] = " + GetInputStr(this, 0) + " + " + GetInputStr(this, 1) + ";";
		break;
	case 2:
		result = "[" + FString::FromInt(output[0]) + "] = " + GetInputStr(this, 0) + " * " + GetInputStr(this, 1) + ";";
		break;
	case 3:
		result = "[" + FString::FromInt(output[0]) + "] = " + GetInputStr(this, 0) + ";";
		break;
	case 4:
		result = "print(" + GetInputStr(this, 0) + ");";
		break;
	case 5:
		result = "if (" + GetInputStr(this, 0) + " != 0) then goto " + GetInputStr(this, 1) + ";";
		break;
	case 6:
		result = "if (" + GetInputStr(this, 0) + " == 0) then goto " + GetInputStr(this, 1) + ";";
		break;
	case 7:
		result = "if ( " + GetInputStr(this, 0) + " < " + GetInputStr(this, 1) + ") then [" + FString::FromInt(output[0]) + "] = 1 else [" + FString::FromInt(output[0]) + "] = 0;";
		break;
	case 8:
		result = "if ( " + GetInputStr(this, 0) + " == " + GetInputStr(this, 1) + ") then [" + FString::FromInt(output[0]) + "] = 1 else [" + FString::FromInt(output[0]) + "] = 0;";
		break;
	default:
		break;
	}
	UE_LOG(LogTemp, Log, TEXT("%s"), *result);
}