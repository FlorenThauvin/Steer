#pragma once
#include "CoreMinimal.h"
#include "VehiculeIA.h"
#include "VehiculeCircuit.generated.h"

UENUM()
enum AlgoCuircuit
{
	CIRCUIT	  UMETA(DisplayName = "Circuit"),
	ONE_WAY	  UMETA(DisplayName = "One path"),
	TWO_WAY   UMETA(DisplayName = "Two path"),
};

UCLASS()
class TP1_IA_API AVehiculeCircuit : public AVehiculeIA
{
	GENERATED_BODY()

public:
	AVehiculeCircuit();

protected:
	virtual void BeginPlay() override;
	bool IsArrived = false;
	bool IsOnTarget = false;
	int Direction = 1;
	int Index = 0;
	float CurrentTime = 0;
	UPROPERTY(EditAnywhere, Category = "Algorithme")
	TEnumAsByte<AlgoCuircuit> AlgoCircuit;
	UPROPERTY(EditAnywhere, Category = "Path")
	TArray<AVehicule*> ListTargets;
	UPROPERTY(EditAnywhere, Category = "Path")
	float DistanceChangeTarget;
	UPROPERTY(EditAnywhere, Category = "Path")
	float Time;

public:
	virtual void Tick(float DeltaTime) override;
	FVector CalculDirection();
	void TargCirc();
	void TargOne();
	void TargTwo(float DeltaTime);
};
