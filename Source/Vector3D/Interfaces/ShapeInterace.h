// Copyright 2023, Malachias Harris, All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ShapeInterace.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UShapeInterace : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class VECTOR3D_API IShapeInterace
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	
	virtual void ChangeMeshColor(FLinearColor color) = 0;
};
