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
namespace footprint_analysis{

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
    return Chromosome {chrN, std::vector<Nucleotide>(seq)};
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



/// Parses a single footprint from input file to by-ref buffer, returns success.

/// Takes a file opened for reading, and a reference to a BlindFootprint.
/// Assumes the next thing in the open filestream is a footprint specification,
/// parses this, and overwrites the given footprint with it, returning true if
/// the parse appears succesful (false on EOF)
/// \arg input A file opened for reading, pointing at a footprint or EOF.
/// \arg buffer A BlindFootprint to be overwritten by parse.
/// \return True on succesful parse, false on EOF, undef (likely true) otherwise
bool getfootprint(FILE * input, BlindFootprint & buffer){
    char chrNbuffer[8];
    size_t begin,end;
    bool retval =
        EOF != std::fscanf(input,"%7s %zu %zu",chrNbuffer,&begin,&end);
    buffer = BlindFootprint{
        std::string{chrNbuffer},
            Location{std::move(begin),std::move(end)}
    };
    return retval;

}

/// Slurps a footprint file, indexing footprint locations by chromosome

/// \arg fpfilename The full name (including path) of the fp file to slurp.
///
/// Splits each line of the footprint file into a chromosome identifier and a
/// location (i.e. start and stop indices), adding the location to the list
/// identified by the chromosome identifier in the map to be returned.
/// \return An associative map, linking each chromosome identifier to a vector
/// of all locations marked on that chromosome.
std::unordered_map<std::string,std::vector<Location>> read_fpfile(
        std::string const & fpfilename) {
    std::FILE * fpfile = std::fopen(fpfilename.c_str(),"r");
    std::unordered_map<std::string,std::vector<Location>> store;
    BlindFootprint buffer;
    while(getfootprint(fpfile,buffer)){
        store[buffer.chrN].push_back(std::move(buffer.loc));
    }
    return store;
}

/// Load all Footprints, with sequences, indexed on chromosome.

/// \arg fpfilename
/// The full name (including path) of the footprint file to load.
///
/// Slurps the footprint file, then, for each chromosome, loads the reference
/// sequence and looks up the sequence for every footprint Location on that
/// chromosome. Combining Location and Sequence yields a full Footprint, which
/// is stored, to be returned once all Footprints are read.
/// \return An associative map, linking each chromosome identifier to a vector
/// of all Footprints appearing on that chromosome.
//
//fp_map :== std::unordered_map<std::string,std::vector<LocalFootprint>>
fp_map load_fp_map(std::string const & fpfilename) {
    std::unordered_map<std::string,std::vector<Location>> blind_store{
        read_fpfile(fpfilename)};
    std::unordered_map<std::string,std::vector<LocalFootprint>> store;
    for (auto entry : blind_store) {
        Chromosome ref{readfa(entry.first)};
        std::vector<LocalFootprint> footprints{};
        for (Location loc : entry.second){
            footprints.push_back(LocalFootprint{Sequence{ref.seq},loc});
        }
        if (!store.insert(std::make_pair(entry.first,footprints)).second){
            std::cerr << "PANIC! Impossible duplicate key in hash table." <<
                         "\nAborting..." << std::endl;
            assert(false);
        }
    }
    return store;
}

std::vector<FullFootprint> load_full_footprints(std::string const & fpfilename) {
    std::vector<FullFootprint> store;
    std::unordered_map<std::string,std::vector<Location>>
            blind_store{read_fpfile(fpfilename)};
    {
        size_t tot_cap = 0;
        for (auto entry : blind_store) {
            tot_cap += entry.second.size();
        }
        store.reserve(tot_cap);
    }
    for (auto entry : blind_store) {
        Chromosome ref{readfa(entry.first)};
        for (Location loc : entry.second) {
            store.emplace_back(ref,loc.first,loc.second);
        }
    }
    store.shrink_to_fit();
    return store;
}


// End of new code



}//namespace ReadFasta
