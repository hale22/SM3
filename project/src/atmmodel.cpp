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

	return (double(kRadEarth)*height_)/double((kRadEarth + height_));
}

double SM3::AtmModel::CalcAccGrav() const  {
	if (height_ < kMinHeight || height_ > kMaxHeight)
		return kErrHeight;

	return kStandAccGrav*pow((double(kRadEarth)/(kRadEarth+height_)), 2);
}

double SM3::AtmModel::CalcTemp() {
	if (height_ < kMinHeight || height_ > kMaxHeight)
		return kErrHeight;

	return constants_["TempLower"] + constants_["BetaGradient"] * (data_["GeoPotHeight"] - constants_["GeoPotLower"]);
}

double SM3::AtmModel::CalcPressure() {
	if (height_ < kMinHeight || height_ > kMaxHeight)
		return kErrHeight;

	if (constants_["BetaGradient"] != 0) {
		return constants_["PressureLower"] /
			pow((constants_["TempLower"] + constants_["BetaGradient"] * (data_["GeoPotHeight"] - constants_["GeoPotLower"]))
					/ constants_["TempLower"],
				(kStandAccGrav / (constants_["BetaGradient"] * kUnitGas)));
	} else {
			return constants_["PressureLower"] / pow(10, (((0.434294 * kStandAccGrav) / (kUnitGas * data_["Temperature"] )) *
				(data_["GeoPotHeight"] - constants_["GeoPotLower"])));
	}
}

double SM3::AtmModel::CalcDensity() {
	if (height_ < kMinHeight || height_ > kMaxHeight)
		return kErrHeight;

	return (data_["Pressure"] * kMolarMass) / (data_["Temperature"] * kUniversalGas);
}

double SM3::AtmModel::CalcSoundSp() {
	if (height_ < kMinHeight || height_ > kMaxHeight)
		return kErrHeight;

	return kSoundSpeed * sqrt(data_["Temperature"]);
}

bool SM3::AtmModel::DefineConstants() {
	double geo_pot_height = data_["GeoPotHeight"];
	if (CompareDouble(geo_pot_height, -2000) && geo_pot_height < 0) {
		constants_["TempLower"] = kTempLower["First Range"];
		constants_["BetaGradient"] = kBetaGradient["First Range"];
		constants_["GeoPotLower"] = kGeoPotLower["First Range"];
		constants_["PressureLower"] = kPressureLower["First Range"];
	}
	if (CompareDouble(geo_pot_height, 0) && geo_pot_height < 11000) {
		constants_["TempLower"] = kTempLower["Second Range"];
		constants_["BetaGradient"] = kBetaGradient["Second Range"];
		constants_["GeoPotLower"] = kGeoPotLower["Second Range"];
		constants_["PressureLower"] = kPressureLower["Second Range"];
	}
	if (CompareDouble(geo_pot_height, 11000) && geo_pot_height < 20000) {
		constants_["TempLower"] = kTempLower["Third Range"];
		constants_["BetaGradient"] = kBetaGradient["Third Range"];
		constants_["GeoPotLower"] = kGeoPotLower["Third Range"];
		constants_["PressureLower"] = kPressureLower["Third Range"];
	}
	if (CompareDouble(geo_pot_height, 20000) && geo_pot_height < 32000) {
		constants_["TempLower"] = kTempLower["Fourth Range"];
		constants_["BetaGradient"] = kBetaGradient["Fourth Range"];
		constants_["GeoPotLower"] = kGeoPotLower["Fourth Range"];
		constants_["PressureLower"] = kPressureLower["Fourth Range"];
	}
	if (CompareDouble(geo_pot_height, 32000) && geo_pot_height < 47000) {
		constants_["TempLower"] = kTempLower["Fifth Range"];
		constants_["BetaGradient"] = kBetaGradient["Fifth Range"];
		constants_["GeoPotLower"] = kGeoPotLower["Fifth Range"];
		constants_["PressureLower"] = kPressureLower["Fifth Range"];
	}
	if (CompareDouble(geo_pot_height, 47000) && geo_pot_height < 51000) {
		constants_["TempLower"] = kTempLower["Sixth Range"];
		constants_["BetaGradient"] = kBetaGradient["Sixth Range"];
		constants_["GeoPotLower"] = kGeoPotLower["Sixth Range"];
		constants_["PressureLower"] = kPressureLower["Sixth Range"];
	}
	if (CompareDouble(geo_pot_height, 51000) && geo_pot_height < 71000) {
		constants_["TempLower"] = kTempLower["Seventh Range"];
		constants_["BetaGradient"] = kBetaGradient["Seventh Range"];
		constants_["GeoPotLower"] = kGeoPotLower["Seventh Range"];
		constants_["PressureLower"] = kPressureLower["Seventh Range"];
	}
	if (CompareDouble(geo_pot_height, 71000) && geo_pot_height <= kMaxHeight) {
		constants_["TempLower"] = kTempLower["Eighth Range"];
		constants_["BetaGradient"] = kBetaGradient["Eighth Range"];
		constants_["GeoPotLower"] = kGeoPotLower["Eighth Range"];
		constants_["PressureLower"] = kPressureLower["Eighth Range"];
	}
	return true;
}

bool SM3::AtmModel::FillDataMap() {
	data_["GeoPotHeight"] = CalcPotHeight();
	DefineConstants();
	data_["AccGrav"] = CalcAccGrav();
	data_["Temperature"] = CalcTemp();
	data_["Pressure"] = CalcPressure();
	data_["Density"] = CalcDensity();
	data_["SoundSpeed"] = CalcSoundSp();
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

bool SM3::AtmModelOutput::PrintPressure(std::ostream& os) {
	os << "Давление: " <<
	std::setprecision(kDoublePrecisPres) <<
	data_["Pressure"] << std::endl;
	return true;
}

bool SM3::AtmModelOutput::PrintDensity(std::ostream& os) {
	os << "Плотность: " <<
	std::setprecision(kDoublePrecis) <<
	data_["Density"] << std::endl;
	return true;
}

bool SM3::AtmModelOutput::PrintSoundSp(std::ostream& os) {
	os << "Скорость звука: " <<
	std::setprecision(kDoublePrecis) <<
	data_["SoundSpeed"] << std::endl;
	return true;
}

std::ostream& operator<<(std::ostream& os, SM3::AtmModelOutput& atm_model) {
	atm_model.PrintHeight(os);
	atm_model.PrintPotHeight(os);
	atm_model.PrintAccGrav(os);
	atm_model.PrintTemp(os);
	atm_model.PrintPressure(os);
	atm_model.PrintDensity(os);
	atm_model.PrintSoundSp(os);
	return os;
}

SM3::AtmModelOutput::AtmModelOutput(int height): AtmModel(height) {}
