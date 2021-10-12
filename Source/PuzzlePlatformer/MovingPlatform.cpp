// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

AMovingPlatform::AMovingPlatform() {
	PrimaryActorTick.bCanEverTick = true;
	SetMobility(EComponentMobility::Movable);
}

// This bit of code makes sure that the server propogates down the replication to the client
void AMovingPlatform::BeginPlay() {
	Super::BeginPlay();

	if (HasAuthority()) {
	SetReplicates(true);
	SetReplicateMovement(true);
	}
}

void AMovingPlatform::Tick(float DeltaTime) {
	// Available on the actor, TRUE means server
	if (HasAuthority()) {
		Super::Tick(DeltaTime);
		FVector Location = GetActorLocation();
		Location += FVector(Speed * DeltaTime, 0, 0);
		SetActorLocation(Location);
	}
}