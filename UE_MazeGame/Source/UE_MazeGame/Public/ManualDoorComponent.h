// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Curves/CurveFloat.h"
#include "ManualDoorComponent.generated.h"

class ATriggerBox;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UE_MAZEGAME_API UManualDoorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UManualDoorComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere) float TimeToRotate = 1.0f;
	UPROPERTY(EditAnywhere) ATriggerBox* TriggerBox;
	UPROPERTY(EditAnywhere) FRuntimeFloatCurve OpenCurve;

	FRotator StartRotation = FRotator::ZeroRotator;

	float CurrentRotationTime = 0.0f;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
