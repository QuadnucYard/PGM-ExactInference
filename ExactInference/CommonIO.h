#pragma once
#include "iohelper.h"
#include "factordef.h"
#include "qyranges.hpp"

namespace pgm::io {

	// 读取查询
	ProbQueryList readQuery(const std::string& filename);

	//输出查询结果
	std::filesystem::path outputQueryResult(const std::string& filename, const fvallist& queryResults);

}