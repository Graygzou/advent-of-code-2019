// Fill out your copyright notice in the Description page of Project Settings.


#include "Day8.h"

int UDay8::ComputeDay8(FString input, int width, int height)
{
	int currentNumberOfZeros = 0;
	int finalNumberOfZeros = -1;

	int currentNumberOfOnes = 0;
	int finalNumberOfOnes = 0;

	int currentNumberOfTwos = 0;
	int finalNumberOfTwos = 0;

	FString currentStr;

	for(int i = 0; i < input.Len(); i++)
	{
		if (FChar::ConvertCharDigitToInt(input[i]) == 1)
		{
			currentNumberOfOnes++;
		}
		else if (FChar::ConvertCharDigitToInt(input[i]) == 2)
		{
			currentNumberOfTwos++;
		}
		else if (FChar::ConvertCharDigitToInt(input[i]) == 0)
		{
			currentNumberOfZeros++;
		}

		currentStr.AppendInt(FChar::ConvertCharDigitToInt(input[i]));
		if (i > 0 && (i+1) % width == 0)
		{
			UE_LOG(LogTemp, Log, TEXT("%s"), *currentStr);
			currentStr = "";
		}

		if (FMath::FloorToInt((i+1) / width) % height == 0)
		{
			UE_LOG(LogTemp, Log, TEXT(""));
		}

		// If we reached the end of a layer
		if (((i+1) % width == 0) && (FMath::FloorToInt((i+1) / width) % height == 0))
		{
			UE_LOG(LogTemp, Log, TEXT("current index = %d"), i);
			UE_LOG(LogTemp, Log, TEXT("top corner of the layer = %d"), FChar::ConvertCharDigitToInt(input[i]));

			if (finalNumberOfZeros == -1 || currentNumberOfZeros < finalNumberOfZeros)
			{
				finalNumberOfTwos = currentNumberOfTwos;
				finalNumberOfOnes = currentNumberOfOnes;
				finalNumberOfZeros = currentNumberOfZeros;
			}

			// Reset everything
			currentNumberOfOnes = 0;
			currentNumberOfTwos = 0;
			currentNumberOfZeros = 0;
		}
	}

	return finalNumberOfOnes * finalNumberOfTwos;
}

void UDay8::ComputeDay8Part2(FString input, int width, int height)
{
	FString currentLine("00000000000000000\n");

	for (int i = 0; i < width * height; ++i)
	{
		int currentIndex = i;
		int currentColorBit = 0;
		do
		{
			currentColorBit = FChar::ConvertCharDigitToInt(input[currentIndex]);
			currentIndex += height * width;
			UE_LOG(LogTemp, Log, TEXT("new index %d"), currentIndex);
		} while (currentIndex < input.Len() && currentColorBit == 2);

		if (currentColorBit == 2)
		{
			UE_LOG(LogTemp, Log, TEXT("something went wrong. Didn't find any 0 or 1 for this cell ?!"));
		}

		// Add the selected color bit to the result string
		currentLine += FString::FromInt(currentColorBit);

		// Print the current line if we reached the end of it
		if ((i + 1) % width == 0)
		{
			currentLine += "\n";
		}
	}
	UE_LOG(LogTemp, Log, TEXT("%s"), *currentLine);
	UE_LOG(LogTemp, Log, TEXT("End of part 2"));
}