#pragma once
#include "CoreMinimal.h"
#include "Vehicule.h"
#include "VehiculePlayer.generated.h"


UCLASS()
class TP1_IA_API AVehiculePlayer : public AVehicule
{
	GENERATED_BODY()
	
public:
	virtual void Tick(float DeltaTime) override;
	AVehiculePlayer();
	void Change();
	void MoveForward(float f);
	void MoveRight(float f);

protected:
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere)
	AVehicule* Vehicule;
	FVector Direction;
	void BindInput();
};
