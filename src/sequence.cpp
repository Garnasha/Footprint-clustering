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
//OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
//THE SOFTWARE.

#include "sequence.h"

namespace footprint_analysis{

template <typename T>
std::vector<T> index_slice(std::vector<T> const & v,size_t begin, size_t end) {
    return std::vector<T>{
        v.begin()+static_cast<std::ptrdiff_t>(begin),
        v.begin()+static_cast<std::ptrdiff_t>(end)};
}

Sequence::Sequence():
    seq()
{}

Sequence::Sequence(std::vector<Nucleotide> seq):
    seq(std::move(seq))
{}

Sequence::Sequence(std::vector<Nucleotide> const & chrseq, Location loc):
    seq(index_slice(chrseq,loc.first,loc.second))
{}

Sequence::
Sequence(std::vector<Nucleotide> const & chrseq, size_t begin, size_t end):
    seq(index_slice(chrseq,begin,end))
{}


std::vector<Nucleotide> const & Sequence::getseq() const {
    return seq;
}

Sequence::operator std::vector<Nucleotide> () const {
    return seq;
}

size_t Sequence::size() const {
    return seq.size();
}
} // namespace footprint_analysis
