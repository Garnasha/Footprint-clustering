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

#include "tests.h"

std::vector<Adj_List> to_adj_lists(std::vector<footprint_analysis::mst::link> links){
    size_t topNode=0;
    for(auto e : links){
        topNode = std::max(e.to,topNode);
        topNode = std::max(e.from,topNode);
    }
    std::vector<Adj_List> adj_ls(topNode+1);
    for(auto e : links) {
        adj_ls[e.to].push_back(e.from);
        adj_ls[e.from].push_back(e.to);
    }
    return adj_ls;
}

bool is_subtree(std::vector<Adj_List> const & adj_ls,
                std::vector<bool> & seen,
                size_t const node,size_t const parent){
    if(seen[node]){
        return false;
    }
    seen[node]=true;
    for(auto e : adj_ls[node]){
        if (e!=parent){
            if(!is_subtree(adj_ls,seen,e,node)){
                return false;
            }
        }
    }
    return true;
}

size_t tree_size(std::vector<footprint_analysis::mst::link> const & links,
               size_t start = 0) {
    auto adj_ls{to_adj_lists(links)};
    std::vector<bool> seen(adj_ls.size(),false);
    seen[start]=true;
    for(auto e : adj_ls[start]){
        if(!is_subtree(adj_ls,seen,e,start)){
            return 0;
        }
    }
    size_t count=0;
    for(auto e : seen) {
        if(e) ++count;
    }
    return count;
}
