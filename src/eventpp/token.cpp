#include "eventpp/manager.hpp"
#include "eventpp/token.hpp"

namespace eventpp {

token::token()
	: m_mgr(nullptr) {
}

token::~token() {
	while (!m_subs.empty()) {
		m_mgr->unsubscribe(m_subs.back());
		m_subs.pop_back();
	}
}

void token::subscribe(size_t code) {
	m_subs.push_back(code);
}

}