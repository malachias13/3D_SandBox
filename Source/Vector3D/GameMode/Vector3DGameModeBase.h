// Copyright 2023, Malachias Harris, All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Vector3DGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class VECTOR3D_API AVector3DGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

protected:

	virtual void BeginPlay() override;

public:
	TArray<AActor*> ShapeActors;
	
};
