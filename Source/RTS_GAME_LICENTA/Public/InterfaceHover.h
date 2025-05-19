// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InterfaceHover.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInterfaceHover : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class RTS_GAME_LICENTA_API IInterfaceHover
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Hover")
		void OnHoverBegin(bool Enemy = false);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Hover")
		void OnHoverEnd();

};
