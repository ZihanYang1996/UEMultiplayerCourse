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

	TextRender = CreateDefaultSubobject<UTextRenderComponent>(TEXT("TextRender"));
	TextRender->SetupAttachment(CubeMesh);

	TextRender_ReplicatedVar = CreateDefaultSubobject<UTextRenderComponent>(TEXT("ReplicatedVar"));
	TextRender_ReplicatedVar->SetupAttachment(CubeMesh);

	ReplicatedVar = 100.0f;

	SetReplicates(true);
}

// Called when the game starts or when spawned
void AMyBox::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		TextRender->SetText(FText::FromString(TEXT("Has Authority")));
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

	if (APlayerController* PC = GetWorld()->GetFirstPlayerController())
	{
		if (PC->IsInputKeyDown(EKeys::SpaceBar) && HasAuthority())
		{
			ReplicatedVar = FMath::RandRange(0.0f, 100.0f);
		}
	}
	TextRender_ReplicatedVar->SetText(FText::FromString(FString::Printf(TEXT("ReplicatedVar: %f"), ReplicatedVar)));
}

void AMyBox::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AMyBox, ReplicatedVar);
}
