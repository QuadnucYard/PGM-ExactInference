#pragma once
#include <map>
#include <set>
#include <string>
#include <valarray>
#include <vector>

namespace pgm {

	// 类型定义
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

	// 随机变量
	struct Variable {
		fid_t id;
		fid_t numValues;
		std::string name;
		std::string abbr;
	};

	using VariableList = std::vector<Variable>;

	// 查询
	struct ProbQuery {
		fidpairlist marginal; //查询的变量及其取值
		fidpairlist given;	  //给定的变量及其取值
	};

	using ProbQueryList = std::vector<ProbQuery>;

} // namespace pgm