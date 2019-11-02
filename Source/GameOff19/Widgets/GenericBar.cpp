// Fill out your copyright notice in the Description page of Project Settings.


#include "GenericBar.h"


void UGenericBar::Update(float NewValue)
{
	if (NewValue != value)
	{
		float delta = NewValue - value; 
		value = NewValue;
		if (delta > 0)
			OnBarIncrease(delta);
		else
			OnBarDecease(-delta); 

		
	}

}