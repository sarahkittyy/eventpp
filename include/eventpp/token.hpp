#pragma once

#include <vector>

namespace eventpp {

class manager;

/**
 * @brief used to subscribe to events in eventpp::manager
 * required as the destruction of this object will unsubscribe to all events subscribed to
 * via this token.
 * 
 */
class token {
public:
	token();
	~token();

private:
	friend class manager;

	/// all subscribe codes.
	std::vector<size_t> m_subs;

	/// used by the manager class to subscribe to an event
	void subscribe(size_t code);

	/// pointer to the event manager. set on first subscription.
	manager* m_mgr;
};

}