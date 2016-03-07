#include <iostream>
#include <string>
#include <algorithm>
#include "libdna.h"

using namespace dnaTools;
using std::string;

const string g_data_dir = "../data/";

void Sequence::readFa(std::ifstream& fastaFile){
	string buffer;
	if(!(fastaFile.get()=='>')) 
		std::cerr << "Warning: Fasta file did not start with '>'.";
	getline(fastaFile,tag);
	while(fastaFile){
		buffer.clear();
		getline(fastaFile,buffer);
		for (char c : buffer){
			seq.push_back(c);
		}
	}
}

Sequence::Sequence(const string& path) {
	readFaPath(path);
}

Sequence::Sequence() {}

void Sequence::newRead(const std::string& path){
	tag = "";
	seq = std::vector<base>();
	readFaPath(path);
}

void Sequence::readFaPath(const string& path) {
	std::ifstream faFile(path);
	readFa(faFile);
}

SubSequence Sequence::slice(const int& begin, const int& end) const{
	return SubSequence(begin,end,*this);
}

const string& Sequence::getTag() const {
	return tag;
}

std::vector<base>::const_iterator Sequence::begin() const{
	return seq.begin();
}

std::vector<base>::const_iterator Sequence::end() const{
	return seq.end();
}

int  Sequence::size() const{
	return seq.size();
}




SubSequence::SubSequence(const int& begin, const int& end, 
		const Sequence& fullseq): 
	begin(begin), end(end),
	tag(fullseq.getTag()),
	seq(std::vector<base>(
		fullseq.begin()+
		(std::max(0,std::min(std::min(end,fullseq.size()),begin))) ,
		fullseq.begin()+(std::min(end,fullseq.size()))
		)
	)
	{}

string SubSequence::seqString() const{
	return string(seq.begin(),seq.end());
}

const string& SubSequence::getTag() const{
	return tag;
}

string SubSequence::locString() const{
	return tag + " " + std::to_string(begin) + " " + std::to_string(end);
}

string SubSequence::fullString() const{
	return locString() + " " + seqString();
}

std::vector<SubSequence> dnaTools::footprintList(std::ifstream& bed3file){
	std::vector<SubSequence> accu;
	string tag;
	int begin,end;
	Sequence open;
	while(bed3file){
		bed3file >> tag >> begin >> end;
//		if(tag != "chr1"){
//			std::cout << "Reached non-chr1 tag " + tag << std::endl;
//			break; 
//		}
		if(tag != open.getTag()){
			std::cout << "Opening " 
				<< g_data_dir + "reffa/" + tag + ".fa" << std::endl;
			open.newRead(g_data_dir + "reffa/" + tag + ".fa");
			std::cout << "Open chromosome has size " 
				<< open.size() << std::endl;
		}
		accu.push_back(open.slice(begin,end));
	}
	return accu;
}
