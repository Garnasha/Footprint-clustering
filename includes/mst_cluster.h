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

#include <vector>
#include <unordered_set>
#include "minspantree.h"
#ifndef MST_CLUSTER_H
#define MST_CLUSTER_H
namespace footprint_analysis {
namespace mst {
template <typename T>
using Cluster = std::vector<T>;

using Safe_Cluster = std::vector<size_t>;

std::vector<Safe_Cluster>
collect_index_clusters(std::vector<link> const & edges);

Safe_Cluster
collect_index_cluster(size_t const root,
                     std::vector<bool> & taken,
                     std::vector<std::vector<size_t>> const & adj_list);

std::vector<std::vector<size_t>>
build_index_adj_list (std::vector<link> const & edge_list);


} // namespace mst
} // namespace footprint_analysis
#endif // MST_CLUSTER_H
