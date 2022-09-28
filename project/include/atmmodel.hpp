#ifndef PROJECT_INCLUDE_ATMMODEL_HPP_
#define PROJECT_INCLUDE_ATMMODEL_HPP_

#include <iostream>
#include <istream>
#include <iostream>
#include <map>
#include <string>

static const int kRadEarth =  6356767;
static const double kStandAccGrav = 9.80665;
static const int kMinHeight = (-2000);
static const int kMaxHeight = 80000;
static const int kErrHeight = (-5000);
static const double kComparePrecis = 1e13;
static const int kDoublePrecis = 5;

namespace SM3 {
class AtmModel {
 protected:
      int height_;
      std::map <std::string, double> data_;

			double CalcPotHeight() const;
      double CalcAccGrav() const;
      double CalcTemp() const;
    //   double CalcPressure(int height);
    //   double CalcDensity(int height);
    //   double CalcSoundSp(int height);

      bool FillDataMap();
 public:
      explicit AtmModel(int height);
      bool operator() (int height);
};

class AtmModelOutput: public AtmModel {
 public:
	explicit AtmModelOutput(int height);
	// friend std::ostream& operator<<(std::ostream& os, AtmModelOutput& atm_model);

	bool PrintHeight(std::ostream& os);
	bool PrintPotHeight(std::ostream& os);
	bool PrintAccGrav(std::ostream& os);
	bool PrintTemp(std::ostream& os);
	// bool PrintPressure(int height) const;
	// bool PrintDensity(int height) const;
	// bool PrintSoundSp(int height) const;
};

bool CompareDouble(const double first, const double second, const double precis = kComparePrecis);
}		// namespace SM3

std::ostream& operator<<(std::ostream& os, SM3::AtmModelOutput& atm_model);

#endif  //  PROJECT_INCLUDE_ATMMODEL_HPP_
