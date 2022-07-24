#pragma once
#include "iohelper.h"
#include "factordef.h"
#include "qyranges.hpp"

namespace pgm::io {

	// ��ȡ��ѯ
	ProbQueryList readQuery(const fs::path& path);

	//�����ѯ���
	void outputQueryResult(const fs::path& path, const fvallist& queryResults);

	std::string toQueryString(const ProbQueryList& queries);

	std::string toResultString(const fvallist& queryResults);
}