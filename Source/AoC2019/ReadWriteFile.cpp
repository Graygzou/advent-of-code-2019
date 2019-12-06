// Fill out your copyright notice in the Description page of Project Settings.


#include "ReadWriteFile.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"

bool UReadWriteFile::FileSaveString(FString SaveTextB, FString FileNameB)
{
	return FFileHelper::SaveStringToFile(SaveTextB, *(FPaths::GameDir() + FileNameB));
}

bool UReadWriteFile::FileLoadString(FString FileNameA, FString& SaveTextA)
{
	const TCHAR* test = *FPaths::GameDir();
	//UE_LOG(LogTemp, Log, TEXT("ICI: %s"), *FPaths::GameDir())
	return FFileHelper::LoadFileToString(SaveTextA, *(FPaths::GameDir() + FileNameA));
}

TArray<FString> UReadWriteFile::SplitString(const FString txt, const FString delimiter)
{
	// Pre-treatment to show the \n properly
	FString contentLeft = txt.ReplaceCharWithEscapedChar();
	// Remove last spaces
	contentLeft = contentLeft.TrimEnd();
	TArray<FString> splitedStrings;
	int32 lastPos = 0;

	//int32 index;
	// > 3 because \n + an extra space make a len 3
	while (contentLeft.Contains(delimiter))
	{
		//UE_LOG(LogTemp, Log, TEXT("contains %s %d"), *contentLeft, contentLeft.Len());

		FString leftStr;
		FString rightStr;

		//UE_LOG(LogTemp, Log, TEXT("contains %s"), (contentLeft.Contains("\n") ? TEXT("True") : TEXT("False")));
	
		bool res = contentLeft.Split(delimiter, &leftStr, &rightStr);
		//UE_LOG(LogTemp, Log, TEXT("return value = %s"), (res ? TEXT("True") : TEXT("False")));

		//UE_LOG(LogTemp, Log, TEXT("Test left, %s"), *leftStr);
		//UE_LOG(LogTemp, Log, TEXT("Test right, %s"), *rightStr);

		splitedStrings.Add(leftStr);

		contentLeft = rightStr;
	}

	// add the rest of the content if necessary
	if (contentLeft.Len() > 0)
	{
		splitedStrings.Add(contentLeft);
	}
	
	//UE_LOG(LogTemp, Log, TEXT("Nb Elem %d"), splitedStrings.Num());
	return splitedStrings;
}

