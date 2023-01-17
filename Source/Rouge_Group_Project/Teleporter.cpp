// Fill out your copyright notice in the Description page of Project Settings.


#include "Teleporter.h"


// Sets default values
ATeleporter::ATeleporter()
{
 	//Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Create Root Static Mesh
	Teleporter = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Teleporter"));
	RootComponent = Teleporter;

	//Create Collision Box
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Collsion Box"));
	CollisionBox->SetupAttachment(Teleporter);
}

void ATeleporter::Teleport(TSubclassOf < AActor> Character)
{
	GetWorld()->GetFirstPlayerController()->GetPawn()->SetActorLocation(TeleportToLocation);
	GetWorld()->GetFirstPlayerController()->GetViewTarget()->SetActorLocation(NewCameraLocation);
}

void ATeleporter::OnComponentBeginOverlap(class UBoxComponent* Component, class AActor* Character, class UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Character->IsA(TriggerClass))
	{
		Teleport(Character_To_Teleport);
	}
}

void ATeleporter::SetTeleportToLocation(FVector Location, int TeleportDirection)
{
	FVector Distance;
	TeleportFromLocation = GetActorLocation();
	FVector PlayerLocation = TeleportFromLocation;
	FVector CameraLocation = TeleportFromLocation;
	switch (TeleportDirection) {
	case 'U':
		PlayerLocation += FVector(0.f, -325.f, 0.f);
		CameraLocation += FVector(0.f, -800.f, 0.f);
		break;
	case 'R':
		PlayerLocation += FVector(300.f, 0.f, 0.f);
		CameraLocation += FVector(1300.f, 0.f, 0.f);

		break;
	case 'D':
		PlayerLocation += FVector(0.f, 325.f, 0.f);
		CameraLocation += FVector(0.f, 800.f, 0.f);
		break;
	case 'L':
		PlayerLocation += FVector(-300.f, 0.f, 0.f);
		CameraLocation += FVector(-1300.f, 0.f, 0.f);
		break;
	}
	TeleportToLocation = PlayerLocation;
	NewCameraLocation = CameraLocation;
}

// Called when the game starts or when spawned
void ATeleporter::BeginPlay()
{
	Super::BeginPlay();
	// delay when enter door
	//GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ATeleporter::DelayTeleport, 1.0f, false);


	FScriptDelegate DelegateSubscribeer;
	DelegateSubscribeer.BindUFunction(this, "OnComponentBeginOverlap");
	CollisionBox->OnComponentBeginOverlap.Add(DelegateSubscribeer);


	SetActorTickEnabled(false);
}

// Called every frame
void ATeleporter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

