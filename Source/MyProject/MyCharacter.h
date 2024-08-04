// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"
#include "MyCharacter.generated.h"


UCLASS()
class MYPROJECT_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharacter();
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	class UInputMappingContext* DefaultMappingContext;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	class UInputAction* MoveAction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	class UInputAction* LookAction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Visuals")
	 UStaticMeshComponent* visualMesh;

	 UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	 float movementSpeed = 15.0f;
	 UPROPERTY(EditAnywhere, BluePrintReadOnly,Category = "Camera")
	 class UCameraComponent* Camera;
	 UPROPERTY(EditAnywhere, BluePrintReadOnly, Category = "Camera")
	 class USpringArmComponent* springArm;
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Player")

	class USceneComponent* playerModel;

private:
	virtual void OnMove(const FInputActionValue& Value);
	virtual void OnLook(const FInputActionValue& value);

};
