#pragma once

#include "CCliqueTree.h"
#include "iohelper.h"

class CCliqueTreeReader {
private:
	CCliqueTreeReader() = delete;
public:
	static CCliqueTree Read_CT(const std::string&);
	static CCliqueTree::QueryList Read_Query(const std::string&);
};

class CCliqueTreeWriter {
private:
	CCliqueTreeWriter() = delete;
public:
	static void OutputResult(const std::string&, const fvallist&);
};
