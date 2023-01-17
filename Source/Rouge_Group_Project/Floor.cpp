
#include "Floor.h"

using namespace std;
// Sets default values
AFloor::AFloor()
{

	UStaticMeshComponent* Plane = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Plane"));
	Plane->SetupAttachment(RootComponent);
	Plane->SetMobility(EComponentMobility::Static);
	Plane->SetCollisionProfileName(UCollisionProfile::NoCollision_ProfileName);
}

void AFloor::SpawnCharacter(FVector Location, FRotator Rotation)
{
	UWorld* World = GetWorld();
	AActor* SpawnedCharacterRef = World->SpawnActor<AActor>(Character_To_Spawn, Location, Rotation);
}

void AFloor::SpawnTeleport(TSubclassOf<ATeleporter> Spawn_Teleport, FVector Location, FRotator Rotation, int Direction)
{
	UWorld* World = GetWorld();
	switch (Direction) {
	case('U'):
		Location.Y += -600.f;
		break;
	case('R'):
		Location.X += 1100.f;
		break;
	case('D'):
		Location.Y += 600.f;
		break;
	case('L'):
		Location.X += -1100.f;
		break;
	}
	Location.Z += 50.f;
	ATeleporter* SpawnedActorRef = World->SpawnActor<ATeleporter>(Spawn_Teleport, Location, Rotation);
	SpawnedActorRef->SetTeleportToLocation(Location, Direction);
}


void AFloor::SpawnFloor(TSubclassOf<ARoom> Spawn_Floor, FVector Location, FRotator Rotation, int RoomType)
{
	UWorld* World = GetWorld();
	ARoom* SpawnedActorRef = World->SpawnActor<ARoom>(Spawn_Floor, Location, Rotation);
	SpawnedActorRef->SetRoomLocation(Location.X, Location.Y);
	SpawnedActorRef->SetRoomType(RoomType);
	SpawnedActorRef->SetCanSpawn();
}

void AFloor::SpawnBossFloor(FVector Location, FRotator Rotation)
{
	UWorld* World = GetWorld();
	ARoom* SpawnedActorRef = World->SpawnActor<ARoom>(Boss_Floor_To_Spawn, Location, Rotation);
	SpawnedActorRef->SetRoomLocation(Location.X, Location.Y);
	SpawnedActorRef->SetCanSpawn();
	SpawnedActorRef->SetBossRoom();
}

void AFloor::SpawnStartFloor(FVector Location, FRotator Rotation)
{
	UWorld* World = GetWorld();
	AActor* SpawnedActorRef = World->SpawnActor<AActor>(Start_Floor_To_Spawn, Location, Rotation);
}

void AFloor::SpawnRock(FVector Location, FRotator Rotation)
{
	UWorld* World = GetWorld();
	AActor* SpawnedActorRef = World->SpawnActor<AActor>(Rock_To_Spawn, Location, Rotation);
}

void AFloor::SpawnSpike(FVector Location, FRotator Rotation)
{
	UWorld* World = GetWorld();
	AActor* SpawnedActorRef = World->SpawnActor<AActor>(Spike_To_Spawn, Location, Rotation);
}

void AFloor::SpawnHeart(FVector Location)
{
	UWorld* World = GetWorld();
	FVector tempLocation = FVector(Location.X, Location.Y, 50.0f);
	AActor* SpawnedActorRef = World->SpawnActor<AActor>(Heart_To_Spawn, tempLocation, FRotator(0, 180, 90));
}


void AFloor::SpawnWalls(TSubclassOf<AActor> Spawn_Wall, FVector Location, FRotator Rotation)
{
	UWorld* World = GetWorld();
	AActor* SpawnedActorRef = World->SpawnActor<AActor>(Spawn_Wall, Location, Rotation);
}

