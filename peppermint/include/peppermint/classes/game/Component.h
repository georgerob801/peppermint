#ifndef PPMINT_COMPONENT_H
#define PPMINT_COMPONENT_H

namespace peppermint {
	namespace game {
		class Component {
		public:
			virtual void start();
			virtual void awake();
			virtual void loop();

			Component* setGameObject(void* gameObject);
			void* getGameObject();

			void initialise();
			bool isInitialised();

			void disable();
			void enable();
			bool isEnabled();
		private:
			void* gameObject;
		protected:
			bool initialised = false;
			bool enabled;
		};
	}
}

#endif