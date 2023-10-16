#ifndef PPMINT_COMPONENT_H
#define PPMINT_COMPONENT_H

namespace peppermint {
	namespace game {
		class Component {
		public:
			virtual void start();
			virtual void awake();
			virtual void loop();
		private:

		};
	}
}

#endif