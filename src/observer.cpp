#include "observer.hpp"

namespace epp {

observer::observer(emitter& em)
	: m_em(em) {
}

observer::~observer() {
	m_em.unhook(*this);
}

void observer::hook(int evt, emitter::callback cb) {
	m_em.hook(*this, evt, cb);
}

void observer::unhook(int evt) {
	m_em.unhook(*this, evt);
}

void observer::unhook() {
	m_em.unhook(*this);
}

}
