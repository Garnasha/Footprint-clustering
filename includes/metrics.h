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

#ifndef METRICS_H
#define METRICS_H
#include "metrics_p.h"
namespace footprint_analysis {

extern template
metrics::hamming::ret_type
distance<metrics::hamming>(Nucleotide const lhs,Nucleotide const rhs);

extern template
metrics::seq_hamming::ret_type
distance<metrics::seq_hamming>(Nucleotide const lhs, Nucleotide const rhs);

//explicit instantiations
extern template
metrics::hamming::ret_type
distance<metrics::hamming>(Nucleotide const,Nucleotide const);

extern template
metrics::hamming::ret_type
distance<metrics::hamming>(Sequence const &,Sequence const &);

extern template
metrics::hamming::ret_type
distance<metrics::hamming>(FullFootprint const &,FullFootprint const &);

extern template
metrics::hamming::ret_type
distance<metrics::hamming>(Seq_Count const & lhs,Seq_Count const & rhs);

extern template
metrics::seq_hamming::ret_type
distance<metrics::seq_hamming>(Nucleotide const,Nucleotide const);

extern template
metrics::seq_hamming::ret_type
distance<metrics::seq_hamming>(Sequence const &,Sequence const &);

extern template
metrics::seq_hamming::ret_type
distance<metrics::seq_hamming>(Seq_Count const &,Seq_Count const &);

extern template
metrics::seq_hamming::ret_type
distance<metrics::seq_hamming>(FullFootprint const &,FullFootprint const &);

} //namespace footprint_analysis
#endif // METRICS_H
