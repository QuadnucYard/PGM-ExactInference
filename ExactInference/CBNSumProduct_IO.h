#pragma once

#include "CBNSumProduct.h"
#include "iohelper.h"

class CBNSumProductReader {
private:
	CBNSumProductReader() = delete;
public:
	static CBNSumProduct Read_BN(const std::string&);
	static CBNSumProduct::QueryList Read_Query(const std::string&);
};

class CBNSumProductWriter {
private:
	CBNSumProductWriter() = delete;
public:
	static void OutputResult(const std::string&, const fvallist&);
};
