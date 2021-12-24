#pragma once

#include <emitter.hpp>

namespace epp {

/**
 * @brief defines an abstract object that subscribes to events from emitters
 */
class observer {
public:
	/**
	 * @brief construct the observer
	 *
	 * @param em the emitter to subscribe to
	 */
	observer(emitter& em);
	virtual ~observer();

	/**
	 * @brief subscribe to the event
	 *
	 * @param evt the event code to subscribe to
	 * @param cb the callback to use
	 */
	void hook(int evt, emitter::callback cb);

	/**
	 * @brief unsubscribe from an event
	 *
	 * @param evt the event to unsubscribe from
	 */
	void unhook(int evt);

	/**
	 * @brief unsubscribe from all events
	 *
	 */
	void unhook();

private:
	friend class emitter;

	/**
	 * @brief called by emitter on destruction to indicate it's no longer valid
	 *
	 */
	void invalidate();

	emitter& m_em;	 /// the saved emitter object

	bool m_invalid;	  /// has the emitter been destroyed?
};

}
