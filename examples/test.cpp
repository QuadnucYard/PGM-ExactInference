#include <iostream>
#include "Factor.h"
#include "stl_utils.h"
#include "qyalgo.hpp"
#include "qyviews_exp.hpp"
#include <ranges>
//#include "CliqueTree.h"
//#include "CBNSumProduct.h"

using namespace std;
using namespace pgm;
using namespace qy;
template <class T>
std::ostream& operator <<(std::ostream& out, const std::vector<T>& rhs) {
	out << "{";
	std::copy(begin(rhs), end(rhs), std::ostream_iterator<T>(out, ","));
	out << "}";
	return out;
}
template <class T>
std::ostream& operator <<(std::ostream& out, const std::valarray<T>& rhs) {
	out << "{";
	std::copy(begin(rhs), end(rhs), std::ostream_iterator<T>(out, ","));
	out << "}";
	return out;
}
template <std::ranges::range _Rng>
void print_range(_Rng&& _Range) {
	cout << "{";
	std::copy(_Range, std::ostream_iterator<std::ranges::range_value_t<_Rng>>(cout, ","));
	cout << "}";
}
void test_factor() {
	vector<Variable> allvars = {
		{0, 2}, {1, 3}, {2, 2}, {3, 3}, {4, 2}
	};
	/*ProbQuery jhfgf;
	Factor f({{0, 2}, {1, 2}, {2, 3}, {3, 2}}, {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23});
	cout << "reduce" << endl;
	f.sumOutVariable(0);
	cout << f.createStride() << endl;
	auto r = f.reduceGivenVariables({{2, 1}, {0, 0}});
	std::ranges::transform(r.m_vars, std::ostream_iterator<int>(cout, ","), &fidpair::first);
	cout << endl;
	cout << r.m_vals << endl;

	cout << "sum over b" << endl;
	r = f.sumOutVariable(2);
	std::ranges::transform(r.m_vars, std::ostream_iterator<int>(cout, ","), &fidpair::first);
	cout << endl;
	cout << r.m_vals << endl;

	cout << "normalized" << endl;
	r = f.normalized();
	std::ranges::transform(r.m_vars, std::ostream_iterator<int>(cout, ","), &fidpair::first);
	cout << endl;
	cout << r.m_vals << endl;


	f = Factor({{1, 2}, {2, 3}, {3, 2}}, {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11});
	cout << "f1" << endl;
	std::ranges::transform(f.m_vars, std::ostream_iterator<int>(cout, ","), &fidpair::first);
	cout << endl;
	std::ranges::copy(f.m_vals, std::ostream_iterator<int>(cout, ","));
	cout << endl;

	Factor f2({{0, 2}, {2, 3}}, {0, 1, 2, 3, 4, 5});
	cout << "f2" << endl;
	std::ranges::transform(f2.m_vars, std::ostream_iterator<int>(cout, ","), &fidpair::first);
	cout << endl;
	std::ranges::copy(f2.m_vals, std::ostream_iterator<int>(cout, ","));
	cout << endl;
	Factor f3 = f * f2;
	cout << "f3" << endl;
	std::ranges::transform(f3.m_vars, std::ostream_iterator<int>(cout, ","), &fidpair::first);
	cout << endl;
	std::ranges::copy(f3.m_vals, std::ostream_iterator<int>(cout, ","));
	cout << endl;*/

}
void test_cliquetree() {
	/*CliqueTree ct;
	ct.addEdge(1, 2);
	ct.addEdge(0, 1);
	ct.build(1);
	pgm::CliqueTree x({});*/
	//Factor f(fidpairlist{{0, 2}});
	//Factor f({{0, 2}, {1, 2}, {2, 3}, {3, 2}}, {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23});
	//Factor ff = f.sumOutVariable({0, 2});

}
template <std::ranges::random_access_range _Rng>
auto test_return(_Rng&& _Range) {
	using value_type = std::ranges::range_value_t<_Rng>;
	return pair<int, value_type&>(1, (_Range[0]));
}
auto test_return2(vector<int>& xxx) {
	return pair<int, int&>(1, xxx[0]);
}
int main() {
	
	vector<int> a {8, 6, 4, 3, 2, 1, 5, 7};
	vector<int> b(a.size());
	qy::ranges::argsort(a, b.begin());
	std::ranges::copy(b, std::ostream_iterator<int>(cout, ","));
	cout << endl;
	//5,4,3,2,6,1,7,0,  每个位置元素在排序前的位置

	cout << "==================\n";

	{
		vector<int> a {3, 6, 3, 4, 5,7};
		for (auto[i, x] : a | qy_exp::ranges::views::enumerate()) {
			//cout << p.first << ":" << p.second << endl;
			x *= 2;
		}
		for (auto&& p : a | qy_exp::ranges::views::enumerate()) {
			cout << p.first << ":" << p.second << endl;
		}
		// transform之类的是会重复计算的

		//vector<int> b {6, 4, 5};
		//auto xx = a | qy_exp::views::except(b);
		////print_range(xx);
		//cout << "size: " << std::ranges::size(xx) << endl;
		//for (auto&& x : xx) {
		//	cout << x << " ";
		//}
	}//std::views::filter

	test_cliquetree();

	{
		vector<int> a {6, 4, 2, 4, 5};
		auto p = test_return(a);
		p.second = 7;
		cout << a << endl;
	}

	return 0;
}