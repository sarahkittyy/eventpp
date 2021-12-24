#pragma once

#include <any>
#include <stdexcept>
#include <string>
#include <unordered_map>

namespace epp {

/**
 * @brief structure that maps string keys to data of arbitrary types
 */
class data {
public:
	/// default constructor
	data();
	/**
	 * @brief brace-initialize with key-value pairs
	 *
	 * @param init the initial value
	 */
	data(std::initializer_list<std::pair<std::string, std::any>> init);

	/**
	 * @brief set a value in the map
	 *
	 * @param key
	 * @param value the value to emplace
	 * @return *this
	 */
	template <typename T>
	data& set(std::string key, T value) {
		m_data[key] = value;
		return *this;
	}

	/**
	 * @brief retrieves a value at the key
	 *
	 * @param key the key to retrieve
	 * @return the value at that key
	 * @remarks throws std::out_of_range if the key doesn't exist
	 */
	template <typename T>
	T get(std::string key) const {
		if (!has(key)) {
			throw std::out_of_range("Key not found in data map");
		}
		return std::any_cast<T>(m_data.at(key));
	}

	/**
	 * @brief returns true if the map contains the specified key
	 */
	bool has(std::string key) const;

	/**
	 * @brief clear all data
	 */
	void clear();

private:
	/// internally saved data
	std::unordered_map<std::string, std::any> m_data;
};

}
