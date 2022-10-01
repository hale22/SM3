#ifndef PROJECT_INCLUDE_ATMMODEL_HPP_
#define PROJECT_INCLUDE_ATMMODEL_HPP_

#include <array>
#include <iostream>
#include <istream>
#include <iostream>
#include <map>
#include <string>

static const int kRadEarth =  6356767;
static const double kStandAccGrav = 9.80665;
static const double kUnitGas = 287.05287;
static const double kUniversalGas = 8314.32;
static const double kMolarMass = 28.96442;
static const double kSoundSpeed = 20.046796;

static const int kMinHeight = (-2000);
static const int kMaxHeight = 80000;
static const int kErrHeight = (-5000);
static const double kComparePrecis = 1e13;
static const int kDoublePrecis = 5;
static const int kDoublePrecisPres = 6;

static std::map<std::string, double> kGeoPotLower =
{{"First Range", -2000}, {"Second Range", 0}, {"Third Range", 11000},
{"Fourth Range", 20000}, {"Fifth Range", 32000}, {"Sixth Range", 47000},
{"Seventh Range", 51000}, {"Eighth Range", 71000}};

static std::map<std::string, double> kBetaGradient =
{{"First Range", -0.0065}, {"Second Range", -0.0065}, {"Third Range", 0},
{"Fourth Range", 0.001}, {"Fifth Range", 0.0028}, {"Sixth Range", 0},
{"Seventh Range", -0.0028}, {"Eighth Range", -0.0020}};

static std::map<std::string, double> kTempLower =
{{"First Range", 301.15}, {"Second Range", 288.15}, {"Third Range", 216.65},
{"Fourth Range", 216.65}, {"Fifth Range", 228.65}, {"Sixth Range", 270.65},
{"Seventh Range", 270.65}, {"Eighth Range", 214.65}};

static std::map<std::string, double> kPressureLower =
{{"First Range", 127774}, {"Second Range", 101325}, {"Third Range", 22632},
{"Fourth Range", 5474.87}, {"Fifth Range", 868.014}, {"Sixth Range", 110.906},
{"Seventh Range", 66.9384}, {"Eighth Range", 3.95639}};





namespace SM3 {
class AtmModel {
 protected:
	int height_;
	std::map <std::string, double> data_;
	std::map <std::string, double> constants_;
	double CalcPotHeight() const;
	double CalcAccGrav() const;
	double CalcTemp();
	double CalcPressure();
	double CalcDensity();
	double CalcSoundSp();

	bool DefineConstants();
  bool FillDataMap();
 public:
      explicit AtmModel(int height);
      bool operator() (int height);
};

class AtmModelOutput: public AtmModel {
 public:
	explicit AtmModelOutput(int height);
	// friend std::ostream& operator<<(std::ostream& os, AtmModelOutput& atm_model);

	bool PrintHeight(std::ostream& os) const;
	bool PrintPotHeight(std::ostream& os);
	bool PrintAccGrav(std::ostream& os);
	bool PrintTemp(std::ostream& os);
	bool PrintPressure(std::ostream& os);
	bool PrintDensity(std::ostream& os);
	bool PrintSoundSp(std::ostream& os);
};

bool CompareDouble(const double first, const double second, const double precis = kComparePrecis);
}		// namespace SM3

std::ostream& operator<<(std::ostream& os, SM3::AtmModelOutput& atm_model);

#endif  //  PROJECT_INCLUDE_ATMMODEL_HPP_
