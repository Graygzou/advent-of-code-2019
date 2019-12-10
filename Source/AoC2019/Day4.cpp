// Fill out your copyright notice in the Description page of Project Settings.


#include "Day4.h"
#include "Misc/Char.h"

bool LegitPassword2(int password)
{
	FString strNumber = FString::FromInt(password);

	int lastAdjacentDigit = -1;
	bool adjacentDigitSame = false;
	bool validated = false;

	//UE_LOG(LogTemp, Log, TEXT("string to do %s "), *strNumber);

	for (int i = 0; i < strNumber.Len()-1; ++i)
	{
		//UE_LOG(LogTemp, Log, TEXT("str %d %d "), FChar::ConvertCharDigitToInt(strNumber[i]), FChar::ConvertCharDigitToInt(strNumber[i + 1]));

		if (FChar::ConvertCharDigitToInt(strNumber[i]) > FChar::ConvertCharDigitToInt(strNumber[i+1]))
		{
			return false;
		}
		int currentNumber = FChar::ConvertCharDigitToInt(strNumber[i]);
		if (FChar::ConvertCharDigitToInt(strNumber[i + 1]) == currentNumber)
		{
			if ((i == 0 || (i > 0 && FChar::ConvertCharDigitToInt(strNumber[i - 1]) != currentNumber)) &&
				(i == strNumber.Len() - 2 || (i < strNumber.Len() - 2 && FChar::ConvertCharDigitToInt(strNumber[i + 2]) != currentNumber)))
			{
				adjacentDigitSame = true;
			}

			/*
			if (FChar::ConvertCharDigitToInt(strNumber[i]) == lastAdjacentDigit)
			{
				adjacentDigitSame = false;
			}
			else
			{
				int currentDoubleNumber = FChar::ConvertCharDigitToInt(strNumber[i]);
				
				//UE_LOG(LogTemp, Log, TEXT("last adjacent %d "), lastAdjacentDigit);

				if (currentDoubleNumber != lastAdjacentDigit)
				{
					adjacentDigitSame = true;
					lastAdjacentDigit = currentDoubleNumber;
				}
				else
				{
					adjacentDigitSame = false;
				}
				//UE_LOG(LogTemp, Log, TEXT("Test %s"), adjacentDigitSame ? TEXT("yeah !") : TEXT("not anymore.."));
			}*/
		}
	}

	return adjacentDigitSame;
}

bool LegitPassword(int password)
{
	FString strNumber = FString::FromInt(password);

	//UE_LOG(LogTemp, Log, TEXT("str len %d"), strNumber.Len());
	//UE_LOG(LogTemp, Log, TEXT("str %s"), *strNumber);

	bool adjacentDigitSame = false;

	//TArray<TCHAR> charArray = strNumber.GetCharArray();
	for (int i = 0; i < strNumber.Len() - 1; ++i)
	{
		/*
		TCHAR* t = *strNumber[i];
		UE_LOG(LogTemp, Log, TEXT("i+1 %c \n ====="), *strNumber[i + 1]);*/
		//UE_LOG(LogTemp, Log, TEXT("i %d, %d"), FChar::ConvertCharDigitToInt(strNumber[i]), FChar::ConvertCharDigitToInt(strNumber[i+1]));
		if (FChar::ConvertCharDigitToInt(strNumber[i]) > FChar::ConvertCharDigitToInt(strNumber[i + 1]))
		{
			return false;
		}
		adjacentDigitSame |= strNumber[i] == strNumber[i + 1];
	}

	return adjacentDigitSame;
}


