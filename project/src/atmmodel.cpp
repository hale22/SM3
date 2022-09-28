#include <cmath>
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <string>

#include "atmmodel.hpp"

double SM3::AtmModel::CalcPotHeight() const {
	if (height_ < kMinHeight || height_ > kMaxHeight)
		return kErrHeight;

	return floor((double(kRadEarth)*double(height_))/(kRadEarth + height_));
}

double SM3::AtmModel::CalcAccGrav() const {
	if (height_ < kMinHeight || height_ > kMaxHeight)
		return kErrHeight;

	return kStandAccGrav*pow((kRadEarth/(kRadEarth+height_)), 2);
}

double SM3::AtmModel::CalcTemp() const {
	if (height_ < kMinHeight || height_ > kMaxHeight)
		return kErrHeight;

	double geo_pot_height = CalcPotHeight();  //  или брать из data_

	double temp_lower = 0;
	double beta_gradient = 0;
	double geo_pot_height_lower = 0;
	if (CompareDouble(geo_pot_height, -2000) && geo_pot_height < 0) {
		temp_lower = 301.15;
		beta_gradient = -0.0065;
		geo_pot_height_lower = -2000;
	}
	if (CompareDouble(geo_pot_height, 0) && geo_pot_height < 11000) {
		temp_lower = 288.15;
		beta_gradient = -0.0065;
		geo_pot_height_lower = 0;
	}
	if (CompareDouble(geo_pot_height, 11000) && geo_pot_height < 20000) {
		temp_lower = 216.65;
		beta_gradient = -0.0065;
		geo_pot_height_lower = 11000;
	}
	if (CompareDouble(geo_pot_height, 20000) && geo_pot_height < 32000) {
		temp_lower = 216.65;
		beta_gradient = 0;
		geo_pot_height_lower = 20000;
	}
	if (CompareDouble(geo_pot_height, 32000) && geo_pot_height < 47000) {
		temp_lower = 228.65;
		beta_gradient = 0.0010;
		geo_pot_height_lower = 32000;
	}
	if (CompareDouble(geo_pot_height, 47000) && geo_pot_height < 51000) {
		temp_lower = 270.65;
		beta_gradient = 0.0028;
		geo_pot_height_lower = 47000;
	}
	if (CompareDouble(geo_pot_height, 51000) && geo_pot_height < 71000) {
		temp_lower = 270.65;
		beta_gradient = 0;
		geo_pot_height_lower = 51000;
	}
	if (CompareDouble(geo_pot_height, 71000) && geo_pot_height <= kMaxHeight) {
		temp_lower = 270.65;
		beta_gradient = -0.0028;
		geo_pot_height_lower = 71000;
	}
	return temp_lower + beta_gradient * (geo_pot_height - geo_pot_height_lower);
}

bool SM3::AtmModel::FillDataMap() {
	data_["GeoPotHeight"] = CalcPotHeight();
	data_["AccGrav"] = CalcAccGrav();
	data_["Temperature"] = CalcTemp();
	return true;
}

SM3::AtmModel::AtmModel(int height) : height_(height) {
	FillDataMap();
}

bool SM3::AtmModel::operator() (int height) {
	height_ = height;
	FillDataMap();
	return true;
}

bool SM3::CompareDouble(const double first, const double second, const double precis) {
  /*if (std::abs(first - second) >= (precis*std::numeric_limits<double>::epsilon()))
    return false;*/
	bool equality_temp =
	std::fabs(first - second) <= std::numeric_limits<double>::epsilon() * std::fabs(first + second)
    * precis
    || std::fabs(first - second) < std::numeric_limits<double>::min()*precis;
  return equality_temp || first > second;
}

bool SM3::AtmModelOutput::PrintHeight(std::ostream& os) const {
	os << "Высота: " <<
	height_ << std::endl;
	return true;
}

bool SM3::AtmModelOutput::PrintPotHeight(std::ostream& os) {
	os << "Геопотенциальная высота: " <<
	std::setprecision(kDoublePrecis) <<
	data_["GeoPotHeight"] << std::endl;
	return true;
}

bool SM3::AtmModelOutput::PrintAccGrav(std::ostream& os) {
	os << "Ускорение свободного падения: " <<
	std::setprecision(kDoublePrecis) <<
	data_["AccGrav"] << std::endl;
	return true;
}

bool SM3::AtmModelOutput::PrintTemp(std::ostream& os) {
	os << "Температура: " <<
	std::setprecision(kDoublePrecis) <<
	data_["Temperature"] << std::endl;
	return true;
}

std::ostream& operator<<(std::ostream& os, SM3::AtmModelOutput& atm_model) {
	atm_model.PrintHeight(os);
	atm_model.PrintPotHeight(os);
	atm_model.PrintAccGrav(os);
	atm_model.PrintTemp(os);
	return os;
}


//  завершенные todo:

//  todo: переделать сравнение даблов с помощью CompareDouble
