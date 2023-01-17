// Fill out your copyright notice in the Description page of Project Settings.


#include "Room.h"

// Sets default values
ARoom::ARoom()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.

	Floor = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Teleporter"));
	RootComponent = Floor;

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Collsion Box"));
	CollisionBox->SetupAttachment(Floor);
}


void ARoom::OnComponentBeginOverlap(class UBoxComponent* Component, class AActor* Object, class UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Object->IsA(PlayerTriggerClass) && boss_room == true && CanSpawn == true)
	{
		SpawnEnemy1(FVector(LocationX + (9 - 2 * START_X + 1) * 100, LocationY + (5 - START_Y) * 100, 50), FRotator(90, 90, 0));
		SpawnEnemy2(FVector(LocationX + (11 - 2 * START_X + 1) * 100, LocationY + (5 - START_Y) * 100, 50), FRotator(90, 90, 0));
		SpawnEnemy3(FVector(LocationX + (13 - 2 * START_X + 1) * 100, LocationY + (5 - START_Y) * 100, 50), FRotator(90, 90, 0));
		SpawnEnemy4(FVector(LocationX + (9 - 2 * START_X + 1) * 100, LocationY + (7 - START_Y) * 100, 50), FRotator(90, 90, 0));
		SpawnEnemy5(FVector(LocationX + (11 - 2 * START_X + 1) * 100, LocationY + (7 - START_Y) * 100, 50), FRotator(90, 90, 0));
		SpawnEnemy6(FVector(LocationX + (13 - 2 * START_X + 1) * 100, LocationY + (7 - START_Y) * 100, 50), FRotator(90, 90, 0));
		numEnemies++;
		has_spawned = true;
	}
	else if (Object->IsA(PlayerTriggerClass) && has_spawned == false && CanSpawn == true)
	{
		has_spawned = true;
		GetEnemyPositions();
		numEnemies = 0;
		srand(time(NULL));
		vector <int> enemyType;
		int chosenType[2];
		int numEnemyTypes = 6;
		enemyType.push_back(1);
		enemyType.push_back(2);
		enemyType.push_back(3);
		enemyType.push_back(4);
		enemyType.push_back(5);
		enemyType.push_back(6);
		int choose = rand() % numEnemyTypes;
		numEnemyTypes--;
		chosenType[0] = enemyType.at(choose);
		enemyType.erase(enemyType.begin() + choose);
		choose = rand() % numEnemyTypes;
		chosenType[1] = enemyType.at(choose);

		int randNumEnemies = (rand() % 4) + 3;
		while (numEnemies < randNumEnemies)
		{
			choose = rand() % 2;
			int randYPos = (rand() % 5) + 4;
			int randXPos = (rand() % 7) + 8;
			FVector EnemySpawnerLocation = FVector(LocationX + (randXPos - 2 * START_X + 1) * 100, LocationY + (randYPos - START_Y) * 100, 50);
			if (chosenType[choose] == 1)
				SpawnEnemy1(EnemySpawnerLocation, FRotator(90, 90, 0));
			else if (chosenType[choose] == 2)
				SpawnEnemy2(EnemySpawnerLocation, FRotator(90, 90, 0));
			else if (chosenType[choose] == 3)
				SpawnEnemy3(EnemySpawnerLocation, FRotator(90, 90, 0));
			else if (chosenType[choose] == 4)
				SpawnEnemy4(EnemySpawnerLocation, FRotator(90, 90, 0));
			else if (chosenType[choose] == 5)
				SpawnEnemy5(EnemySpawnerLocation, FRotator(90, 90, 0));
			else if (chosenType[choose] == 6)
				SpawnEnemy6(EnemySpawnerLocation, FRotator(90, 90, 0));

			numEnemies++;
		}



		//while (EnemyLocationX.empty() == false)
		//{
		//	choose = rand() % 2;
		//	FVector EnemySpawnerLocation = FVector(LocationX + (EnemyLocationX.back() - 2 * START_X + 1) * 100, LocationY + (EnemyLocationY.back() - START_Y) * 100, 50);
		//	if (chosenType[choose] == 1)
		//		SpawnEnemy1(EnemySpawnerLocation, FRotator(90, 90, 0));
		//	else if (chosenType[choose] == 2)
		//		SpawnEnemy2(EnemySpawnerLocation, FRotator(90, 90, 0));
		//	else if (chosenType[choose] == 3)
		//		SpawnEnemy3(EnemySpawnerLocation, FRotator(90, 90, 0));
		//	else if (chosenType[choose] == 4)
		//		SpawnEnemy4(EnemySpawnerLocation, FRotator(90, 90, 0));
		//	else if (chosenType[choose] == 4)
		//		SpawnEnemy5(EnemySpawnerLocation, FRotator(90, 90, 0));
		//
		//	EnemyLocationX.pop_back();
		//	EnemyLocationY.pop_back();
		//	numEnemies++;
		//}
		if (numEnemies > 0)
		{
			SpawnWalls(FVector(LocationX, LocationY, 0));
		}
	}
	if (Object->IsA(DoorTriggerClass))
	{
		if (numEnemies < 1)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, "Destroy Doors", true, { 3,3 });
			Object->Destroy();
		}
	}
}

void ARoom::SpawnEnemy1(FVector Location, FRotator Rotation)
{
	UWorld* World = GetWorld();
	AActor* SpawnedActorRef = World->SpawnActor<AActor>(Enemy1_To_Spawn, FVector(Location.X, Location.Y, 100.f), Rotation);
}

