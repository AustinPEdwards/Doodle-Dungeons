// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include <iostream>
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h" 
#include "DrawDebugHelpers.h"

#include "Room.h"
#include "Teleporter.h"
#include "WorldGeneration.h"
#include "RockGeneration.h"
#include "SpikeGeneration.h"

#include <iostream>
#include <time.h>
#include <stack>
#include <vector>

#include "Floor.generated.h"



UCLASS()
class ROUGE_GROUP_PROJECT_API AFloor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFloor();

	UPROPERTY(EditAnywhere)
		TSubclassOf<AActor> Character_To_Spawn;

	UPROPERTY(EditAnywhere)
		TSubclassOf<ARoom> Floor_To_Spawn;

	UPROPERTY(EditAnywhere)
		TSubclassOf<AActor> Start_Floor_To_Spawn;

	UPROPERTY(EditAnywhere)
		TSubclassOf<ARoom> Boss_Floor_To_Spawn;

	UPROPERTY(EditAnywhere)
		TSubclassOf<AActor> Rock_To_Spawn;

	UPROPERTY(EditAnywhere)
		TSubclassOf<AActor> Spike_To_Spawn;

	UPROPERTY(EditAnywhere)
		TSubclassOf<AActor> Heart_To_Spawn;

	UPROPERTY(EditAnywhere)
		TSubclassOf<ATeleporter> Spawn_Up_Teleport;

	UPROPERTY(EditAnywhere)
		TSubclassOf<ATeleporter> Spawn_Right_Teleport;

	UPROPERTY(EditAnywhere)
		TSubclassOf<ATeleporter> Spawn_Down_Teleport;

	UPROPERTY(EditAnywhere)
		TSubclassOf<ATeleporter> Spawn_Left_Teleport;

	UPROPERTY(EditAnywhere)
		TSubclassOf<AActor> Spawn_Wall_A;

	UPROPERTY(EditAnywhere)
		TSubclassOf<AActor> Spawn_Wall_B;

	UPROPERTY(EditAnywhere)
		TSubclassOf<AActor> Spawn_Wall_C;

	UPROPERTY(EditAnywhere)
		TSubclassOf<AActor> Spawn_Wall_D;

	UPROPERTY(EditAnywhere)
		TSubclassOf<AActor> Spawn_Wall_E;

	UPROPERTY(EditAnywhere)
		TSubclassOf<AActor> Spawn_Wall_F;

	UPROPERTY(EditAnywhere)
		TSubclassOf<AActor> Spawn_Wall_G;

	UPROPERTY(EditAnywhere)
		TSubclassOf<AActor> Spawn_Wall_H;

	UPROPERTY(EditAnywhere)
		TSubclassOf<AActor> Spawn_Wall_I;

	UPROPERTY(EditAnywhere)
		TSubclassOf<AActor> Spawn_Wall_J;

	UPROPERTY(EditAnywhere)
		TSubclassOf<AActor> Spawn_Wall_K;

	UPROPERTY(EditAnywhere)
		TSubclassOf<AActor> Spawn_Wall_L;

	UPROPERTY(EditAnywhere)
		TSubclassOf<AActor> Spawn_Wall_M;

	UPROPERTY(EditAnywhere)
		TSubclassOf<AActor> Spawn_Wall_N;

	UPROPERTY(EditAnywhere)
		TSubclassOf<AActor> Spawn_Wall_O;

	UPROPERTY(EditAnywhere)
		TSubclassOf<AActor> Spawn_Wall_P;
protected:

	virtual void BeginPlay() override;

	UFUNCTION()
		void SpawnFloor(TSubclassOf<ARoom> Spawn_Floor, FVector Location, FRotator Rotation, int RoomType);

	UFUNCTION()
		void SpawnStartFloor(FVector Location, FRotator Rotation);

	UFUNCTION()
		void SpawnBossFloor(FVector Location, FRotator Rotation);

	UFUNCTION()
		void SpawnHeart(FVector Location);

	UFUNCTION()
		void SpawnRock(FVector Location, FRotator Rotation);

	UFUNCTION()
		void SpawnSpike(FVector Location, FRotator Rotation);

	UFUNCTION()
		void SpawnWalls(TSubclassOf<AActor> Spawn_Wall, FVector Location, FRotator Rotation);

	UFUNCTION()
		void SpawnTeleport(TSubclassOf<ATeleporter> Spawn_Teleport, FVector Location, FRotator Rotation, int Direction);

	UFUNCTION()
		void SpawnCharacter(FVector Location, FRotator Rotation);
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
