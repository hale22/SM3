#pragma once

#include <cmath>
#include <iostream>
#include <map>
#include <string>

#include "atmmodel.hpp"

double SM3::AtmModel::CalcPotHeight(int height) const {
	if (height < kMinHeight || height > kMaxHeight)
		return kErrHeight;

	return  (kRadEarth*height)/(kRadEarth + height);
}

double SM3::AtmModel::CalcAccGrav(int height) const {
	if (height < kMinHeight || height > kMaxHeight)
		return kErrHeight;

	return kStandAccGrav*pow((kRadEarth/(kRadEarth+height)), 2);
}

double  SM3::AtmModel::CalcTemp(int height) const {
	if (height < kMinHeight || height > kMaxHeight)
		return kErrHeight;

	double geo_pot_height = CalcPotHeight(height); // или брать из data_

	double temp_lower;
	double beta_gradient;
	if (height >= -	2000 && height < 0) {
		temp_lower = 301.15;
		beta_gradient = -0.0065;
	}
	if (height >= 0 && height < 11000) {
		temp_lower = 288.15;
		beta_gradient = -0.0065;
	}
	if (height >= 11000 && height < 20000) {
		temp_lower = 216.65;
		beta_gradient = 0;
	}
	if (height >= 20000 && height < 32000) {
		temp_lower = 216.65;
		beta_gradient = -0.0065;
	}
}