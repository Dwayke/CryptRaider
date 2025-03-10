// Fill out your copyright notice in the Description page of Project Settings.


#include "Mover.h"
#include "Math/UnrealMathUtility.h"


// Sets default values for this component's properties
UMover::UMover()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMover::BeginPlay()
{
	Super::BeginPlay();

	OriginalLocation = GetOwner()->GetActorLocation();

	// ...
	
}


// Called every frame
void UMover::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (ShouldMove)
	{
		FVector CurrentLocation = GetOwner()->GetActorLocation();
		FVector TargetLocation = OriginalLocation + MoveOffset;
		float MoveSpeed = FVector::Dist(CurrentLocation, TargetLocation) / MoveTime;

		FVector NewLocation = FMath::VInterpConstantTo(CurrentLocation, TargetLocation, DeltaTime, MoveSpeed);
		GetOwner()->SetActorLocation(NewLocation);
	}
	else
	{
		FVector CurrentLocation = GetOwner()->GetActorLocation();
		float MoveSpeed = FVector::Dist(CurrentLocation, OriginalLocation) / MoveTime;
		FVector NewLocation = FMath::VInterpConstantTo(CurrentLocation, OriginalLocation, DeltaTime, MoveSpeed);
		GetOwner()->SetActorLocation(NewLocation);
	}

	// ...
	AActor* Owner = GetOwner();
	FVector OwnerLocation = Owner->GetActorLocation();
	FString OwnerLocationString = OwnerLocation.ToCompactString();
}

void UMover::SetShouldMove(bool NewShouldMove)
{
	ShouldMove = NewShouldMove;
}

