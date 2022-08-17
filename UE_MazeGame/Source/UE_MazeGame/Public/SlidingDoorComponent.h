// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Curves/CurveFloat.h"
#include "SlidingDoorComponent.generated.h"

class ATriggerBox;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UE_MAZEGAME_API USlidingDoorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USlidingDoorComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
		FVector DesiredLocation = FVector::ZeroVector;

	UPROPERTY(EditAnywhere)
		float TimeToLocation = 1.0f;

	UPROPERTY(EditAnywhere)
		ATriggerBox* TriggerBox;

	UPROPERTY(EditAnywhere)
		FRuntimeFloatCurve OpenCurve;

	UPROPERTY(EditAnywhere)
		bool ReturnToStart = false;

	UPROPERTY(EditAnywhere)
		float TimeToReturn = 1.0f;

	FVector StartLocation = FVector::ZeroVector;
	FVector FinalLocation = FVector::ZeroVector;
	float CurrentLocationTime = 0.0f;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
