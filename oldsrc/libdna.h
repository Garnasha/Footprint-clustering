#pragma once
#ifndef SJW_DNALIB_H
#define SJW_DNALIB_H
#include <fstream>
#include <vector>

namespace dnaTools{
	typedef char base;

	class SubSequence;

	class Sequence {
		private:
		std::vector<base> seq;//the sequence
		std::string tag;//the tag at the beginning of the file

		/**
		 * for use in the constructor, sets seq and tag
		 * from the given FASTA-formatted ifstream.
		 */
		void readFa(std::ifstream& fastaFile);
		/**
		 * wrapper around readFa, opens the file at path and
		 * passes the resulting ifstream
		 */
		void readFaPath(const std::string& path);

		public:
		/**
		 * Reads in the sequence stored in the file specified by path.
		 * The file specified by path must be in FASTA-format.
		 */
		Sequence(const std::string& path);
		Sequence();

		void newRead(const std::string& path);

		/**
		 * Returns a SubSequence pointing at a slice of seq
		 * running from seq[max(0,begin)] inclusive to 
		 * seq(min(size,end)) exclusive
		 */
		SubSequence slice(const int &begin, const int &end) const;

		const std::string& getTag() const;
		
		std::vector<base>::const_iterator begin() const;
		std::vector<base>::const_iterator end() const;


		int size() const;
	};

	class SubSequence {
		private:
		std::string tag;
		int begin, end;
		std::vector<base> seq;


		public:
		SubSequence(const int& begin, const int& end, 
			const Sequence& fullseq);

		int size() const;
		std::string seqString() const;
		const std::string& getTag() const;
		std::string locString() const;
		std::string fullString() const;
		const std::vector<base>& getSeq() const;
	};

	//TODO: implement in .cpp from here.

	class SmallBase {
		private:
		char id;
		public:
		SmallBase(base content);
		SmallBase(int code);

		char& toInt();
		char toString();
	};

	class ShortSeq{
		private:
		unsigned long long content;
		unsigned char size;
		
		public:
		ShortSeq(SubSequence);

		const unsigned char& getSize() const;
		SmallBase at(const unsigned char& index);
		const unsigned long long& asInt();
	};

	class SeqNode{
		private:
		unsigned int count;
		std::vector<ShortSeq> edges;
		unsigned int treeID;

		public:
		SeqNode();
		SeqNode(const unsigned int& treeID);

		void connect(SeqNode other);
		const unsigned int& getTreeID();
		const std::vector<ShortSeq> getEdges();
		const unsigned int getCount();
	};

	class SeqMipmap {
		private:
		std::vector<SeqNode> list;
		int maxLength;




	};

	std::vector<SubSequence> filterSeqByLength(//TODO:continue


	std::vector<SubSequence> footprintList(std::ifstream& bed3file);
}




#endif // SJW_DNALIB_H
