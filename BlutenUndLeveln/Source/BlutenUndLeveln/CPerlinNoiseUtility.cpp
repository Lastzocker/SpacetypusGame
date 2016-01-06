// ©Playtypus Games 2015


#include "BlutenUndLeveln.h"
#include "CPerlinNoiseUtility.h"
#include <iostream>
#include <noise.h>

using namespace noise;

void UCPerlinNoiseUtility::PerlinTest(const float &x, const float &y, const float &z, float &random)
{
	//module::Perlin myModule;
	noise::module::Perlin myModule;
	double value = myModule.GetValue(x, y, z);
	random = value;
}