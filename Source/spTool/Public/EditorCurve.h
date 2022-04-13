#pragma once
#include "CoreMinimal.h"
#include "Engine/Classes/Components/SplineComponent.h"

class BuildingEditorCurve
{
public:
	BuildingEditorCurve();
	~BuildingEditorCurve();


	static BuildingEditorCurve& Get();


	/*
	* 得到曲线其余的点序号
	*/
	TArray<int32> GetSplineOtherPoint(USplineComponent* SplineComp);
	/*
	*批量删除曲线点的方法
	*/
	void BatchDeleteSplinePoint(USplineComponent* SplineComp, const TArray<int32>& SelectedKeys);
	/*
	* 批量添加曲线点
	*/
	void BatchAddSplinePoint(USplineComponent* SplineComp, const int32& SideNum);
};