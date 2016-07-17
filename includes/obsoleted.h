#ifndef OBSOLETED_H
#define OBSOLETED_H

#if 0
std::tuple<std::string,size_t,size_t> split_fp(std::string const & entry);
BlindFootprint split_fp(std::string const & entry);
#endif

FullFootprint parsefootprint(Chromosome const & chr,std::string const & entry);

#if 0
template<typename V,typename T>
V & pushifnew(V & v, T && e);
#endif

#if 0 //Old Shame
std::vector<StandaloneFootprint> read_footprints(std::string const fpfilename);
#endif

#endif // OBSOLETED_H
