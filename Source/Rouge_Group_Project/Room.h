// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ConstructorHelpers.h"
#include "GameFramework/Actor.h"
#include "GameFramework/DefaultPawn.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h" 

#include "EnemySpawnerGeneration.h"

#include <time.h>
#include <vector>
#include "GenericPlatform/GenericPlatformProcess.h"

#include "Room.generated.h"

UCLASS(meta = (BlueprintSpawnableComponent), Blueprintable)
class ROUGE_GROUP_PROJECT_API ARoom : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARoom();

	UPROPERTY(EditAnywhere)
		TSubclassOf<AActor> Enemy1_To_Spawn;

	UPROPERTY(EditAnywhere)
		TSubclassOf<AActor> Enemy2_To_Spawn;

	UPROPERTY(EditAnywhere)
		TSubclassOf<AActor> Enemy3_To_Spawn;

	UPROPERTY(EditAnywhere)
		TSubclassOf<AActor> Enemy4_To_Spawn;

	UPROPERTY(EditAnywhere)
		TSubclassOf<AActor> Enemy5_To_Spawn;

	UPROPERTY(EditAnywhere)
		TSubclassOf<AActor> Enemy6_To_Spawn;

	UPROPERTY(EditAnywhere)
		TSubclassOf<AActor> Boss_To_Spawn;

	UPROPERTY(EditAnywhere)
		TSubclassOf<AActor> Sprite_To_Spawn;

	UPROPERTY(EditAnywhere)
		TSubclassOf<AActor> Walls_To_Spawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemies")
		int numEnemies;

	void SetCanSpawn();
	void SetBossRoom();
	void SetRoomType(int RoomNum);
	void SetRoomLocation(int LocationX, int LocationY);
	void DecreaseNumEnemies();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	int RoomType;
	bool has_spawned = false;
	bool boss_room = false;
	bool CanSpawn = false;
	vector <int> EnemyLocationX, EnemyLocationY;
	int LocationX, LocationY;


	const int COL = 13;
	const int ROW = 13;
	const int START_X = COL / 2;
	const int START_Y = ROW / 2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UClass* PlayerTriggerClass = ADefaultPawn::StaticClass();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UClass* DoorTriggerClass = ADefaultPawn::StaticClass();

	UFUNCTION()
		void OnComponentBeginOverlap(class UBoxComponent* Component, class AActor* Character, class UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void SpawnEnemy1(FVector Location, FRotator Rotation);

	UFUNCTION()
		void SpawnEnemy2(FVector Location, FRotator Rotation);

	UFUNCTION()
		void SpawnEnemy3(FVector Location, FRotator Rotation);

	UFUNCTION()
		void SpawnEnemy4(FVector Location, FRotator Rotation);

	UFUNCTION()
		void SpawnEnemy5(FVector Location, FRotator Rotation);

	UFUNCTION()
		void SpawnEnemy6(FVector Location, FRotator Rotation);

	UFUNCTION()
		void SpawnBoss(FVector Location, FRotator Rotation);

	UFUNCTION()
		void SpawnWalls(FVector Location);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
private:
	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* Floor;

	UPROPERTY(EditDefaultsOnly)
		UBoxComponent* CollisionBox;

	UFUNCTION()
		void GetEnemyPositions();

};
