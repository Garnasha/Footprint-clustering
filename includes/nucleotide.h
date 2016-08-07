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

#ifndef NUCLEOTIDE_H
#define NUCLEOTIDE_H
#include <string>
#include <vector>
namespace footprint_analysis {
struct Nucleotide{
private:
    using Nuc = Nucleotide;
    class from_bits_tag {};

    unsigned char base_bits;

    constexpr Nucleotide(unsigned char const bits,from_bits_tag);

    constexpr static char bits_to_letter[16] {
        /*       C   C
             A       A*/
        '-','A','C','M',//
        'T','W','Y','H',// T
        'G','R','S','V',//   G
        'K','D','B','N' // T G
    };
    static constexpr unsigned char letter_to_bits(char const);



public:
    constexpr Nucleotide(char c);

    constexpr operator char () const;
    constexpr Nucleotide  complement() const;

    friend constexpr Nuc operator| (Nuc const lhs,Nuc const rhs);
};

std::string to_string(std::vector<Nucleotide> const & seq);

} // namespace footprint analysis

#endif // NUCLEOTIDE_H
