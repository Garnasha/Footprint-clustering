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

#include "metrics.tpp"

namespace footprint_analysis {

template<>
metrics::hamming::ret_type
distance<metrics::hamming>(Nucleotide const lhs,Nucleotide const rhs) {
    //is high bits of lhs a subset of those rhs or vice versa? Then 0, else 1.
    //subset test: rhs = union(rhs,lhs) OR lhs = union (lhs,rhs)
    return (rhs == (lhs | rhs) || lhs == (lhs | rhs))?0:1;
}

template<>
metrics::seq_hamming::ret_type
distance<metrics::seq_hamming>(Sequence const & lhs, Sequence const & rhs) {
    return std::min(distance<metrics::hamming>(lhs,rhs),
                    distance<metrics::hamming>(lhs.complement(),rhs));
}

template<>
metrics::seq_hamming::ret_type
distance<metrics::seq_hamming>(Nucleotide const lhs, Nucleotide const rhs) {
    return std::min(distance<metrics::hamming>(lhs,rhs),
                    distance<metrics::hamming>(lhs.complement(),rhs));
}

//explicit instantiations
template
metrics::seq_hamming::ret_type
distance<metrics::seq_hamming>(Nucleotide const,Nucleotide const);

template
metrics::seq_hamming::ret_type
distance<metrics::seq_hamming>(Sequence const &,Sequence const &);

template
metrics::seq_hamming::ret_type
distance<metrics::seq_hamming>(Seq_Count const &,Seq_Count const &);

template
metrics::seq_hamming::ret_type
distance<metrics::seq_hamming>(FullFootprint const &,FullFootprint const &);

template
metrics::hamming::ret_type
distance<metrics::hamming>(Nucleotide const,Nucleotide const);

template
metrics::hamming::ret_type
distance<metrics::hamming>(Sequence const &,Sequence const &);

template
metrics::hamming::ret_type
distance<metrics::hamming>(FullFootprint const &,FullFootprint const &);

template
metrics::hamming::ret_type
distance<metrics::hamming>(Seq_Count const & lhs,Seq_Count const & rhs);
} // namespace footprint_analysis
