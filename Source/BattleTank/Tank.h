// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTankDelegate);

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Called by the engine when actor takes damage
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser) override;

public:	
	UFUNCTION(BlueprintPure, Category = "Health")
		float GetHealthPercentage() const;
	FTankDelegate OnDeath;
	
private:
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		float MaxHealth = 100.0f;
	float CurrentHealth = MaxHealth;
};
