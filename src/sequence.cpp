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
#include "sequence.tpp"
#include <iostream>

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

Nucleotide const & Sequence::operator[](size_t const i) const{
    return seq[i];
}

Nucleotide & Sequence::operator[](size_t const i) {
    return seq[i];
}

Sequence::iterator Sequence::begin(){
    return seq.begin();
}
Sequence::const_iterator Sequence::begin() const{
    return seq.begin();
}
Sequence::const_iterator Sequence::cbegin() const{
    return seq.cbegin();
}

Sequence::iterator Sequence::end(){
    return seq.end();
}
Sequence::const_iterator Sequence::end() const{
    return seq.end();
}
Sequence::const_iterator Sequence::cend() const{
    return seq.cend();
}

Sequence & Sequence::absorb_join(Sequence const & other){
    if(other.size() != size()) { //sanity: should not happen.
        std::cerr << "WARNING: Sequence join size mismatch." << std::endl;
        seq.resize(other.size()); //let's at least not segfault.
    }
    for(size_t i = 0; i < other.size(); ++i) {
        seq[i] |= other[i];
    }
    return *this;
}

size_t Sequence::size() const {
return seq.size();
}

/*
using vSIt = std::vector<Sequence>::iterator;
template<> Sequence fold_join<vSIt>(vSIt,vSIt);
*/

bool operator==(Sequence const & lhs,Sequence const & rhs){
    return lhs.getseq() == rhs.getseq();
}
bool operator<(Sequence const & lhs,Sequence const & rhs) {
    return lhs.getseq() < rhs.getseq();
}
bool operator<=(Sequence const & lhs,Sequence const & rhs){
    return lhs.getseq() <= rhs.getseq();
}
bool operator>(Sequence const & lhs,Sequence const & rhs){
    return lhs.getseq() > rhs.getseq();
}
bool operator>=(Sequence const & lhs,Sequence const & rhs){
    return lhs.getseq() >= rhs.getseq();
}

} // namespace footprint_analysis
