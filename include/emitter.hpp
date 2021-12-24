#pragma once

#include <functional>

#include <data.hpp>

namespace epp {

class observer;

/**
 * @brief defines an abstract object that emits events to observers
 */
class emitter {
public:
	// callback typedef
	typedef std::function<void(data d)> callback;

	virtual ~emitter();

	/**
	 * @brief emit an event
	 *
	 * @param e the event code to emit
	 * @param d the data to send with the event
	 */
	void emit(int e, data d);

private:
	friend class observer;

	/// mapping of events to callbacks, one per observer
	typedef std::unordered_map<int, callback> hookmap;

	/**
	 * @brief hooks an observer into an event
	 *
	 * @param ob the observer to hook
	 * @param e the event to connect to
	 * @param cb the callback used for the event
	 */
	void hook(observer& ob, int e, callback cb);

	/**
	 * @brief unhooks an observer from a specific event
	 *
	 * @param ob the observer to unhook
	 * @param e the event to unhook it from
	 */
	void unhook(observer& ob, int e);

	/**
	 * @brief unhook an observer from all of its events
	 *
	 * @param ob the observer to remove
	 */
	void unhook(observer& ob);

	/// all observers and their hookmaps
	std::unordered_map<observer*, hookmap> m_hooks;
};

}
