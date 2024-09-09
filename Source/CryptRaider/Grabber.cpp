// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"
#include "Engine/World.h"

//#include "DrawDebugHelpers.h"


// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
		// ...	
	UPhysicsHandleComponent* PhysicsHandle = GetPhysicsHandle();
	if (PhysicsHandle && PhysicsHandle->GetGrabbedComponent() != nullptr)
	{
		FVector TargetLocation = GetComponentLocation() + (GetForwardVector() * HoldDistance);
		PhysicsHandle->SetTargetLocationAndRotation(TargetLocation, GetComponentRotation());
	}

}

void UGrabber::Release()
{
	
	UPhysicsHandleComponent* PhysicsHandle = GetPhysicsHandle();
	if (PhysicsHandle && PhysicsHandle->GetGrabbedComponent())
	{
		AActor* GrabbedComponent = PhysicsHandle->GetGrabbedComponent()->GetOwner();
		if (GrabbedComponent)
		{
			GrabbedComponent->Tags.Remove("Grabbed");
		}
		PhysicsHandle->ReleaseComponent();
		UE_LOG(LogTemp, Display, TEXT("Released"));
	}
}

void UGrabber::Grab()
{
	UPhysicsHandleComponent* PhysicsHandle = GetPhysicsHandle();
	FHitResult HitResult;

	if (PhysicsHandle && GetGrabbableInReach(HitResult))
	{
		UPrimitiveComponent* HitComponent = HitResult.GetComponent();
		HitComponent->WakeAllRigidBodies();
		HitComponent->SetSimulatePhysics(true);
		HitResult.GetActor()->Tags.Add("Grabbed");
		HitResult.GetActor()->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 5, 8, FColor::Magenta, false, 5);
		PhysicsHandle->GrabComponentAtLocationWithRotation(HitComponent, NAME_None, HitResult.ImpactPoint, GetComponentRotation());
		UE_LOG(LogTemp, Display, TEXT("Grabbed"));
	}
}

UPhysicsHandleComponent* UGrabber::GetPhysicsHandle() const
{
	return GetOwner()->GetComponentByClass<UPhysicsHandleComponent>();;
}

bool UGrabber::GetGrabbableInReach(FHitResult& OutHitResult) const
{
	FVector StartLine = GetComponentLocation();
	FVector EndLine = StartLine + (GetForwardVector() * MaxGrabDistance);
	DrawDebugSphere(GetWorld(), EndLine, 5, 8, FColor::Cyan, false, 5);
	FCollisionShape CollisionSphere = FCollisionShape::MakeSphere(GrabRadius);
	return GetWorld()->SweepSingleByChannel(OutHitResult, StartLine, EndLine, FQuat::Identity, ECC_GameTraceChannel2, CollisionSphere);
}

