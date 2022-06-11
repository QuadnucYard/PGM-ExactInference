#pragma once

#include "CliqueTree.h"
#include "iohelper.h"

namespace pgm {

class CCliqueTreeReader {
private:
	CCliqueTreeReader() = delete;
public:
	static CliqueTree Read_CT(const std::string&);
	static ProbQueryList Read_Query(const std::string&);
};

class CCliqueTreeWriter {
private:
	CCliqueTreeWriter() = delete;
public:
	static void OutputResult(const std::string&, const fvallist&);
};

}