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

#include "fullfootprint.h"

namespace footprint_analysis {
/// Simple constructor, looks up and stores sequence and metadata.
FullFootprint::FullFootprint(
        Chromosome const & chr,
        size_t begin,
        size_t end):
    chrN(chr.name),
    seq(chr.seq,begin,end),
    loc(begin,end)
{}

/// \brief Pretty-printing string cast.
/// \return A single-line pretty-printing representation.
//
FullFootprint::operator std::string () const {
    return chrN + " "                                                   //chrN
            + to_string(seq.getseq())                                   //seq
            + " (" + std::to_string(loc.first) +", "
            + std::to_string(loc.second) + ")";                         //loc
}
} // namespace footprint analysis
