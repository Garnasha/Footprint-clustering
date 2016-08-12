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

#include "nucleotide.h"


namespace footprint_analysis {
constexpr char Nucleotide::bits_to_letter[];

unsigned char  Nucleotide::letter_to_bits(char const c) {
    switch (c){
        case 'a':
        case 'A':
            return 0x01;
        case 'c':
        case 'C':
            return 0x02;
        case 't':
        case 'T':
            return 0x04;
        case 'g':
        case 'G':
            return 0x08;
        case 'n':
        case 'N':
            return 0x0f;
        default:
            return 0;
    }
}

Nucleotide::Nucleotide(unsigned char const bits,from_bits_tag):
    base_bits(bits)
{}

Nucleotide::Nucleotide():
    base_bits(0)
{}

Nucleotide::Nucleotide(char const c):
    base_bits(letter_to_bits(c))
{}


Nucleotide::operator char () const {
    return bits_to_letter[base_bits];
}

Nucleotide Nucleotide::complement() const
{
   return Nucleotide{
       static_cast<unsigned char>((base_bits&0x03) << 2 | (base_bits&0x0c) >> 2),
       from_bits_tag{}
   };
}

Nucleotide operator|(Nucleotide const lhs, Nucleotide const rhs) {
    return Nucleotide{
        static_cast<unsigned char>(lhs.base_bits | rhs.base_bits),
        Nucleotide::from_bits_tag{} };
}

Nucleotide & Nucleotide::operator|=(Nucleotide const & other){
    base_bits |= other.base_bits;
    return *this;
}

bool operator==(Nucleotide const lhs, Nucleotide const rhs) {
    return lhs.base_bits == rhs.base_bits;
}

bool operator!=(Nucleotide const lhs, Nucleotide const rhs) {
    return lhs.base_bits != rhs.base_bits;
}

bool operator<(Nucleotide const lhs,Nucleotide const rhs) {
    return lhs.base_bits < rhs.base_bits;
}

bool operator<=(Nucleotide const lhs,Nucleotide const rhs) {
    return lhs.base_bits <= rhs.base_bits;
}

bool operator>(Nucleotide const lhs,Nucleotide const rhs) {
    return lhs.base_bits > rhs.base_bits;
}

bool operator>=(Nucleotide const lhs,Nucleotide const rhs) {
    return lhs.base_bits >= rhs.base_bits;
}

/// Overload of std::to_string for argument std::vector<Nucleotide>
std::string to_string(std::vector<Nucleotide> const & seq){
    return std::string(seq.begin(),seq.end());
}

} // namespace footprint_analysis
