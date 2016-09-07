#include "libfasta.h"
#include <iostream>
#include <algorithm>
#include <tuple>
#include <cassert>
#include "mst_core.h"
#include "tests.h"
#include "minspantree.tpp"

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


    auto seq_counts{count_sequences(std::move(fps))};
    std::cout << "INFO: seq_count count: " << seq_counts.size() << std::endl;
    auto distfunc = [](Seq_Count const & lhs,Seq_Count const & rhs) {
        return distance<metrics::hamming>(lhs,rhs);
    };
    std::cout << "INFO: defined distfunc." << std::endl;
    auto tree = mst::prim_gen_mst(seq_counts,distfunc);
    std::cout << "INFO: built tree, testing..." << std::endl;
    std::cout << "Tree rooted at 0 has size " << tree_size(tree,0)<<std::endl;
    //auto motifs = find_mst_motifs(std::move(fps));
    //std::cout << motifs.size() << std::endl;
    //for (auto m : motifs) std::cout << to_string(m.seq.getseq()) << " " << m.count << std::endl;
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
