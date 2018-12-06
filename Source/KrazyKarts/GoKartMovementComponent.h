// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GoKartMovementComponent.generated.h"

USTRUCT()
struct FGoKartMove
{
	GENERATED_BODY()

	UPROPERTY()
		float Throttle;
	UPROPERTY()
		float SteeringThrow;
	UPROPERTY()
		float DeltaTime;
	UPROPERTY()
		float Time;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class KRAZYKARTS_API UGoKartMovementComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Sets default values for this component's properties
	UGoKartMovementComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	void SimulateMove(const FGoKartMove& Move);
	
	FVector GetVelocity() { return Velocity; };
	void SetVelocity(FVector Val) { Velocity = Val; };

	void SetThrottle(float Val) { Throttle = Val; };
	void SetSteeringThrow(float Val) { SteeringThrow = Val; };

	FGoKartMove GetLastMove() { return LastMove; };

private:
	FGoKartMove CreateMove(float DeltaTime);

	FVector GetAirResistance();
	FVector GetRollingResistance();

	void ApplyRotation(float DeltaTime, float SteeringThrow);

	void UpdateLocationFromVelocity(float DeltaTime);

	UPROPERTY(EditAnywhere)
		float Mass = 1000.f;

	//The force applied to the car when the throttle is fully down (N).
	UPROPERTY(EditAnywhere)
		float MaxDrivingForce = 10000.f;

	UPROPERTY(EditAnywhere)
		float MaxDegreePerSec = 90.f;

	// Minimum radius of the car turning circle at full lock (m)
	UPROPERTY(EditAnywhere)
		float MinTurningRadius = 10.f;

	UPROPERTY(EditAnywhere)
		float DragCoefficient = 16.f;

	UPROPERTY(EditAnywhere)
		float RollingResistanceCoefficient = .015f;

	FVector Velocity;
	
	float Throttle;

	float SteeringThrow;

	FGoKartMove LastMove;
};