int UDay4::ComputeDay4(int lowerBound, int upperBound)
{
	int nbCombinaisons = 0;
	FString strLowerBound = FString::FromInt(lowerBound);
	FString strUpperBound = FString::FromInt(upperBound);

	UE_LOG(LogTemp, Log, TEXT("Test %s"), *strLowerBound);
	UE_LOG(LogTemp, Log, TEXT("Test %s"), *strUpperBound);

	// Units Tests
	/*
	bool t = LegitPassword2(112233);
	UE_LOG(LogTemp, Log, TEXT("Test 112233 %s"), t ? TEXT("ok") : TEXT("NO"));	// true
	t = LegitPassword2(123444);
	UE_LOG(LogTemp, Log, TEXT("Test 123444 %s"), !t ? TEXT("ok") : TEXT("NO"));	// false
	t = LegitPassword2(111122);
	UE_LOG(LogTemp, Log, TEXT("Test 111122 %s"), t ? TEXT("ok") : TEXT("NO"));	// true

	t = LegitPassword2(144466);
	UE_LOG(LogTemp, Log, TEXT("Test 144466 %s"), t ? TEXT("ok") : TEXT("NO"));	// true
	t = LegitPassword2(111455);
	UE_LOG(LogTemp, Log, TEXT("Test 111455 %s"), t ? TEXT("ok") : TEXT("NO"));	// true
	t = LegitPassword2(111456);
	UE_LOG(LogTemp, Log, TEXT("Test 111456 %s"), !t ? TEXT("ok") : TEXT("NO"));	// false

	t = LegitPassword2(111111);
	UE_LOG(LogTemp, Log, TEXT("Test 111111 %s"), !t ? TEXT("ok") : TEXT("NO"));	// false
	t = LegitPassword2(112333);
	UE_LOG(LogTemp, Log, TEXT("Test 112333 %s"), t ? TEXT("ok") : TEXT("NO"));	// true
	t = LegitPassword2(113333);
	UE_LOG(LogTemp, Log, TEXT("Test 113333 %s"), t ? TEXT("ok") : TEXT("NO"));	// true

	t = LegitPassword2(223450);
	UE_LOG(LogTemp, Log, TEXT("Test 223450 %s"), !t ? TEXT("ok") : TEXT("NO"));	// false
	t = LegitPassword2(123789);
	UE_LOG(LogTemp, Log, TEXT("Test 123789 %s"), !t ? TEXT("ok") : TEXT("NO"));	// false
	t = LegitPassword2(112233);
	UE_LOG(LogTemp, Log, TEXT("Test 112233 %s"), t ? TEXT("ok") : TEXT("NO"));	// true
	t = LegitPassword2(123444);
	UE_LOG(LogTemp, Log, TEXT("Test 123444 %s"), !t ? TEXT("ok") : TEXT("NO"));	// false
	t = LegitPassword2(111122);
	UE_LOG(LogTemp, Log, TEXT("Test 111122 %s"), t ? TEXT("ok") : TEXT("NO"));	// true
	t = LegitPassword2(699999);
	UE_LOG(LogTemp, Log, TEXT("Test 699999 %s"), !t ? TEXT("ok") : TEXT("NO"));	// false
	t = LegitPassword2(688999);
	UE_LOG(LogTemp, Log, TEXT("Test 688999 %s"), t ? TEXT("ok") : TEXT("NO"));	// true
	*/

	for (int i = lowerBound; i <= upperBound; ++i)
	{
		if (LegitPassword2(i))
		{
			nbCombinaisons += 1;
		}
	}

	/*
	for (int32 i = 0; i < strDiff.Len(); i++)
	{
		int res = 1; 
		// Study the previous number if it's not the first one
		if (i < strNumber.Len() - 1)
		{
			res = 10 - FMath::Max(FCString::Atoi(&strNumber[i + 1]), FCString::Atoi(&strNumber[i]) + 1);
		}

		UE_LOG(LogTemp, Log, TEXT("Test %d"), res);

		// If it's no the last number compute the following combinaison
		if (i >= 0)
		{
			for (int j = 0; j < res; ++j)
			{
				UE_LOG(LogTemp, Log, TEXT("Test %d"), FCString::Atoi(&strNumber[i]));
				res += 10 - FCString::Atoi(&strNumber[i]) + 1 + j;
			}
		}
		nbCombinaisons += res;
	}*/

	/*
	for (int a = 1; a <= 5; ++a)
	{
		int bound = a;
		if (a == 5)
		{
			bound = 7;
		}
		for (int b = bound; b < 9; ++b)
		{
			for (int i = b; i < 9; ++i)
			{
				for (int j = i; j < 9; ++j)
				{
					for (int z = j; z < 9; ++z)
					{
						nbCombinaisons += z;
					}
				}
			}
		}
	}*/
	return nbCombinaisons;
}