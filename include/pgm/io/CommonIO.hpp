/* #pragma once
#include "iohelper.h"
#include "factordef.h"
#include "qyranges.hpp"

namespace pgm::io {

	// 读取查询
	ProbQueryList readQuery(const fs::path& path);

	//输出查询结果
	void outputQueryResult(const fs::path& path, const fvallist& queryResults);

	std::string toQueryString(const ProbQueryList& queries);

	std::string toResultString(const fvallist& queryResults);
} */