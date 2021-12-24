#include "emitter.hpp"

#include <algorithm>

#include <observer.hpp>

namespace epp {

emitter::~emitter() {
}

void emitter::emit(int e, data d) {
	for (auto& [observer, hookmaps] : m_hooks) {
		for (auto& [event, callback] : hookmaps) {
			if (event == e) {
				callback(d);
			}
		}
	}
}

void emitter::hook(observer& ob, int c, callback cb) {
	hookmap& hm = m_hooks[&ob];
	hm[c]		= cb;
}

void emitter::unhook(observer& ob, int e) {
	hookmap& hm = m_hooks[&ob];
	hm.erase(e);
}

void emitter::unhook(observer& ob) {
	m_hooks.erase(&ob);
}

}
