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

#ifndef FULLFOOTPRINT_H
#define FULLFOOTPRINT_H

#include "dnatypes.h"
#include <tuple>
#include <string>

namespace footprint_analysis {

typedef std::pair<size_t,size_t> Slice;
typedef Slice Location;

/// A footprint sequence and full location.
class FullFootprint{
public:
    /// Which chromosome the footprint is located on.
    std::string chrN;
    std::vector<Nucleotide> seq;
    Location loc;

    FullFootprint(Chromosome const & chr,size_t start,size_t end);
    explicit operator std::string () const;
};

} // namespace footprint_analysis

#endif // FULLFOOTPRINT_H
