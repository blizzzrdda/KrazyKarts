// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GoKartMovementComponent.h"
#include "GoKartMovementReplicator.generated.h"

USTRUCT()
struct FGoKartState
{
	GENERATED_BODY()

public:
	UPROPERTY()
		FGoKartMove LastMove;
	UPROPERTY()
		FVector Velocity;
	UPROPERTY()
		FTransform Transform;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class KRAZYKARTS_API UGoKartMovementReplicator : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGoKartMovementReplicator();
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const override;
	
	UFUNCTION(Server, WithValidation, Reliable)
	void Server_SendMove(FGoKartMove Move);


private:
	UPROPERTY(VisibleAnywhere)
		UGoKartMovementComponent *MovementComponent;

	void ClearAcknowledgeMoves(FGoKartMove LastMove);

	void UpdateServerState(const FGoKartMove& Move);

	void ClientTick(float DeltaTime);

	UPROPERTY(ReplicatedUsing = OnRep_ServerState)
		FGoKartState ServerState;

	UFUNCTION()
		void OnRep_ServerState();

	void SimulatedProxy_OnRep_ServerState();
	void AutonomousProxy_OnRep_ServerState();

	TArray<FGoKartMove> UnacknowledgedMoves;

	float ClientTimeSinceUpdate;
	float ClientTimeBetweenLastUpdate;
	FVector ClientStartLocation;
};
