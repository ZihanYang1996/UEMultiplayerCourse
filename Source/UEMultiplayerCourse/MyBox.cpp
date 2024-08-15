// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBox.h"

#include "Components/TextRenderComponent.h"
#include "Net/UnrealNetwork.h"
#include "SparseVolumeTexture/SparseVolumeTexture.h"

// Sets default values
AMyBox::AMyBox()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CubeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CubeMesh"));
	SetRootComponent(CubeMesh);
	CubeMesh->SetIsReplicated(true);  // Component is also need to be set manually to replicate

	TextRender = CreateDefaultSubobject<UTextRenderComponent>(TEXT("TextRender"));
	TextRender->SetupAttachment(CubeMesh);

	TextRender_ReplicatedVar = CreateDefaultSubobject<UTextRenderComponent>(TEXT("ReplicatedVar"));
	TextRender_ReplicatedVar->SetupAttachment(CubeMesh);

	ReplicatedVar = 100.0f;

	
	
}

// Called when the game starts or when spawned
void AMyBox::BeginPlay()
{
	Super::BeginPlay();

	SetReplicates(true);
	SetReplicateMovement(true);
	
	if (HasAuthority())
	{
		TextRender->SetText(FText::FromString(TEXT("Has Authority")));
		GetWorld()->GetTimerManager().SetTimer(TestTimerHandle, this, &AMyBox::DecreaseReplicatedVar, 2.0f, false);
	}
	else
	{
		TextRender->SetText(FText::FromString(TEXT("No Authority")));
	}
}

// Called every frame
void AMyBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
#if 0	
	if (APlayerController* PC = GetWorld()->GetFirstPlayerController())
	{
		if (PC->IsInputKeyDown(EKeys::SpaceBar) && HasAuthority())
		{
			ReplicatedVar = FMath::RandRange(0.0f, 100.0f);
			OnRep_REplicatedVar();
		}
	}
#endif	
	TextRender_ReplicatedVar->SetText(FText::FromString(FString::Printf(TEXT("ReplicatedVar: %f"), ReplicatedVar)));
}

void AMyBox::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AMyBox, ReplicatedVar);
}

void AMyBox::OnRep_REplicatedVar()
{
	if (HasAuthority())
	{
		// GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Call from Server")));
		FVector CurrenLocation = GetActorLocation();
		SetActorLocation(FVector(CurrenLocation.X, CurrenLocation.Y, CurrenLocation.Z + 50));
	}
	else
	{
		// GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Call from: %d"), static_cast<int>(GPlayInEditorID)));
	}
}

void AMyBox::DecreaseReplicatedVar()
{
	ReplicatedVar -= 1.0f;
	OnRep_REplicatedVar();
	if (ReplicatedVar > 0.0f)
	{
		GetWorld()->GetTimerManager().SetTimer(TestTimerHandle, this, &AMyBox::DecreaseReplicatedVar, 2.0f, false);
	}
	else
	{
		ReplicatedVar = 0.0f;
	}
}
