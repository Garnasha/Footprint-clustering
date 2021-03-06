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

template <typename Vertex, typename Weight>
struct weighted_edge {
    Vertex from;
    Vertex to;
    Weight weight;

    static constexpr Weight unreachable = std::numeric_limits<Weight>::max();
    weighted_edge<Vertex,Weight> reversed();
    bool operator< (weighted_edge<Vertex,Weight> const & other) {
        return weight < other.weight;
    }
};

using link = weighted_edge<size_t,unsigned int>;

template <typename T, typename Distfunc>
size_t prim_update_memos (std::vector<T> const & nodes, Distfunc const & d,
                        std::vector<bool> const & connected, size_t const added,
                        std::vector<link> & memo);

template <typename T, typename Distfunc>
std::vector<link> prim_gen_mst(std::vector<T> const & nodes, Distfunc const & d);
} // namespace mst
} // namespace footprint_analysis
#endif // MINSPANTREE_H
