#include "VehiculePlayer.h"
#include "VehiculeIA.h"
#include <Components/InputComponent.h>

AVehiculePlayer::AVehiculePlayer(){PrimaryActorTick.bCanEverTick = true;}

void AVehiculePlayer::BeginPlay(){
	Super::BeginPlay();
	BindInput();
}

void AVehiculePlayer::BindInput(){
	InputComponent = NewObject<UInputComponent>(this);
	InputComponent->RegisterComponent();
	if (InputComponent){
		InputComponent->BindAxis("MoveForward", this, &AVehiculePlayer::MoveForward);
		InputComponent->BindAxis("MoveRight", this, &AVehiculePlayer::MoveRight);
		InputComponent->BindAction("ChangeAlgo", IE_Pressed, this, &AVehiculePlayer::Change);
		EnableInput(GetWorld()->GetFirstPlayerController());
	}
}


void AVehiculePlayer::Tick(float DeltaTime){
	FVector SteeringForce = Truncate(Direction, MaxForce);
	FVector Acceleration = SteeringForce / Mass;
	Velocity = Truncate(Velocity + Acceleration, MaxSpeed);
	SetActorRotation(FRotator(Velocity.Rotation()));
	SetActorLocation(GetActorLocation() + Velocity);
}

void AVehiculePlayer::Change(){
	AVehiculeIA* IA = Cast<AVehiculeIA>(Vehicule);
	if (IA) IA->ChangeAlgo();
}

void AVehiculePlayer::MoveForward(float f){Direction = FVector(Direction.X + f * 10, Direction.Y, Direction.Z);}
void AVehiculePlayer::MoveRight(float f){Direction = FVector(Direction.X, Direction.Y + f *10 , Direction.Z);}