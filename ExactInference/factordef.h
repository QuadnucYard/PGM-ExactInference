#pragma once
#include <vector>
#include <set>
#include <map>
#include <string>
#include <valarray>

namespace pgm {

	// ���Ͷ���
	using fid_t = unsigned int;
	using fval_t = double;
	using fidlist = std::vector<fid_t>;
	using fvallist = std::vector<fval_t>;
	using fvalarr = std::valarray<fval_t>;
	using fidset = std::set<fid_t>;
	using fidmap = std::map<fid_t, fid_t>;
	using fidpair = std::pair<fid_t, fid_t>;
	using fidsetmap = std::map<fid_t, fidset>;
	using fidmultimap = std::multimap<fid_t, fid_t>;
	using fidpairlist = std::vector<fidpair>;

	// �������
	struct Variable
	{
		fid_t id;
		fid_t numValues;
		std::string name;
		std::string abbr;
	};

	using VariableList = std::vector<Variable>;

	// ��ѯ
	struct ProbQuery
	{
		fidpairlist marginalVars;	//��ѯ�ı�������ȡֵ
		fidpairlist givenVars;		//�����ı�������ȡֵ
	};

	using ProbQueryList = std::vector<ProbQuery>;

}