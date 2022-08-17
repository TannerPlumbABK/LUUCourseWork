// Fill out your copyright notice in the Description page of Project Settings.


#include "SlidingDoorComponent.h"
#include "Engine/TriggerBox.h"

// Sets default values for this component's properties
USlidingDoorComponent::USlidingDoorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USlidingDoorComponent::BeginPlay()
{
	Super::BeginPlay();
	StartLocation = GetOwner()->GetActorLocation();
	FinalLocation = GetOwner()->GetActorLocation() + DesiredLocation;
	CurrentLocationTime = 0.0f;
}


// Called every frame
void USlidingDoorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	APawn* PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();

	if (PlayerPawn && TriggerBox->IsOverlappingActor(PlayerPawn))
	{
		if (CurrentLocationTime < TimeToLocation)
		{
			CurrentLocationTime += DeltaTime;
			const float TimeRatio = FMath::Clamp(CurrentLocationTime / TimeToLocation, 0.0f, 1.0f);
			const float MoveAlpha = OpenCurve.GetRichCurveConst()->Eval(TimeRatio);
			const FVector CurrentLocation = FMath::Lerp(StartLocation, FinalLocation, MoveAlpha);
			GetOwner()->SetActorLocation(CurrentLocation);
		}
	}
	else
	{
		if (ReturnToStart && CurrentLocationTime > 0)
		{
			CurrentLocationTime -= DeltaTime;
			const float TimeRatio = FMath::Clamp(CurrentLocationTime / TimeToReturn, 0.0f, 1.0f);
			const float MoveAlpha = OpenCurve.GetRichCurveConst()->Eval(TimeRatio);
			const FVector CurrentLocation = FMath::Lerp(StartLocation, FinalLocation, MoveAlpha);
			GetOwner()->SetActorLocation(CurrentLocation);
		}
	}
}

