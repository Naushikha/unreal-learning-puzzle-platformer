// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

AMovingPlatform::AMovingPlatform() {
	PrimaryActorTick.bCanEverTick = true; // This is appparently required for every C++ actor !READ!
	SetMobility(EComponentMobility::Movable);
}

// This bit of code makes sure that the server propogates down the replication to the client
void AMovingPlatform::BeginPlay() {
	Super::BeginPlay();

	if (HasAuthority()) {
		SetReplicates(true);
		SetReplicateMovement(true);
		// Calculate the vector direction to move in
		FVector GlobalTargetLocation = GetTransform().TransformPosition(TargetLocation); // TargetLocation is local to this actor (relative to its origin)
		UnitMoveDirection = (GlobalTargetLocation - GetActorLocation()).GetSafeNormal();
	}
}

void AMovingPlatform::Tick(float DeltaTime) {
	// Available on the actor, TRUE means server
	if (HasAuthority()) {
		Super::Tick(DeltaTime);
		FVector Location = GetActorLocation();
		Location += UnitMoveDirection * Speed * DeltaTime;
		SetActorLocation(Location);
	}
}