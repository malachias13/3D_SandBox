// Copyright 2023, Malachias Harris, All rights reserved


#include "PlayerSpectator.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "GameFramework/InputSettings.h"
#include <Kismet/GameplayStatics.h>

APlayerSpectator::APlayerSpectator()
{
	PhysicsHandleComponent = CreateDefaultSubobject<UPhysicsHandleComponent>(TEXT("PhysicsHandle"));
	bHoldingClick = false;
}

void APlayerSpectator::BeginPlay()
{
	Super::BeginPlay();

	PlayerController = Cast<APlayerController>(GetController());
	if (PlayerController) {
		PlayerController->bShowMouseCursor = true;
	}

}

void APlayerSpectator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	HandleUpdatePhysicsActor();
}

const FHitResult APlayerSpectator::PerfromLineTraceFromMouse()
{
	FHitResult HitResult;
	if (!PlayerController) { return HitResult; }
	FVector WorldLocation;
	FVector WorldDirection;
	PlayerController->DeprojectMousePositionToWorld(WorldLocation, WorldDirection);


	FVector end = WorldDirection * 10000 + WorldLocation;
	GetWorld()->LineTraceSingleByChannel(HitResult, WorldLocation, end, ECollisionChannel::ECC_Visibility);
	return HitResult;
}

void APlayerSpectator::HandleUpdatePhysicsActor()
{
	if (bHoldingClick) {
		FHitResult HitResult = PerfromLineTraceFromMouse();
		if (HitResult.GetComponent() && HitResult.GetComponent()->GetCollisionObjectType() == ECollisionChannel::ECC_PhysicsBody) {
			HitResult.GetComponent()->WakeRigidBody();
		}
		PhysicsHandleComponent->SetTargetLocation(HitResult.ImpactPoint);
	}
}


void APlayerSpectator::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);
	
	PlayerInputComponent->BindAction("Click", IE_Pressed, this, &APlayerSpectator::ClickPressButton);
	PlayerInputComponent->BindAction("Click", IE_Released, this, &APlayerSpectator::ClickReleaseButton);
	PlayerInputComponent->BindAction("Restart", IE_Pressed, this, &APlayerSpectator::RestartMap);
}

void APlayerSpectator::ClickPressButton()
{
	if (!PlayerController) { return; }
	FHitResult CursorHitResult;
	if (PlayerController->GetHitResultUnderCursor(ECollisionChannel::ECC_PhysicsBody, true, CursorHitResult)) {
		bHoldingClick = true;
		FHitResult HitResult = PerfromLineTraceFromMouse();

		if (HitResult.GetComponent() && HitResult.GetComponent()->GetCollisionObjectType() == ECollisionChannel::ECC_PhysicsBody) {
			HitResult.GetComponent()->WakeRigidBody();
		}
		PhysicsHandleComponent->GrabComponentAtLocationWithRotation(CursorHitResult.GetComponent(), {},
			HitResult.ImpactPoint, FRotator{});
	}
}

void APlayerSpectator::ClickReleaseButton()
{
	bHoldingClick = false;
	PhysicsHandleComponent->ReleaseComponent();
}

void APlayerSpectator::RestartMap()
{
	UGameplayStatics::OpenLevel(this, *UGameplayStatics::GetCurrentLevelName(this));
}

