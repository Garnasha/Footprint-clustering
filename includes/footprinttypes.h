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

#ifndef FOOTPRINTTYPES_H
#define FOOTPRINTTYPES_H

#include <string>
#include <vector>
#include <tuple>
#include <unordered_map>

#include "dnatypes.h"

#include "fullfootprint.h"
namespace footprint_analysis {

typedef std::pair<size_t,size_t> Slice;
typedef Slice Location;

struct BlindFootprint{
    std::string chrN;
    Location loc;
};

struct LocalFootprint{
    Sequence seq;
    Location loc;
};

typedef std::unordered_map<std::string,std::vector<LocalFootprint>> fp_map;
} // namespace footprint_analysis
#endif // FOOTPRINTTYPES_H
