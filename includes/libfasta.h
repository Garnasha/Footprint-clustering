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

#include <cstdio>
#include <cassert>
#include <cstddef>

#include <iostream>
#include <fstream>
#include <string>

#include <vector>
#include <tuple>

#include <numeric>
#include <algorithm>
#include <unordered_map>

#include "dnatypes.h"
#include "footprinttypes.h"

namespace footprint_analysis{

using std::string;
using std::ifstream;
using std::vector;


const std::string datapath{"/home/sal/scriptie/data/"};
const std::string refpath{datapath+"reffa/"};
const std::string monocytes{"Monocytes_0.05FDR_FOOTPRINTS"};

typedef std::pair<size_t,size_t> Slice;
typedef Slice Location;


std::vector<std::string> readlines(string const & fname);

Chromosome readfa(std::string const & chrN);

std::vector<std::string> split(std::string const & s, char delim);

bool getfootprint(FILE * input, BlindFootprint & fp);

std::unordered_map<std::string, std::vector<Location>> read_fpfile(
        std::string const & fpfilename);

fp_map load_fp_map(std::string const & fpfilename);

std::vector<FullFootprint> load_full_footprints(std::string const & fpfilename);


}//namespace ReadFasta
#endif //LIBFASTA_H
