#include <iostream>
#include <string>


#include "atmmodel.hpp"

int main() {
	SM3::AtmModelOutput atmmodel(-100);
	std::cout << atmmodel << std::endl;
	atmmodel(3500);
	std::cout << atmmodel << std::endl;
	atmmodel(17000);
	std::cout << atmmodel << std::endl;
	atmmodel(26000);
	std::cout << atmmodel << std::endl;
	atmmodel(36000);
	std::cout << atmmodel << std::endl;
	atmmodel(49000);
	std::cout << atmmodel << std::endl;
	atmmodel(55480);
	std::cout << atmmodel << std::endl;
	atmmodel(79000);
	std::cout << atmmodel << std::endl;
	atmmodel(84000);
	std::cout << atmmodel << std::endl;
}