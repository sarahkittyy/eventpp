#pragma once

#include <any>
#include <string>
#include <unordered_map>

namespace eventpp {

/**
 * @brief a simple data serializer, used for easily storing and retrieving data
 * to send through events.
 * 
 */
class data {
public:
	data();

	/**
	 * @brief update the data at the given key
	 * 
	 * @param key the key to store the data in
	 * @param value the data to store
	 * @return data& a reference to *this
	 */
	template <class T>
	data& set(const std::string& key, const T value) {
		m_data[key] = value;
		return *this;
	}

	/**
	 * @brief get the value at the given key
	 * 
	 * @tparam T the type of data stored at that key
	 * @param key the key to retrieve
	 * @return T the data at that key
	 */
	template <class T>
	T get(const std::string& key) const {
		return std::any_cast<T>(m_data.at(key));
	}

private:
	/// internally stored data
	std::unordered_map<std::string, std::any> m_data;
};

}