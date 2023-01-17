// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ConstructorHelpers.h"
#include "GameFramework/Actor.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/DefaultPawn.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h" 

#include <string>

#include "Teleporter.generated.h"

UCLASS( meta = (BlueprintSpawnableComponent) )
class ROUGE_GROUP_PROJECT_API ATeleporter : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATeleporter();

	UFUNCTION(BlueprintCallable)
		void Teleport(TSubclassOf<AActor> Character);

	UPROPERTY(EditAnywhere)
		TSubclassOf<AActor> Character_To_Teleport;

	UFUNCTION()
		void SetTeleportToLocation(FVector Location, int TeleportDirection);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
		void OnComponentBeginOverlap(class UBoxComponent* Component, class AActor* Character, class UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UClass* TriggerClass = ADefaultPawn::StaticClass();
	//Delay function
//	void DelayTeleport();
private:
	// Static mesh - Set to 1x1x.1 door Teleporter pad 
	// Use for artwork?
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* Teleporter;

	UPROPERTY(EditDefaultsOnly)
		UBoxComponent* CollisionBox;

	FVector TeleportFromLocation;
	FVector TeleportToLocation;
	FVector OldCameraLocation;
	FVector NewCameraLocation;

//	FTimerHandle TimerHandle;

public: 
	virtual void Tick(float DeltaTime) override;
};
