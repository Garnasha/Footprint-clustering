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

#ifndef MINSPANTREE_H
#define MINSPANTREE_H

#include <vector>
#include <cstddef>
#include <limits>

namespace footprint_analysis {
namespace mst {

template <typename Vertex, typename Num>
struct weighted_edge {
    Vertex from;
    Vertex to;
    Num weight;

    static constexpr Num unreachable = std::numeric_limits<Num>::max();
};

using link = weighted_edge<size_t,unsigned int>;


} // ::footprint_analysis::mst::
} // ::footprint_analysis::
#endif // MINSPANTREE_H
