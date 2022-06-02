////////////////////////////////////////////////////////////////////////////////
// CBNSumProduct_OutputToYAML.cpp
// 输出查询结果到YAML文件
////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "CBNSumProduct.h"

#ifdef USE_YAML

//输出查询结果到YAML文件
void CBNSumProduct::OutputToYAML()
{
	YAML::Node root;

	for (fval_t qr : m_QueryResults)
	{
		root["prob"].push_back(std::format("{:.6f}", qr));
	}

	namespace fs = std::filesystem;
	fs::path path = fs::current_path() / "Data" / "Output.yaml";
	std::ofstream fout(path);
	fout << root;
	fout.close();

	ShellExecute(NULL, L"open", path.c_str(), NULL, NULL, SW_SHOWNORMAL);
}

#endif // USE_YAML