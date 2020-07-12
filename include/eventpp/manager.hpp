#pragma once

#include <functional>
#include <string>
#include <unordered_map>

#include "eventpp/data.hpp"
#include "eventpp/token.hpp"

namespace eventpp {

typedef std::function<void(const data& d)> event_handler;

class manager {
public:
	manager();

	/**
	 * @brief raise an event, calling all subscribers of this event
	 * 
	 * @param CODE the event's ID/code
	 * @param d the data to pass along in this event.
	 */
	void raise(int CODE, data d);

	/**
	 * @brief subscribe to an event.
	 * 
	 * @param tok your subscription token.
	 * @param CODE the event code to subscribe to
	 * @param fn the event handler function
	 * 
	 * @return size_t The subscription code. Save this if you want to manually unsubscribe later.
	 */
	size_t subscribe(token& tok, int CODE, event_handler fn);

	/**
	 * @brief unsusbscribe from an event
	 * 
	 * @param sub_code 
	 */
	void unsubscribe(size_t sub_code);

private:
	/// the map of event codes to event handlers, and their subscription code.
	std::unordered_multimap<
		int,
		std::pair<
			event_handler,
			size_t>>
		m_subs;

	/// the next available subscription code.
	size_t m_sub_code;
};

}