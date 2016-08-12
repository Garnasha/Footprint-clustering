#include "libfasta.h"
#include <iostream>
#include <algorithm>
#include <tuple>
#include <cassert>
#include "mst_core.h"

using namespace footprint_analysis;

struct ffp_comp{
    bool operator ()(FullFootprint const & lhs, FullFootprint const & rhs) {
        return lhs.seq.size() < rhs.seq.size() || (
                lhs.seq.size() == rhs.seq.size() &&
                std::tie(lhs.chrN,lhs.loc) < std::tie(rhs.chrN,rhs.loc));
    }
};

int main(void){
    auto fps = load_full_footprints(datapath+monocytes);
    std::cout << fps.size() << std::endl;
    auto motifs = find_mst_motifs(std::move(fps));
    std::cout << motifs.size() << std::endl;
    for (auto m : motifs) std::cout << to_string(m.seq.getseq()) << " " << m.count << std::endl;
    /*
    for (auto fp : fps) std::cout << std::string(fp) << std::endl;
    std::cout << " That's all, now to sort them" << std::endl;
    std::sort(fps.begin(),fps.end(),ffp_comp{});
//  size_t i = 0;
    for (auto fp : fps) std::cout << std::string(fp) << std::endl;
    //for (size_t j = 0; j < 1000; ++j){
     //   std::cout << std::string(fps[j]) << " size " << fps[j].seq.size() << std::endl;
    //}
    */
#if 0
    while(true){
        std::cout << "Enter an index to print" << std::endl;
        std::cin >> i;
/*        std::cout << fps[i].chrN << " " 
            << std::string(fps[i].seq.begin(),fps[i].seq.end()) << " "
            << "(" << fps[i].loc.first << "," << fps[i].loc.second << ")" 
            << std::endl;*/
        std::cout << std::string(fps[i]) << std::endl;
    }
#endif
}
