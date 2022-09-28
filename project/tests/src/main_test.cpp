#include <iostream>
#include <string>


#include "atmmodel.hpp"

int main() {
	SM3::AtmModelOutput atmmodel(-100);
	std::cout << atmmodel << std::endl;
	atmmodel(3000);
	std::cout << atmmodel << std::endl;
	atmmodel(17046);
	std::cout << atmmodel << std::endl;
	atmmodel(26107);
	std::cout << atmmodel << std::endl;
	atmmodel(36000);
	std::cout << atmmodel << std::endl;
	atmmodel(48365);
	std::cout << atmmodel << std::endl;
	atmmodel(55000);
	std::cout << atmmodel << std::endl;
	atmmodel(79000);
	std::cout << atmmodel << std::endl;
	atmmodel(84000);
	std::cout << atmmodel << std::endl;
}