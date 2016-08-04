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
#include <queue>

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

//Import from C++17
template<class...> struct conjunction : std::true_type { };
template<class B1> struct conjunction<B1> : B1 { };
template<class B1, class... Bn>
struct conjunction<B1, Bn...> :
        std::conditional<B1::value != false, conjunction<Bn...>, B1>::type  {};
//End import
template<typename... Bn>
constexpr bool conjunction_v = conjunction<Bn...>::value;

//Fakes an std::
template <typename Vertex>
class DenseUIntSet {
private:
    using vb = std::vector<bool>;
    vb is_members;
public:
    using size_type = typename vb::size_type;
    using key_type = Vertex;
    void reserve (size_type size){
        return is_members.reserve(size);
    }



};

template <typename T>
using DenseSet =
    std::conditional<
        conjunction_v<std::is_integral<T>,std::is_unsigned<T>>,
        DenseUIntSet<T>,
        std::unordered_set<T>
    >;

template <typename Vertex>
using DenseSet_t = typename DenseSet<Vertex>::type;

template <typename Vertex, typename Edge>
Cluster<Vertex>
collect_cluster(
        Vertex const & seed,
        DenseSet_t<Vertex> & visited,
        std::unordered_map<Vertex,std::vector<Edge>> const & adj_list){
    std::queue<Vertex> to_visit{seed};
    Cluster<Vertex> ret_store;
    while(!to_visit.empty()){
       Vertex v = to_visit.front();
       to_visit.pop();
       if(visited.count(v) != 0){
           continue;
       }
       ret_store.push_back(v);
       for(auto edge : adj_list[v]){
           if(visited.count(edge.to) != 0) {
               continue;
           }
           to_visit.push(edge.to);
       }
       visited.push_back(v);
    }
    return ret_store;
}


template <typename Vertex, typename Edge>
std::vector<Cluster<Vertex>>
collect_clusters(std::vector<Edge> const & edges) {
    static_assert(std::is_same<Vertex,decltype(Edge::to)>(),
                  "Edge::to is not a Vertex!"); //sanity check


    using V = Vertex;
    using E = Edge;

    std::unordered_map<V,std::vector<E>> adj_list{build_adj_list<V,E>(edges)};
    DenseSet_t<Vertex> visited;
    visited.reserve(adj_list.size());
    std::vector<Cluster<V>> ret_store;
    for (auto node : adj_list) {
        V & v = node.left;
        if (visited.count(v) != 0){
            continue;
        }
        ret_store.push_back(collect_cluster<V,E>(v, visited, adj_list));
    }
    return ret_store;
}

template <typename Edge>
std::vector<Cluster<size_t>> collect_clusters(std::vector<Edge> const & v) {
    static_assert(std::is_same<size_t,decltype(Edge::to)>(),
                  "Edge::to is not a size_t!");


}
} // namespace mst
} // namespace footprint_analysis
#endif // MST_CLUSTER_TPP
