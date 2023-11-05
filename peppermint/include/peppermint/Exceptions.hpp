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

			class ComponentNotFoundException : public std::exception {
			public:
				char* what() {
					return (char*)"This game object does not have a component of that type.";
				}
			};

			class IsNotComponentException : public std::exception {
			public:
				char* what() {
					return (char*)"The provided type was not a component.";
				}
			};
		}
		namespace rendering {
			namespace shader {
				class CannotOpenFileException : public std::exception {
				public:
					char* what() {
						return (char*)"Cannot open file.";
					}
				};
			}

			namespace tileset {
				class InvalidTextureSetIndexException : public std::exception {
				public:
					char* what() {
						return (char*)"Invalid texture set index.";
					}
				};
			}
			
			namespace texture {
				class CannotLoadTextureException : public std::exception {
				public:
					char* what() {
						return (char*)"Cannot load texture.";
					}
				};
			}
		}
		namespace component {
			class InvalidCoordinateException : public std::exception {
			public:
				char* what() {
					return (char*)"The coordinates provided were out of range.";
				}
			};
		}
		namespace serialisation {
			namespace world {
				class CorruptedFileException : public std::exception {
				public:
					char* what() {
						return (char*)"The provided world file is corrupted.";
					}
				};

				class InvalidFileTypeException : public std::exception {
				public:
					char* what() {
						return (char*)"The provided file is not a world file.";
					}
				};
			}
			namespace asset {
				class CorruptedFileException : public std::exception {
				public:
					char* what() {
						return (char*)"The provided asset file is corrupted.";
					}
				};

				class InvalidFileTypeException : public std::exception {
				public:
					char* what() {
						return (char*)"The provided file is not an asset file.";
					}
				};
			}
		}
	}
}

#endif