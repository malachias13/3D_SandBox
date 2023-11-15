// Copyright 2023, Malachias Harris, All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SpectatorPawn.h"
#include "PlayerSpectator.generated.h"

/**
 * 
 */
UCLASS()
class VECTOR3D_API APlayerSpectator : public ASpectatorPawn
{
	GENERATED_BODY()

public:
	APlayerSpectator();

private:
	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UPhysicsHandleComponent* PhysicsHandleComponent;

	APlayerController* PlayerController;
	bool bHoldingClick;

protected:
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;

	void ClickPressButton();
	void ClickReleaseButton();
	void RestartMap();

public:
	virtual void Tick(float DeltaTime) override;

private:
	const FHitResult PerfromLineTraceFromMouse();
	void HandleUpdatePhysicsActor();


	
};
