#include "stdafx.h"
#include "CCliqueTree.h"

#ifdef USE_YAML

//输出查询结果到YAML文件
void CCliqueTree::OutputToYAML() const
{
	YAML::Node root;
	for (fval_t qr : m_CTQueryResults)
	{
		root["prob"].push_back(std::format("{:.6f}", qr));
	}

	namespace fs = std::filesystem;
	fs::path path = fs::current_path() / "Data" / "CliqueTree_Output.yaml";
	std::ofstream fout(path);
	fout << root;
	fout.close();

	ShellExecute(NULL, L"open", path.c_str(), NULL, NULL, SW_SHOWNORMAL);
}

#endif // USE_YAML
