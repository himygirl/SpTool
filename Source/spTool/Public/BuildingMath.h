#pragma once
#include "CoreMinimal.h"
#include "Engine/Classes/Components/SplineComponent.h"


struct twoPoints 
{
 FVector A;
 FVector B;
};

class BuildingMath
{
public:
	BuildingMath();
	~BuildingMath();


	static BuildingMath& Get();

	/*
	* 得到一个点，xy 轴方向的相邻点，并依据标签得到需要的点位
	*/
	TArray<twoPoints> GetConsecutivePointXY(const TArray<FVector>& points, const FString& tag);


};