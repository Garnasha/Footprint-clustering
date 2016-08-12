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

#include "sequence.h"
#include <iterator>
#include <type_traits>

#ifndef SEQUENCE_TPP
#define SEQUENCE_TPP

namespace footprint_analysis {
template <typename Obj,typename It>
Obj fold_join(It begin, It end){
    static_assert(std::is_base_of<std::input_iterator_tag,
                  typename std::iterator_traits<It>::iterator_category
                  >::value, "Iterator not an input iterator!\n");
    static_assert(std::is_same<Obj,
                    typename std::iterator_traits<It>::value_type>::value,
                  "Iterator does not match Obj type!\n");
    if (end == begin) {
        return Obj{};
    }
//  if (end<begin) { //only guaranteed to be valid for RandomAccessIterator
//      return Sequence{};
//  }
    // TODO: normal case: prep and loop.
    Obj joined = *begin;
    ++begin;
    for(;begin != end;++begin) {
        joined.absorb_join(*begin);
    }
    return joined;
}

} // namespace footprint_analysis
#endif // SEQUENCE_TPP
