#pragma once
#include "BayesianNetwork.h"
#include "iohelper.h"

namespace pgm {

	class CBNSumProductReader {
	private:
		CBNSumProductReader() = delete;
	public:
		static BayesianNetwork Read_BN(const std::string&);
		static ProbQueryList Read_Query(const std::string&);
	};

	class CBNSumProductWriter {
	private:
		CBNSumProductWriter() = delete;
	public:
		static void OutputResult(const std::string&, const fvallist&);
	};

}