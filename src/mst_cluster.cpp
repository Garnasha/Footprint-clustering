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


#include "mst_cluster.h"
#include <stack>
#include <iostream>

namespace footprint_analysis {
namespace mst {

std::vector<Safe_Cluster>
collect_index_clusters(std::vector<link> const & edges) {
    std::vector<std::vector<size_t>> adj_list(build_index_adj_list(edges));
    size_t const vec_count(adj_list.size());
    std::vector<bool> taken(vec_count);
    std::vector<Safe_Cluster> ret_store;
    ret_store.reserve(vec_count);
    for(size_t i = 0; i < vec_count; ++i) {
        if (!taken[i]) {
            ret_store.push_back(collect_index_cluster(i,taken,adj_list));
        }
    }
    return ret_store;
}

Safe_Cluster
collect_index_cluster(size_t const root,
                      std::vector<bool> & taken,
                      std::vector<std::vector<size_t>> const & adj_list) {
    Safe_Cluster ret_store;
    std::stack<size_t,std::vector<size_t>> to_visit;
    to_visit.push(root);
    taken[root] = true;
    while(!to_visit.empty()) {
        size_t const current = to_visit.top(); to_visit.pop();
        ret_store.push_back(current);
        for(size_t neighbour : adj_list[current]) {
            if(!taken[neighbour]) {
                taken[neighbour] = true;
                to_visit.push(neighbour);
            }
        }
    }
    return ret_store;
}

size_t static max_index_from_edges(std::vector<link> const & edge_list) {
    std::cout << "INFO (max_index_from_edges): Called" << std::endl;
    size_t max = 0;
    for(auto e : edge_list) {
        max = std::max(e.to,max);
        max = std::max(e.from,max);
    }
    std::cout << "INFO (max_index_from_edges): Complete, result " <<
                 max << std::endl;
    return max;
}

std::vector<std::vector<size_t>>
build_index_adj_list (std::vector<link> const & edge_list) {
    std::cout << "INFO (build_index_adj_list): Called" << std::endl;
    std::vector<std::vector<size_t>> adj_list(max_index_from_edges(edge_list)+1);
    for(auto e : edge_list) {
        adj_list[e.to].push_back(e.from);
        adj_list[e.from].push_back(e.to);
    }
    std::cout << "INFO (build_index_adj_list): Complete, result size " <<
                 adj_list.size() << std::endl;
    return adj_list;
}

} // namespace mst

} // namespace footprint_analysis
