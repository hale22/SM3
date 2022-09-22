#pragma once

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


namespace SM3 {
class AtmModel {
  protected:
      int height_;
      std::map <std::string, double> data_;
      
      double CalcPotHeight(int height);
      double CalcAccGrav(int height);
      double CalcTemp(int height);
      double CalcPressure(int height);
      double CalcDensity(int height);
      double CalcSoundSp(int height);
      
      bool FillDataMap(int height);
      bool CalcModel(int height);
   
  public:
      explicit AtmModel(int height); 
      bool operator() (int height);
     
      //  todo: список инициализации
};

class AtmModelOutput: public AtmModel {
 private:
 	bool PrintPotHeight(int height) const;
 	bool PrintAccGrav(int height) const;
 	bool PrintTemp(int height) const;
 	bool PrintPressure(int height) const;
 	bool PrintDensity(int height) const;
 	bool PrintSoundSp(int height) const;
	bool PrintAll(int height) const;
 public:
	friend
	std::ostream& operator<<(std::ostream& os, const AtmModelOutput& atm_model);
};
} // namespace SM3

std::ostream& operator<<(std::ostream& os, const SM3::AtmModelOutput& atm_model);