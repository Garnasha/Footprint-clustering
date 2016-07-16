#include "libfasta.h"
#include <iostream>

using namespace footprint_analysis;

int main(void){
    auto fps = read_footprints(datapath+monocytes);
    size_t i = 0;
    while(true){
        std::cout << "Enter an index to print" << std::endl;
        std::cin >> i;
/*        std::cout << fps[i].chrN << " " 
            << std::string(fps[i].seq.begin(),fps[i].seq.end()) << " "
            << "(" << fps[i].loc.first << "," << fps[i].loc.second << ")" 
            << std::endl;*/
        std::cout << std::string(fps[i]) << std::endl;
    }
}
