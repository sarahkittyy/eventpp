#include <algorithm>

#include "eventpp/manager.hpp"

namespace eventpp {

manager::manager()
	: m_sub_code(0) {
}

void manager::raise(int CODE, data d) {
	// seek all handlers
	auto found = m_subs.equal_range(CODE);

	// call them all
	for (auto i = found.first; i != found.second; ++i) {
		i->second.first(d);
	}
}

size_t manager::subscribe(token& tok, int CODE, event_handler fn) {
	size_t sub_code = m_sub_code++;

	m_subs.insert({ CODE, std::make_pair(fn, sub_code) });

	// assign the token a manager parent if none is found
	if (tok.m_mgr == nullptr) {
		tok.m_mgr = this;
	}

	tok.subscribe(sub_code);
	return sub_code;
}

void manager::unsubscribe(size_t sub_code) {
	auto iter = std::find_if(
		m_subs.begin(),
		m_subs.end(),
		[&sub_code](decltype(m_subs)::value_type& i) {
			return i.second.second == sub_code;
		});

	if (iter != m_subs.end()) {
		m_subs.erase(iter);
	}
}

}