// Called when the game starts or when spawned
void AFloor::BeginPlay()
{
	Super::BeginPlay();

	srand(time(NULL));
	stack <int> posX, posY;
	int endPosX = 0, endPosY = 0, maxStack;
	int startX, startY;
	maxStack = posX.size();
	char maze[COL][ROW];
	char mazeDirection[COL][ROW];
	createBase(maze);
	createStart(maze, startX, startY);
	posX.push(startX);
	posY.push(startY);
	generateMaze(maze, mazeDirection, posX, posY, endPosX, endPosY, maxStack);
	cleanupMaze(maze, endPosX, endPosY);

	for (int y = 0; y < ROW; y++)
	{
		for (int x = 0; x < COL; x++)
		{
			if (maze[y][x] != ' ')
			{
				int LocationX = (x - START_X) * 24 * 100, LocationY = (y - START_Y) * 14 * 100;
				FVector Location = FVector(LocationX, LocationY, 0);
				FRotator Rotation = FRotator(0, 0, 0);

				if (x == START_X && y == START_Y)
				{
					//SpawnBossFloor(Location, Rotation);
					SpawnStartFloor(Location, Rotation);
				}
				else if (maze[y][x] == 'G')
				{
					SpawnBossFloor(Location, Rotation);
				}
				else
				{
					vector <int> rockLocationX, rockLocationY;
					vector <int> spikeLocationX, spikeLocationY;
					int RoomType = rand() % 25 + 1;
					SpawnFloor(Floor_To_Spawn, Location, Rotation, RoomType);
					if (maze[y][x] == 'T')
					{
						SpawnHeart(Location);
					}
					switch (RoomType)
					{
					case 1:
						Rock1(rockLocationX, rockLocationY);
						Spike1(spikeLocationX, spikeLocationY);
						break;
					case 2:
						Rock2(rockLocationX, rockLocationY);
						Spike2(spikeLocationX, spikeLocationY);
						break;
					case 3:
						Rock3(rockLocationX, rockLocationY);
						Spike3(spikeLocationX, spikeLocationY);
						break;
					case 4:
						Rock4(rockLocationX, rockLocationY);
						Spike4(spikeLocationX, spikeLocationY);
						break;
					case 5:
						Rock5(rockLocationX, rockLocationY);
						Spike5(spikeLocationX, spikeLocationY);
						break;
					case 6:
						Rock6(rockLocationX, rockLocationY);
						Spike6(spikeLocationX, spikeLocationY);
						break;
					case 7:
						Rock7(rockLocationX, rockLocationY);
						Spike7(spikeLocationX, spikeLocationY);
						break;
					case 8:
						Rock8(rockLocationX, rockLocationY);
						Spike8(spikeLocationX, spikeLocationY);
						break;
					case 9:
						Rock9(rockLocationX, rockLocationY);
						Spike9(spikeLocationX, spikeLocationY);
						break;
					case 10:
						Rock10(rockLocationX, rockLocationY);
						Spike10(spikeLocationX, spikeLocationY);
						break;
					case 11:
						Rock11(rockLocationX, rockLocationY);
						Spike11(spikeLocationX, spikeLocationY);
						break;
					case 12:
						Rock12(rockLocationX, rockLocationY);
						Spike12(spikeLocationX, spikeLocationY);
						break;
					case 13:
						Rock13(rockLocationX, rockLocationY);
						Spike13(spikeLocationX, spikeLocationY);
						break;
					case 14:
						Rock14(rockLocationX, rockLocationY);
						Spike14(spikeLocationX, spikeLocationY);
						break;
					case 15:
						Rock15(rockLocationX, rockLocationY);
						Spike15(spikeLocationX, spikeLocationY);
						break;
					case 16:
						Rock16(rockLocationX, rockLocationY);
						Spike16(spikeLocationX, spikeLocationY);
						break;
					case 17:
						Rock17(rockLocationX, rockLocationY);
						Spike17(spikeLocationX, spikeLocationY);
						break;
					case 18:
						Rock18(rockLocationX, rockLocationY);
						Spike18(spikeLocationX, spikeLocationY);
						break;
					case 19:
						Rock19(rockLocationX, rockLocationY);
						Spike19(spikeLocationX, spikeLocationY);
						break;
					case 20:
						Rock20(rockLocationX, rockLocationY);
						Spike20(spikeLocationX, spikeLocationY);
						break;
					case 21:
						Rock21(rockLocationX, rockLocationY);
						Spike21(spikeLocationX, spikeLocationY);
						break;
					case 22:
						Rock22(rockLocationX, rockLocationY);
						Spike22(spikeLocationX, spikeLocationY);
						break;
					case 23:
						Rock23(rockLocationX, rockLocationY);
						Spike23(spikeLocationX, spikeLocationY);
						break;
					case 24:
						Rock24(rockLocationX, rockLocationY);
						Spike24(spikeLocationX, spikeLocationY);
						break;
					case 25:
						Rock25(rockLocationX, rockLocationY);
						Spike25(spikeLocationX, spikeLocationY);
						break;
					}

					while (rockLocationX.empty() == false)
					{
						FVector RockLocation = FVector(LocationX + (rockLocationX.back() - 2 * START_X + 1) * 100, LocationY + (rockLocationY.back() - START_Y) * 100, 50);
						SpawnRock(RockLocation, FRotator(0, 0, 0));
						rockLocationX.pop_back();
						rockLocationY.pop_back();
					}
					while (spikeLocationX.empty() == false)
					{
						FVector SpikeLocation = FVector(LocationX + (spikeLocationX.back() - 2 * START_X + 1) * 100, LocationY + (spikeLocationY.back() - START_Y) * 100, 50);
						SpawnSpike(SpikeLocation, FRotator(0, 0, 0));
						spikeLocationX.pop_back();
						spikeLocationY.pop_back();
					}
				}
					lookForDoors(maze, x, y);

					switch (maze[y][x]) {
					case 'A':
						SpawnWalls(Spawn_Wall_A, Location, Rotation);
						SpawnTeleport(Spawn_Up_Teleport, Location, Rotation, 'U');
						break;
					case 'B':
						SpawnWalls(Spawn_Wall_B, Location, Rotation);
						SpawnTeleport(Spawn_Left_Teleport, Location, Rotation, 'L');
						break;
					case 'C':
						SpawnWalls(Spawn_Wall_C, Location, Rotation);
						SpawnTeleport(Spawn_Down_Teleport, Location, Rotation, 'D');
						break;
					case 'D':
						SpawnWalls(Spawn_Wall_D, Location, Rotation);
						SpawnTeleport(Spawn_Down_Teleport, Location, Rotation, 'D');
						SpawnTeleport(Spawn_Left_Teleport, Location, Rotation, 'L');
						break;
					case 'E':
						SpawnWalls(Spawn_Wall_E, Location, Rotation);
						SpawnTeleport(Spawn_Right_Teleport, Location, Rotation, 'R');
						break;
					case 'F':
						SpawnWalls(Spawn_Wall_F, Location, Rotation);
						SpawnTeleport(Spawn_Right_Teleport, Location, Rotation, 'R');
						SpawnTeleport(Spawn_Left_Teleport, Location, Rotation, 'L');
						break;
					case 'G':
						SpawnWalls(Spawn_Wall_G, Location, Rotation);
						SpawnTeleport(Spawn_Right_Teleport, Location, Rotation, 'R');
						SpawnTeleport(Spawn_Down_Teleport, Location, Rotation, 'D');
						break;
					case 'H':
						SpawnWalls(Spawn_Wall_H, Location, Rotation);
						SpawnTeleport(Spawn_Right_Teleport, Location, Rotation, 'R');
						SpawnTeleport(Spawn_Down_Teleport, Location, Rotation, 'D');
						SpawnTeleport(Spawn_Left_Teleport, Location, Rotation, 'L');
						break;
					case 'I':
						SpawnWalls(Spawn_Wall_I, Location, Rotation);
						SpawnTeleport(Spawn_Up_Teleport, Location, Rotation, 'U');
						break;
					case 'J':
						SpawnWalls(Spawn_Wall_J, Location, Rotation);
						SpawnTeleport(Spawn_Up_Teleport, Location, Rotation, 'U');
						SpawnTeleport(Spawn_Left_Teleport, Location, Rotation, 'L');
						break;
					case 'K':
						SpawnWalls(Spawn_Wall_K, Location, Rotation);
						SpawnTeleport(Spawn_Up_Teleport, Location, Rotation, 'U');
						SpawnTeleport(Spawn_Down_Teleport, Location, Rotation, 'D');
						break;
					case 'L':
						SpawnWalls(Spawn_Wall_L, Location, Rotation);
						SpawnTeleport(Spawn_Up_Teleport, Location, Rotation, 'U');
						SpawnTeleport(Spawn_Down_Teleport, Location, Rotation, 'D');
						SpawnTeleport(Spawn_Left_Teleport, Location, Rotation, 'L');
						break;
					case 'M':
						SpawnWalls(Spawn_Wall_M, Location, Rotation);
						SpawnTeleport(Spawn_Up_Teleport, Location, Rotation, 'U');
						SpawnTeleport(Spawn_Right_Teleport, Location, Rotation, 'R');
						break;
					case 'N':
						SpawnWalls(Spawn_Wall_N, Location, Rotation);
						SpawnTeleport(Spawn_Up_Teleport, Location, Rotation, 'U');
						SpawnTeleport(Spawn_Right_Teleport, Location, Rotation, 'R');
						SpawnTeleport(Spawn_Left_Teleport, Location, Rotation, 'L');
						break;
					case 'O':
						SpawnWalls(Spawn_Wall_O, Location, Rotation);
						SpawnTeleport(Spawn_Up_Teleport, Location, Rotation, 'U');
						SpawnTeleport(Spawn_Right_Teleport, Location, Rotation, 'R');
						SpawnTeleport(Spawn_Down_Teleport, Location, Rotation, 'D');
						break;
					case 'P':
						SpawnWalls(Spawn_Wall_P, Location, Rotation);
						SpawnTeleport(Spawn_Up_Teleport, Location, Rotation, 'U');
						SpawnTeleport(Spawn_Right_Teleport, Location, Rotation, 'R');
						SpawnTeleport(Spawn_Down_Teleport, Location, Rotation, 'D');
						SpawnTeleport(Spawn_Left_Teleport, Location, Rotation, 'L');
						break;
					}
			}
		}
	}
	SpawnCharacter(FVector(10.f, 10.f, 70.f), FRotator(0,0,0));
}

// Called every frame
void AFloor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

 