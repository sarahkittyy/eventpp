#include "data.hpp"

namespace epp {

data::data() {
}

data::data(std::initializer_list<std::pair<std::string, std::any>> init) {
	for (auto& [k, v] : init) {
		m_data[k] = v;
	}
}

bool data::has(std::string key) const {
	return m_data.contains(key);
}

void data::clear() {
	m_data.clear();
}

}
