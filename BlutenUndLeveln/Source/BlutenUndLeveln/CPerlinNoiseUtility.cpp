// ©Playtypus Games 2015


#include "BlutenUndLeveln.h"
#include "CPerlinNoiseUtility.h"
#include <iostream>
#include <noise.h>

using namespace noise;

void UCPerlinNoiseUtility::PerlinTest(float &random)
{
	//module::Perlin myModule;
	noise::module::Perlin myModule;
	double value = myModule.GetValue(1.25, 0.75, 0.50);
	random = value;
}