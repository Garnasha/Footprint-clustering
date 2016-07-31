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

#ifndef MST_CLUSTER_TPP
#define MST_CLUSTER_TPP

#include "mst_cluster.h"
#include <algorithm>
#include <type_traits>
#include <unordered_map>

namespace footprint_analysis {
namespace mst {

template <typename T, typename Ord>
void remove_greatest_n(std::vector<T> & v, size_t n, Ord ordering) {
    std::sort(v.begin(),v.end(),ordering);
    v.resize(v.size()-n);
} //done

template <typename Vertex, typename Edge>
std::unordered_map<Vertex,std::vector<Edge>>
build_adj_list(std::vector<Edge> const & edges) {

}

template <typename Vertex, typename Edge>
std::vector<Cluster<Vertex>>
collect_clusters(std::vector<Edge> const & edges) {
    static_assert(std::is_same<Vertex,decltype(Edge::to)>(),
                  "Edge::to is not a Vertex!");
    std::unordered_map<Vertex,std::vector<Edge>> adj_list{build_adj_list(edges)};
    std::unordered_set<Vertex> collected;
    for (auto v : adj_list) {
        if (collected.count(v.left) != 0){
            continue;
        }

    }
}

template <typename Edge>
std::vector<Cluster<size_t>> collect_clusters(std::vector<Edge> const & v) {
    static_assert(std::is_same<size_t,decltype(Edge::to)>(),
                  "Edge::to is not a size_t!");


}
} // namespace mst
} // namespace footprint_analysis
#endif // MST_CLUSTER_TPP
