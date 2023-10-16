#ifndef PPMINT_EXCEPTIONS_H
#define PPMINT_EXCEPTIONS_H

#include <iostream>

namespace peppermint {
	namespace exceptions {
		namespace gameObject {
			class AlreadyHasComponentException : public std::exception {
			public:
				char* what() {
					return (char*)"This game object already has a component of that type.";
				}
			};
		}
	}
}

#endif