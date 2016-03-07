#include <iostream>
#include "libdna.h"

using std::cout;
using namespace dnaTools;



int main(int argc, char **argv){
	cout << Sequence("../data/reffa/chr1.fa").slice(30000,30050).fullString()
		<< std::endl;
	std::ifstream bed3("../data/Monocytes_0.05FDR_FOOTPRINTS");
	std::vector<SubSequence> footprints = footprintList(bed3);
	for(SubSequence s : footprints){
		cout << s.fullString() << std::endl;
	}
	return 0;
	/*
	std::ifstream infile("../data/reffa/chr1.fa");
	if(infile){
		cout << "Opened chr1.fa" << std::endl;
	}
	sequence seq = readFa(infile);
	cout << seq.size() << std::endl;
	sequence selection(seq.begin()+30000,seq.begin()+30050);
	std::string outbuffer(selection.begin(),selection.end());
	cout << outbuffer << std::endl;
	*/
}
