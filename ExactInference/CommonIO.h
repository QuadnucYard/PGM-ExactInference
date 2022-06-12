#pragma once
#include "iohelper.h"
#include "factordef.h"
#include "qyranges.hpp"

namespace pgm::io {

	// ��ȡ��ѯ
	ProbQueryList readQuery(const std::string& filename);

	//�����ѯ���
	std::filesystem::path outputQueryResult(const std::string& filename, const fvallist& queryResults);

}