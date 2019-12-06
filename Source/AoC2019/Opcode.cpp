// Fill out your copyright notice in the Description page of Project Settings.

#include "Opcode.h"

struct Opcode
{
	int code;
	int firstInput;
	int secondInput;
	int output;
};

//UOpcode::UOpcode()
//{
//	//UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject);
//	UOpcode* tempObject = NewObject<UOpcode>();
//}

void UOpcode::compute(TArray<FString>& programArray)
{
	bool done = false;
	for (int32 i = 0; !done && i < programArray.Num() / 4; ++i)
	{
		int32 realIndex = i * 4;
		if (programArray.Num() >= realIndex + 4)
		{
			// This is a real opcode
			int operationCode = FCString::Atoi(*programArray[realIndex]);

			done = operationCode == 99;
			if (!done) {

				Opcode opcode{
					operationCode,
					FCString::Atoi(*programArray[++realIndex]),
					FCString::Atoi(*programArray[++realIndex]),
					FCString::Atoi(*programArray[++realIndex]),
				};
				UE_LOG(LogTemp, Log, TEXT(", %d"), opcode.code);
				UE_LOG(LogTemp, Log, TEXT(", %d"), opcode.firstInput);
				UE_LOG(LogTemp, Log, TEXT(", %d"), opcode.secondInput);
				UE_LOG(LogTemp, Log, TEXT(", %d"), opcode.output);
				UE_LOG(LogTemp, Log, TEXT("Array length, %d"), programArray.Num());
				if (opcode.code == 1)
				{
					// Addition
					int result = FCString::Atoi(*programArray[opcode.firstInput]) + FCString::Atoi(*programArray[opcode.secondInput]);
					programArray[opcode.output] = FString::FromInt(result);
				}
				else if (opcode.code == 2)
				{
					// Product
					int result = FCString::Atoi(*programArray[opcode.firstInput]) * FCString::Atoi(*programArray[opcode.secondInput]);
					programArray[opcode.output] = FString::FromInt(result);
				}
			}
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
