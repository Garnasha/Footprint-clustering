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

#include "libfasta.h"

/// \file
/// \brief Library for dealing with fasta files and footprints.

/// Namespace for reading fasta format files and extracting footprints.
namespace ReadFasta{

/// Overload of std::to_string for argument std::vector<Nucleotide>
std::string to_string(std::vector<Nucleotide> const & seq){
    return std::string(seq.begin(),seq.end());
}

/// Simple constructor, looks up and stores sequence and metadata.
Footprint::Footprint(Chromosome const & chr,size_t begin,size_t end):
    chrN(chr.name),
    seq(chr.seq.begin()+begin,chr.seq.begin()+end),
    loc(begin,end)
{}

/// Pretty-printing string cast.

/// \return A single-line pretty-printing representation. 
Footprint::operator std::string () const {
    return this->chrN + " " +                                     //chrN
        std::string(this->seq.begin(),this->seq.end()) +          //seq
        " (" + this->loc.first << ", " + this->loc.second + ")";  //loc
}

/// Slurp a file by lines

/// Opens and slurps a text file, splitting on lines.
/// \return File contents as a vector of lines.
std::vector<std::string> readlines(string const & fname){
    ifstream file{fname.c_str()};
    //TODO(Sal): Maybe replace/supplement this with an exception.
    if(!file) 
        std::cerr << "Could not open file " << fname << std::endl;

    string tmp;
    vector<string> ret;
    while(file){
        getline(file,tmp);
        if(tmp.length()>0)
            ret.push_back(tmp);
    }

    return ret;
}

/// Slurp a fasta file.

/// Opens and slurps the fasta file associated with the chromosome label $chrN.
/// \return A Chromosome with the sequence in the file and the proper metadata.
Chromosome readfa(std::string const & chrN){ 
    auto file = std::ifstream{refpath+chrN+".fa"};
    //TODO(Sal): Maybe replace/supplement this with an exception.
    if(!file)
        std::cerr << "Error opening file " << refpath+chrN+".fa" << std::endl;
    std::string tmp;
    std::vector<Nucleotide> sequence;
    std::getline(file,tmp);
    while(file){
        getline(file,tmp);
        sequence.insert(sequence.end(),tmp.begin(),tmp.end());
    }
    return 
        Chromosome {
        chrN, 
        vector<Nucleotide>(sequence)
        };
}

/// Splits s on delim

/// Splits s on delim, discarding any delim characters.
/// \return An in-order vector of substrings of s.
std::vector<std::string> split(std::string const & s,char delim){
    std::vector<std::string> ret;
    auto begin = s.begin();
    auto end = begin;
    while (end != s.end()){
        while(begin != s.end() && *begin == delim) ++begin;
        end = begin;
        while(end != s.end() && *end != delim) ++end;
        if (distance(begin,end) > 0)
            ret.push_back(std::string(begin,end));
        begin = end;
    }
    return ret;
}

//TODO: Continue refactoring here, adding doxygen comments to refactored code.
//TODO: refactor to create a collection of BlindFootprint per chromosome.
Footprint parsefootprint(Chromosome const & chr,std::string const & entry){
    auto splitent = split(entry,'\t');
    assert(chr.name==splitent[0]);
    return Footprint(chr,stoull(splitent[1]),stoull(splitent[2]));
}

// Appends a new item if unequal to last element

// \arg &coll A collection storing elements of template type T
// \arg el An object of template type T
// Appends el to coll except if this duplicates the last element of coll.
// \return coll, by-ref
template<typename V,typename T>
V & pushifnew(V & coll, T && el){
    if (coll.size() == 0 || coll[coll.size()-1] != el)
        coll.push_back(el);
    return coll;
}


std::vector<Footprint> read_footprints(std::string const fpfilename){
    std::vector<std::string> fpfile(readlines(fpfilename)); 
    /*std::sort(
            fpfile.begin(),
            fpfile.end(),
            [](string const & l,string const & r){
                return split(l,'\t')[0] < split(r,'\t')[0];
                }
            );*/
    std::vector<std::string> chrlist;
    std::cout << "Read fpfile, extracting chrnames..." <<std::endl;
    for(auto s : fpfile){
        assert(s.length()>0);
        pushifnew(chrlist,split(s,'\t')[0]);
    }
    /*std::transform(
            fpfile.begin(),
            fpfile.end(),
            chrlist.begin(),
            [](string const&s) {return split(s,'\t')[0];}
            );*/
    std::vector<Footprint> footprints;
    for(auto chrN : chrlist){
        std::cout << "Reading " << chrN << std::endl;
        Chromosome chr = readfa(chrN);
        std::cout << "Read " << chrN << std::endl;
        std::vector<Footprint> listcomp;//start Julia list comp...
        for(auto s : fpfile) 
            if(split(s,'\t')[0] == chrN)
                listcomp.push_back(parsefootprint(chr,s));
        footprints.insert(footprints.end(),listcomp.begin(),listcomp.end());
    }
    return footprints;
}


}//namespace ReadFasta
