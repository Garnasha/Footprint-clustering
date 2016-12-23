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

#ifndef METRICS_TPP
#define METRICS_TPP

#include "metrics_p.h"

namespace footprint_analysis {

template <typename Metric>
typename Metric::ret_type
distance(Nucleotide const lhs, Nucleotide const rhs);
//no default definition.

template<>
typename metrics::hamming::ret_type
distance<metrics::hamming>(Nucleotide const,Nucleotide const);

template <typename Metric>
typename Metric::ret_type
distance(Sequence const & lhs, Sequence const & rhs) {
    typename Metric::ret_type dist{0};
    if (lhs.size() != rhs.size()) {
        return {100};
    }
    auto syn_iter = rhs.begin();
    for (auto l : lhs) {
        dist += distance<Metric>(l,*(syn_iter++));
    }
    return dist;
}

template <typename Metric>
typename Metric::ret_type
distance(FullFootprint const & lhs, FullFootprint const & rhs) {
    return distance<Metric>(lhs.seq,rhs.seq);
}

template <typename Metric>
typename Metric::ret_type
distance(Seq_Count const & lhs,Seq_Count const & rhs){
    return distance<Metric>(lhs.seq,rhs.seq);
}
} // namespace footprint_analysis
#endif // METRICS_TPP
