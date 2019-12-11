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
