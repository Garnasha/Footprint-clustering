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

#ifndef MST_CORE_H
#define MST_CORE_H

#include <cstddef>
#include <string>
#include "nucleotide.h"
#include "sequence.h"
#include "fullfootprint.h"
#include "mst_cluster.h"
#include "minspantree.h"
#include "metrics.h"


namespace footprint_analysis {


std::vector<Seq_Count> count_sequences(std::vector<FullFootprint> && raws);


template<typename Metric>
typename Metric::ret_type
distance(Seq_Count const & lhs,Seq_Count const & rhs);

std::vector<Seq_Count> find_mst_motifs(std::vector<FullFootprint> && raws);

std::vector<Seq_Count> cjoinsFromIndexClusters(
    std::vector<std::vector<size_t>> const & clusters,
    std::vector<Seq_Count> const & lookup);
} // namespace footprint_analysis
#endif // SEQ_COUNT_H
