
template <class T, _SR range R>
inline auto to(R&& r) {
	return T(_SR begin(r), _SR end(r));
}

template <_SR random_access_range _Rng, class _Ty, class _Pj = std::identity>
inline size_t index_of(_Rng&& _Range, const _Ty& _Val, _Pj _Proj = {}) {
	auto it = _SR find(_Range, _Val, _Proj);
	return it == _SR end(_Range) ? -1 : it - _SR begin(_Range);
}

template <_SR random_access_range _Rng, class _Pr, class _Pj = std::identity>
inline size_t index_of_if(_Rng&& _Range, _Pr _Pred, _Pj _Proj = {}) {
	auto it = _SR find_if(_Range, _Pred, _Proj);
	return it == _SR end(_Range) ? -1 : it - _SR begin(_Range);
}

template <_SR input_range _Rng, class _Ty, class _Pj = std::identity>
inline bool includes(_Rng&& _Range, const _Ty& _Val, _Pj _Proj = {}) {
	return _SR find(_Range, _Val, _Proj) != _SR end(_Range);
}

template <_SR input_range _Rng, class _Pj = std::identity>
auto sum(_Rng&& _Range, _Pj _Proj = {}) {
	auto first = _SR begin(_Range);
	const auto last = _SR end(_Range);
	auto val = std::invoke(_Proj, *first++);
	for (; first != last; ++first) {
		val = _STD move(val) + std::invoke(_Proj, *first);
	}
	return val;
}

template <_SR input_range _Rng, class _Pj = std::identity>
auto product(_Rng&& _Range, _Pj _Proj = {}) {
	auto first = _SR begin(_Range);
	const auto last = _SR end(_Range);
	auto val = std::invoke(_Proj, *first++);
	for (; first != last; ++first) {
		val = _STD move(val) * std::invoke(_Proj, *first);
	}
	return val;
	/*return std::accumulate(_SR begin(_Range) + 1, _SR end(_Range),
		std::invoke(_Proj, *_SR begin(_Range)),
		[=](auto x, auto& y) { return x * std::invoke(_Proj, y); });*/
}