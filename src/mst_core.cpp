//The MIT License (MIT)
//
//Copyright (c) 2016 Sal Wolffs
//
//Permission is hereby granted, free of charge, to any person obtaining a copy
//of this software and associated documentation files (the "Software"), to deal
//in the Software without restriction, including without limitation the rights
//to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//copies of the Software, and to permit persons to whom the Software is
//furnished to do so, subject to the following conditions:
//
//The above copyright notice and this permission notice shall be included in
//all copies or substantial portions of the Software.
//
//THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//SOFTWARE.

#include "mst_core.h"
#include "mst_core.tpp"
#include <algorithm>
#include <utility>

namespace footprint_analysis {

Seq_Count::Seq_Count():
    seq(),count(0)
{}

Seq_Count::Seq_Count(Sequence _seq,size_t _count):
    seq(_seq),count(_count)
{}

Seq_Count & Seq_Count::absorb_join(Seq_Count const & other) {
    seq.absorb_join(other.seq);
    count += other.count;
    return *this;
}

std::vector<Seq_Count> count_sequences(std::vector<FullFootprint> && raws) {
    std::sort(raws.begin(),
              raws.end(),
              [](FullFootprint const & lhs, FullFootprint const & rhs){
        return lhs.seq < rhs.seq;
    });
    std::vector<Seq_Count> store;
    Seq_Count buffer{raws[0].seq,0};
    for (auto fp : raws) {
        if(fp.seq == buffer.seq) {
            ++buffer.count;
        } else {
            store.push_back(std::move(buffer));
            buffer = Seq_Count{fp.seq,1};
        }
    }
    store.push_back(std::move(buffer));
    return store;
}

template <typename Metric>
typename Metric::ret_type
distance(Seq_Count const & lhs,Seq_Count const & rhs){
    return distance<Metric>(lhs.seq,rhs.seq);
}
template
typename metrics::hamming::ret_type
distance<metrics::hamming>(Seq_Count const &,Seq_Count const &);

std::vector<Seq_Count> find_mst_motifs(std::vector<FullFootprint> && raws) {
    auto seq_counts{count_sequences(std::move(raws))};
    auto distfunc = [](Seq_Count const & lhs,Seq_Count const & rhs) {
        return distance<metrics::hamming>(lhs,rhs);
    };
    auto tree = mst::prim_gen_mst(seq_counts,distfunc);
    auto order_by_weight = [](mst::link const & lhs,mst::link const & rhs) {
        return lhs.weight < rhs.weight;
    };
    mst::remove_greatest_n(tree,600,order_by_weight);
    auto clusters = mst::collect_clusters<size_t,mst::link>(tree);
    std::vector<Seq_Count> motifs;
    for (auto cluster_indices : clusters) {
        std::vector<Seq_Count> cluster;
        cluster.reserve(cluster_indices.size());
        for(auto i : cluster_indices) cluster.push_back(seq_counts[i]);
        motifs.push_back(fold_join<Seq_Count>(cluster.begin(),cluster.end()));
    }
    return motifs;
}
} // namespace footprint_analysis
