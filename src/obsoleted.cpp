
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wsign-conversion"
#if 0
// OBSOLETE: refactored into getfootprint, read_fpfile, readfootprints
FullFootprint parsefootprint(Chromosome const & chr,std::string const & entry){
    std::vector<std::string> splitent{split(entry,'\t')};
    assert(chr.name==splitent[0]);
    return FullFootprint(chr,stoull(splitent[1]),stoull(splitent[2]));
}
#endif
#pragma clang diagnostic pop

// Old Shame
#if 0
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
#endif
#if 0 //Should be unused now, and is a dirty template

/// Appends a new item if unequal to last element

/// \arg &coll A collection storing elements of template type T
/// \arg el An object of template type T
/// Appends el to coll except if this duplicates the last element of coll.
/// \return coll, by-ref
template<typename V,typename T>
V & pushifnew(V & coll, T && el){
    if (coll.size() == 0 || coll[coll.size()-1] != el)
        coll.push_back(el);
    return coll;
}

#endif

// Start of new code
#if 0 //shame on me
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
