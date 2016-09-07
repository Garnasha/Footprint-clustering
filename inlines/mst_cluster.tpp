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
#include "minspantree.tpp"
#include <algorithm>
#include <type_traits>
#include <unordered_map>
#include <queue>
#include <cstddef>
#include <cassert>

namespace footprint_analysis {
namespace mst {

//Import from C++17
template<class...> struct conjunction : std::true_type { };
template<class B1> struct conjunction<B1> : B1 { };
template<class B1, class... Bn>
struct conjunction<B1, Bn...> :
        std::conditional<B1::value != false, conjunction<Bn...>, B1>::type  {};
//End import
template<typename... Bn>
constexpr bool conjunction_v = conjunction<Bn...>::value;

/// \brief Fakes an std::unordered_set<UInt_T>, backed by std::vector<bool>
/// Warning: bare bones, does not support e.g. iteration (iterator is nullptr_t)
template <typename UInt_T>
class DenseUIntSet {
private:
    using vb = std::vector<bool>;
    vb is_members;
public:
    using size_type = typename vb::size_type;
    using key_type = UInt_T;
    using value_type = key_type;
    using iterator = std::nullptr_t;
    using const_iterator = const iterator;
    void reserve (size_type size){
        return is_members.reserve(size);
    }
    size_type count(key_type const k) const {
        if (is_members.size() <= k){
            return 0;
        }
        else {
            return is_members[k]?1:0;
        }
    }

    std::pair<iterator,bool> insert( const value_type value ) {
        if (is_members.size() <= value){
            is_members.resize(value+1);
        }
        if (is_members[value]){
            return {nullptr,false};
        }
        else {
            is_members[value]=true;
            return {nullptr,true};
        }
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

template <typename T, typename Ord>
void remove_greatest_n(std::vector<T> & v, size_t n, Ord ordering) {
    std::sort(v.begin(),v.end(),ordering);
    v.resize(v.size()-n);
} //done

template <typename Vertex, typename Edge>
std::unordered_map<Vertex,std::vector<Edge>>
build_adj_list(std::vector<Edge> const & edges) {
    std::unordered_map<Vertex,std::vector<Edge>> adj_list;
    for (auto e : edges) {
        adj_list[e.to].push_back(e);
        adj_list[e.from].push_back(e.reversed());
    }
    return adj_list;
}


template <typename Vertex, typename Edge>
Cluster<Vertex>
collect_cluster(
        Vertex const & seed,
        DenseSet_t<Vertex> & visited,
        std::unordered_map<Vertex,std::vector<Edge>> const & adj_list)
{
    std::queue<Vertex> to_visit;
    to_visit.push(seed);
    Cluster<Vertex> ret_store;
    assert(visited.count(seed) == 0);

    while(!to_visit.empty()){
       Vertex v = to_visit.front();
       to_visit.pop();
       if(visited.count(v) != 0){
           continue;
       }
       ret_store.push_back(v);
       for(auto edge : adj_list.at(v)){
           assert(edge.from == v);
           if(visited.count(edge.to) != 0) {
               continue;
           }
           to_visit.push(edge.to);
       }
       visited.insert(v);
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

    //TODO: replace this by a DenseMap_t, matching DenseSet_t
    std::unordered_map<V,std::vector<E>> adj_list{build_adj_list<V,E>(edges)};
    DenseSet_t<Vertex> visited;
    visited.reserve(adj_list.size());
    std::vector<Cluster<V>> ret_store;
    for (auto node : adj_list) {
        V const & v = node.first;
        if (visited.count(v) != 0){
            continue;
        }
        ret_store.push_back(collect_cluster<V,E>(v, visited, adj_list));
    }
    return ret_store;
}

} // namespace mst
} // namespace footprint_analysis
#endif // MST_CLUSTER_TPP