void ARoom::SpawnEnemy2(FVector Location, FRotator Rotation)
{
	UWorld* World = GetWorld();
	AActor* SpawnedActorRef = World->SpawnActor<AActor>(Enemy2_To_Spawn, FVector(Location.X, Location.Y, 100.f), Rotation);
}

void ARoom::SpawnEnemy3(FVector Location, FRotator Rotation)
{
	UWorld* World = GetWorld();
	AActor* SpawnedActorRef = World->SpawnActor<AActor>(Enemy3_To_Spawn, FVector(Location.X, Location.Y, 100.f), Rotation);
}

void ARoom::SpawnEnemy4(FVector Location, FRotator Rotation)
{
	UWorld* World = GetWorld();
	AActor* SpawnedActorRef = World->SpawnActor<AActor>(Enemy4_To_Spawn, FVector(Location.X, Location.Y, 100.f), Rotation);
}

void ARoom::SpawnEnemy5(FVector Location, FRotator Rotation)
{
	UWorld* World = GetWorld();
	AActor* SpawnedActorRef = World->SpawnActor<AActor>(Enemy5_To_Spawn, FVector(Location.X, Location.Y, 100.f), Rotation);
}

void ARoom::SpawnEnemy6(FVector Location, FRotator Rotation)
{
	UWorld* World = GetWorld();
	AActor* SpawnedActorRef = World->SpawnActor<AActor>(Enemy6_To_Spawn, FVector(Location.X, Location.Y, 100.f), Rotation);
}

void ARoom::SpawnBoss(FVector Location, FRotator Rotation)
{
	UWorld* World = GetWorld();
	AActor* SpawnedActorRef = World->SpawnActor<AActor>(Boss_To_Spawn, FVector(Location.X, Location.Y, 100.f), Rotation);
}

void ARoom::SpawnWalls(FVector Location)
{
	// Spawning all 4 doors,  will need to mess with rotation later
	UWorld* World = GetWorld();

	AActor* WallsRef = World->SpawnActor<AActor>(Walls_To_Spawn, FVector(Location.X, Location.Y, 102.f), FRotator(0, 0, 0));

}

void ARoom::GetEnemyPositions()
{
	switch (RoomType)
	{
	case 1:
		EnemySpawner1(EnemyLocationX, EnemyLocationY);
		break;
	case 2:
		EnemySpawner2(EnemyLocationX, EnemyLocationY);
		break;
	case 3:
		EnemySpawner3(EnemyLocationX, EnemyLocationY);
		break;
	case 4:
		EnemySpawner4(EnemyLocationX, EnemyLocationY);
		break;
	case 5:
		EnemySpawner5(EnemyLocationX, EnemyLocationY);
		break;
	case 6:
		EnemySpawner6(EnemyLocationX, EnemyLocationY);
		break;
	case 7:
		EnemySpawner7(EnemyLocationX, EnemyLocationY);
		break;
	case 8:
		EnemySpawner8(EnemyLocationX, EnemyLocationY);
		break;
	case 9:
		EnemySpawner9(EnemyLocationX, EnemyLocationY);
		break;
	case 10:
		EnemySpawner10(EnemyLocationX, EnemyLocationY);
		break;
	case 11:
		EnemySpawner11(EnemyLocationX, EnemyLocationY);
		break;
	case 12:
		EnemySpawner12(EnemyLocationX, EnemyLocationY);
		break;
	case 13:
		EnemySpawner13(EnemyLocationX, EnemyLocationY);
		break;
	case 14:
		EnemySpawner14(EnemyLocationX, EnemyLocationY);
		break;
	case 15:
		EnemySpawner15(EnemyLocationX, EnemyLocationY);
		break;
	case 16:
		EnemySpawner16(EnemyLocationX, EnemyLocationY);
		break;
	case 17:
		EnemySpawner17(EnemyLocationX, EnemyLocationY);
		break;
	case 18:
		EnemySpawner18(EnemyLocationX, EnemyLocationY);
		break;
	case 19:
		EnemySpawner19(EnemyLocationX, EnemyLocationY);
		break;
	case 20:
		EnemySpawner20(EnemyLocationX, EnemyLocationY);
		break;
	case 21:
		EnemySpawner21(EnemyLocationX, EnemyLocationY);
		break;
	case 22:
		EnemySpawner22(EnemyLocationX, EnemyLocationY);
		break;
	case 23:
		EnemySpawner23(EnemyLocationX, EnemyLocationY);
		break;
	case 24:
		EnemySpawner24(EnemyLocationX, EnemyLocationY);
		break;
	case 25:
		EnemySpawner25(EnemyLocationX, EnemyLocationY);
		break;
	}
}


// Called when the game starts or when spawned
void ARoom::BeginPlay()
{
	Super::BeginPlay();

	FScriptDelegate DelegateSubscribeer;
	DelegateSubscribeer.BindUFunction(this, "OnComponentBeginOverlap");
	CollisionBox->OnComponentBeginOverlap.Add(DelegateSubscribeer);

	SetActorTickEnabled(false);
}

// Called every frame
void ARoom::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARoom::SetRoomType(int RoomNum)
{
	RoomType = RoomNum;
}


void ARoom::SetRoomLocation(int FloorLocationX, int FloorLocationY)
{
	LocationX = FloorLocationX;
	LocationY = FloorLocationY;
}

void ARoom::SetCanSpawn()
{
	CanSpawn = true;
}

void ARoom::SetBossRoom()
{
	boss_room = true;
}

void ARoom::DecreaseNumEnemies()
{
	numEnemies--;
}