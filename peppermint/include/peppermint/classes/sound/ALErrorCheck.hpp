#ifndef PPMINT_AL_ERROR_CHECK
#define PPMINT_AL_ERROR_CHECK

#include <AL/al.h>
#include <peppermint/Exceptions.hpp>

namespace peppermint {
	namespace sound {
		class ALErrorCheck {
		public:
			/// <summary>
			/// Check for errors thrown by OpenAL.
			/// </summary>
			void errorCheck() {
				ALenum err = alGetError();
				if (err != AL_NO_ERROR) throw peppermint::exceptions::sound::openal::GenericException(alGetString(err));
			}
		};
	}
}

#endif