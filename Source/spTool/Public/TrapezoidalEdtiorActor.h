// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/Classes/Components/SplineComponent.h"
#include "GameFramework/Actor.h"
#include "TrapezoidalEdtiorActor.generated.h"

UCLASS()
class SPTOOL_API ATrapezoidalEdtiorActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATrapezoidalEdtiorActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:

	// house setting
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "BottomLong", Category = "A_Parameter")
		float BottomLong;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "Height", Category = "A_Parameter")
		float Height;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,meta = (ClampMin = "1.0", ClampMax = "89.0"), DisplayName = "LeftDeg", Category = "A_Parameter")
		float LeftDeg;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "1.0", ClampMax = "89.0"), DisplayName = "RightDeg", Category = "A_Parameter")
		float RightDeg;
public:
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "EditorCurve", Keywords = "EditorCurve"), Category = "TrapezoidalEdtiorActor")
		TArray<FVector> EditorCurve(USplineComponent* splineCom);

public:
	/*
	* 半圆的段数
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "SemicircleNum", Category = "B_Parameter")
		int32 SemicircleNum;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "L_Semicircle", Category = "B_Parameter")
		float L_Semicircle;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "Height_Semicircle", Category = "B_Parameter")
		float Height_Semicircle;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "A_Quadrangle", Category = "B_Parameter")
		float A_Quadrangle;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "Height_Quadrangle", Category = "B_Parameter")
		float Height_Quadrangle;


	UFUNCTION(BlueprintCallable, meta = (DisplayName = "EditorSemicircleAndQuadrangleCurve", Keywords = "EditorSemicircleAndQuadrangleCurve"), Category = "TrapezoidalEdtiorActor")
		void EditorSemicircleAndQuadrangleCurve(USplineComponent* splineCom);

	TArray<FVector> GetSemicircleAndQuadranglePoints(USplineComponent* splineCom);

public:
/*
* 凸型设置
*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "bottom_h", Category = "C_Parameter")
		float bottom_h;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "left_a", Category = "C_Parameter")
		float left_a;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "top_h", Category = "C_Parameter")
		float top_h;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "top_", Category = "C_Parameter")
		float top_;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "right_a", Category = "C_Parameter")
		float right_a;

		/*
		* 编辑凸型曲线
		*/
	TArray<FVector> EditorConvexCurve(USplineComponent* splineCom);
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "SetConvexSplineComPoints", Keywords = "SetConvexSplineComPoints"), Category = "TrapezoidalEdtiorActor")
	void SetConvexSplineComPoints(USplineComponent* splineCom);



	UFUNCTION(BlueprintCallable, meta = (DisplayName = "GetConsecutivePointXY", Keywords = "GetConsecutivePointXY"), Category = "TrapezoidalEdtiorActor")
		void GetConsecutivePointXY(AActor* act);
};
