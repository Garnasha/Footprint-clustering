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

#ifndef MINSPANTREE_TPP
#define MINSPANTREE_TPP

#include "minspantree.h"



namespace footprint_analysis {
namespace mst {

template <typename T, typename Distfunc>
size_t prim_update_memos (std::vector<T> const & nodes, Distfunc const & d,
                        std::vector<bool> const & connected, size_t const added,
                        std::vector<link> & memo) {
    size_t candidate = 0;
    for (size_t i = 0; i < nodes.size(); ++i) {
        decltype(link::weight) w = d(nodes[added],nodes[i]);
        if (w < memo[i].weight) {
            memo[i] = link{added,i,d(added,i)};
        }
        if (!connected[i] && // i is a valid candidate AND
                (connected[candidate] || // the current candidate isn't, OR:
                 memo[i].weight < memo[candidate].weight)) // i is better
        {
            candidate = i;
        }
    }
}

template <typename T, typename Distfunc>
std::vector<link> prim_gen_mst(std::vector<T> const & nodes, Distfunc const & d){
    std::vector<link> memo{nodes.size(),link{0,0,link::unreachable}};
    std::vector<bool> connected(nodes.size(),false);
    size_t connected_count = 0;
    size_t candidate = 0;

    std::vector<link> ret_store;
    ret_store.reserve(nodes.size()-1);

    do {
        if (!(connected_count == 0)) {
            ret_store.push_back(memo[candidate]);
        }
        connected[candidate] = true;
        ++connected_count;
        candidate = prim_update_memos(nodes, d, connected, candidate, memo);
    } while (connected_count < nodes.size());
}

} // namespace mst
} // namespace footprint_analysis
#endif // MINSPANTREE_TPP
