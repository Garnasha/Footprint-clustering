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

#ifndef METRICS_P_H
#define METRICS_P_H

#include "nucleotide.h"
#include "sequence.h"
#include "fullfootprint.h"
#include "seq_count.h"

namespace footprint_analysis {
namespace metrics{
struct hamming {using ret_type = unsigned int;};
struct seq_hamming {using ret_type = hamming::ret_type;};
} // namespace metrics

template <typename Metric>
typename Metric::ret_type
distance(Nucleotide const lhs, Nucleotide const rhs);

template <typename Metric>
typename Metric::ret_type
distance(Sequence const & lhs, Sequence const & rhs);

template <typename Metric>
typename Metric::ret_type
distance(FullFootprint const & lhs, FullFootprint const & rhs);

template<typename Metric>
typename Metric::ret_type
distance(Seq_Count const & lhs,Seq_Count const & rhs);

//int hamming_d(Nucleotide const lhs,Nucleotide const rhs);
//int hamming_d(Sequence const & lhs,Sequence const & rhs);
//int hamming_d(FullFootprint const & lhs,FullFootprint const & rhs);

} // namespace footprint_analysis
#endif // METRICS_H
