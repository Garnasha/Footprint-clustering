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

#pragma once
#ifndef LIBFASTA_H
#define LIBFASTA_H

#include <iostream>
#include <fstream>
#include <string>
#include <tuple>
#include <vector>
#include <numeric>
#include <cstdio>
#include <cassert>
#include <algorithm>

namespace ReadFasta{

using std::string;
using std::ifstream;
using std::vector;


const std::string datapath{"/home/sal/scriptie/data/"};
const std::string refpath{datapath+"reffa/"};
const std::string monocytes{"Monocytes_0.05FDR_FOOTPRINTS"};

struct Nucleotide{
    char base;

    Nucleotide(char c):base(c){}
    operator char () const {return base;}
};



struct Chromosome{
    std::string const name;
    std::vector<Nucleotide> const seq;
};


struct BlindFootprint{
    std::string chrN;
    std::pair<size_t,size_t> loc;
};

/// A footprint sequence and location.
class Footprint{
public:
    /// Which chromosme the footprint is located on.
    std::string chrN;
    std::vector<Nucleotide> seq;
    /// \todo Replace this by size_t start,end; and refactor.
    std::pair<size_t,size_t> loc; 

    Footprint(Chromosome const & chr,size_t start,size_t end);
    explicit operator std::string () const;
};

std::string to_string(std::vector<Nucleotide> const & seq);

std::vector<std::string> readlines(string const & fname);
    
Chromosome readfa(std::string const & chrN); 

std::tuple<std::string,size_t,size_t> split_fp(std::string const & entry);
BlindFootprint split_fp(std::string const & entry);

Footprint parsefootprint(Chromosome const & chr,std::string const & entry);

template<typename V,typename T>
V & pushifnew(V & v, T && e);

std::vector<Footprint> read_footprints(std::string const fpfilename);


}//namespace ReadFasta
#endif //LIBFASTA_H
