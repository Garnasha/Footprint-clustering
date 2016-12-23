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

template <typename T>
void highpass_count(T& counts,size_t const cutoff) {
    std::sort(counts.begin(),counts.end(),
              [](typename T::value_type const & lhs,
                 typename T::value_type const & rhs) {
        return lhs.count > rhs.count;
    });
    for (size_t i = 0; i < counts.size();++i){
        if (counts[i].count < cutoff) {
            counts.resize(i);
            return;
        }
    }

}

template <typename T>
void lowpass_weight(T& links,unsigned int cutoff){
    for (size_t i = 0; i < links.size();++i){
        if (links[i].weight > cutoff) {
            links.resize(i);
            return;
        }
    }
}

int main(void){
    auto fps = load_full_footprints(datapath+monocytes);
    std::cout << fps.size() << std::endl;
    auto seq_counts{count_sequences(std::move(fps))};
    std::cout << "INFO: seq_count count: " << seq_counts.size() << std::endl;
    std::cout << "Please enter a highpass cutoff for sequence counts: \n";
    size_t hp_cutoff=0;
    std::cin >> hp_cutoff;
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    std::cin.clear();
    std::cout << "INFO: high-passing seq_counts with cutoff " << hp_cutoff << std::endl;
    highpass_count(seq_counts,hp_cutoff);
    std::cout << "INFO: high-passed seq_count counts, remaining: " << seq_counts.size() << std::endl;
    auto distfunc = [](Seq_Count const & lhs,Seq_Count const & rhs) {
        return distance<metrics::seq_hamming>(lhs,rhs);
    };
    std::cout << "INFO: defined distfunc." << std::endl;
    auto tree = mst::prim_gen_mst(seq_counts,distfunc);
    std::cout << "INFO: built tree, testing..." << std::endl;
    auto testcluster = collect_index_clusters(tree);
    std::cout << "testcluster has " << testcluster.size() << " element(s)" <<
                 std::endl << "first has size " << testcluster[0].size() <<
                 std:: endl;
    std::sort(tree.begin(),tree.end());
    std::cout << "INFO: SORTED" << std::endl;
    auto sortcluster = collect_index_clusters(tree);
    std::cout << "sortcluster has " << sortcluster.size() << " element(s)" <<
                 std::endl << "first has size " << sortcluster[0].size() <<
                 std::endl;
    lowpass_weight(tree,1);
    //tree.resize(tree.size()-600);
    std::cout << "Shrunk tree by 600, new size " << tree.size() << std::endl;
    auto clusters = collect_index_clusters(tree);
    std::cout << "clusters has " << clusters.size() << " element(s)" <<
                 std::endl << "first has size " << clusters[0].size() <<
                 std::endl;
    auto motifs = cjoinsFromIndexClusters(clusters,seq_counts);
    std::cout << "motifs has " << motifs.size() << " element(s)" <<
                 std::endl << "first is " << to_string(motifs[0].seq) <<
                 " seen " << motifs[0].count << " times " <<
                 std::endl;
    std::cout << "Sorting by length..." << std::endl;
    std::sort(motifs.begin(),motifs.end(),
              [](Seq_Count const & lhs, Seq_Count const & rhs){
                    return lhs.count > rhs.count ||
                            (lhs.count == rhs.count &&
                             lhs.seq.size() < rhs.seq.size());});
    std::cout << "Press any key to continue." << std::endl;
    std::cin.get();
    for (auto m : motifs) {
        std::cout << to_string(m.seq) << " " << m.count << " " << m.joincount << "\n";
    }
    //auto motifs = joinsFromIndexClusters(clusters,fps);


    //std::cout << "Tree rooted at 0 has size " << tree_size(tree,0)<<std::endl;
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
