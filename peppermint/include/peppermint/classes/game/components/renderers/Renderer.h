#ifndef PPMINT_COMPONENT_RENDERER_H
#define PPMINT_COMPONENT_RENDERER_H

#include <peppermint/classes/game/Component.h>

namespace peppermint {
	namespace game {
		namespace components {
			class Renderer : public Component {
			public:
				virtual void render();
			};
		}
	}
}

#endif