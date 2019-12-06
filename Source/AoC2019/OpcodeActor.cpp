// Fill out your copyright notice in the Description page of Project Settings.


#include "OpcodeActor.h"

// Sets default values
AOpcodeActor::AOpcodeActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AOpcodeActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AOpcodeActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

///**/
//int AOpcodeActor::compute()
//{
//	int result;
//	if (opcode)
//	{
//		// Addition
//		result = firstInput + secondInput;
//	}
//	else
//	{
//		// Product
//		result = firstInput * secondInput;
//	}
//	return result;
//}
