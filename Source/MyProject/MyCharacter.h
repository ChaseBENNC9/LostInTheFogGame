// Fill out your copyright notice in the Description page of Project Settings.
//Header File of My Character class
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"
#include "Brazier.h"  
#include "MyCharacter.generated.h"


UCLASS()
class MYPROJECT_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharacter();
	


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// The Brazier that the character is closest to
	ABrazier* focusedBrazier;
	ABrazier* lastActivatedBrazier;

	//Napping Context which holds Key mappings values for input actions
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	class UInputMappingContext* DefaultMappingContext;

	//The Input Action assigned to Moving
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	class UInputAction* MoveAction;
	//Input Action Assigned to interacting
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	class UInputAction* InteractAction;
	//Input Action Assigned to Jumping
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	class UInputAction* JumpAction;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Input")
	class UInputAction* SpecialAction;
	//The mesh component of the character
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Visuals")
	 UStaticMeshComponent* visualMesh;

	 //Moving speed modifier
	 UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	 float movementSpeed = 15.0f;

	 //camera component
	 UPROPERTY(EditAnywhere, BluePrintReadOnly,Category = "Camera")
	 class UCameraComponent* Camera;

	 //Spring arm component will keep the camera at a constant position when the player turns
	 UPROPERTY(EditAnywhere, BluePrintReadOnly, Category = "Camera")
	 class USpringArmComponent* springArm;
	 //The Parent of the visuals of the character
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Player")
	class USceneComponent* playerModel;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
private:
	virtual void OnMove(const FInputActionValue& Value);
	virtual void OnInteract(const FInputActionValue& value);
	virtual void BeginJump(const FInputActionValue& value);
	virtual void EndJump(const FInputActionValue& value);
	virtual void OnSpecial(const FInputActionValue& value);
	//The fuel left in your lamp before it will be depleted.
	float fuel;


};
