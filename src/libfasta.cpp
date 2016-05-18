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

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wold-style-cast"
/// Simple constructor, looks up and stores sequence and metadata.
FullFootprint::FullFootprint(Chromosome const & chr,size_t begin,size_t end):
    chrN(chr.name),
    seq(chr.seq.begin()+(long)begin,chr.seq.begin()+(long)end),
    loc(begin,end)
{}
#pragma clang diagnostic pop

/// Pretty-printing string cast.

/// \return A single-line pretty-printing representation. 

FullFootprint::operator std::string () const {
    return this->chrN + " "                                  //chrN
            + std::string(this->seq.begin(),this->seq.end()) //seq
            + " (" + std::to_string(this->loc.first) +", "
            + std::to_string(this->loc.second) + ")";        //loc
}

/// Slurp a file by lines

/// Opens and slurps a text file, splitting on lines.
/// \return File contents as a vector of lines.
//
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
//
Chromosome readfa(std::string const & chrN){ 
    auto file = std::ifstream{refpath+chrN+".fa"};
    //TODO(Sal): Maybe replace/supplement this with an exception.
    if(!file)
        std::cerr << "Error opening file " << refpath+chrN+".fa" << std::endl;
    std::string tmp;
    std::vector<Nucleotide> seq;
    std::getline(file,tmp);
    while(file){
        getline(file,tmp);
        seq.insert(seq.end(),tmp.begin(),tmp.end());
    }
    return  Chromosome { chrN, std::vector<Nucleotide>(seq) };
}

/// Splits s on delim

/// Splits s on delim, discarding any delim characters.
/// \return An in-order vector of substrings of s.
//
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

/// Appends a new item if unequal to last element

/// \arg &coll A collection storing elements of template type T
/// \arg el An object of template type T
/// Appends el to coll except if this duplicates the last element of coll.
/// \return coll, by-ref
//
template<typename V,typename T>
V & pushifnew(V & coll, T && el){
    if (coll.size() == 0 || coll[coll.size()-1] != el)
        coll.push_back(el);
    return coll;
}

// Start of new code
#if 0
std::istream & getfootprint(std::istream & input, BlindFootprint & fp) {
    //Some bad experience with [fs]scanf... not sure it's optimized properly.
    assert(input);
    //parse chromosome name
    auto chrname = [](std::ifstream & input) constexpr -> std::string {
        char buffer[11];
        for(size_t i = 0;i<11;++i){
            int ci = input.get();
            if(ci == ' '){
                buffer[i]='\0';
                break;
            }
            if (std::char_traits<char>::not_eof(ci) &&
                    is_alphanumeric(static_cast<char>(ci))) {
                buffer[i] = static_cast<char>(ci);
            }
            else {
                throw std::domain_error{"Bad fasta entry (1)."};
            }
        }

        buffer[10] = '\0';
        return std::string{buffer};
    }(input);

    //parse starting index on chromosome
    auto chrname = [](std::ifstream & input) constexpr -> int {
        for(size_t i = 0;i<11;++i){
            int ci = input.get();
            switch(ci){
                case std::char_traits<char>::eof() :
                case '\n' :
                    buffer[i]='\0';
                    break;
                default:
                    if (is_numeric(ci)){
                        buffer[i] = ci;
                    }
                    else {
                        throw std::domain_error{"Bad fasta entry (2)."};
                    }
            }
        }
    }
}
#endif

std::unordered_map<std::string,std::vector<Location>> read_fpfile(
        std::string const & fpfilename) {
    std::ifstream fpfile{fpfilename};
    std::unordered_map<std::string,std::vector<Location>> store;
    BlindFootprint buffer;
    while(getfootprint(fpfile,buffer)){
        store[buffer.chrN].push_back(std::move(buffer.loc));
    }
    return store;
}

std::unordered_map<std::string,std::vector<Footprint>> readfootprints(
        std::string const & fpfilename) {
    std::unordered_map<std::string,std::vector<Location>> blind_store{
        read_fpfile(fpfilename)};
    std::unordered_map<std::string,std::vector<Footprint>> store;
    for (auto entry : blind_store) {
        Chromosome ref{readfa(entry.first)};
        std::vector<Footprint> footprints{};
        for (Location loc : entry.second){
            footprints.push_back(Footprint{Sequence{ref.seq},loc});
        }
        if (!store.insert(std::make_pair(entry.first,footprints)).second){
            std::cerr << "PANIC! Impossible duplicate key in hash table." <<
                         "\nAborting..." << std::endl;
            assert(false);
        }
    }
    return store;
}



// End of new code

//TODO: refactor to create a collection of BlindFootprint per chromosome.
FullFootprint parsefootprint(Chromosome const & chr,std::string const & entry){
    std::vector<std::string> splitent{split(entry,'\t')};
    assert(chr.name==splitent[0]);
    return FullFootprint(chr,stoull(splitent[1]),stoull(splitent[2]));
}

std::vector<FullFootprint> read_footprints(std::string const fpfilename){
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
    std::vector<FullFootprint> footprints;
    for(auto chrN : chrlist){
        std::cout << "Reading " << chrN << std::endl;
        Chromosome chr = readfa(chrN);
        std::cout << "Read " << chrN << std::endl;
        std::vector<FullFootprint> listcomp;//start Julia list comp...
        for(auto s : fpfile) 
            if(split(s,'\t')[0] == chrN)
                listcomp.push_back(parsefootprint(chr,s));
        footprints.insert(footprints.end(),listcomp.begin(),listcomp.end());
    }
    return footprints;
}

}//namespace ReadFasta
