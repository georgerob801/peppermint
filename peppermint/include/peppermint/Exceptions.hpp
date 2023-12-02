#ifndef PPMINT_EXCEPTIONS_H
#define PPMINT_EXCEPTIONS_H

#include <iostream>

namespace peppermint {
	namespace exceptions {
		namespace gameObject {
			/// <summary>
			/// Thrown when a GameObject already has a Component of a certain type, and thus cannot have another of that type added.
			/// </summary>
			class AlreadyHasComponentException : public std::exception {
			public:
				char* what() {
					return (char*)"This game object already has a component of that type.";
				}
			};
			/// <summary>
			/// Thrown when a Component of a certain type cannot be found on a GameObject.
			/// </summary>
			class ComponentNotFoundException : public std::exception {
			public:
				char* what() {
					return (char*)"This game object does not have a component of that type.";
				}
			};
			/// <summary>
			/// Thrown when the provided type does not inherit from peppermint::game::Component.
			/// </summary>
			class IsNotComponentException : public std::exception {
			public:
				char* what() {
					return (char*)"The provided type was not a component.";
				}
			};
		}
		namespace rendering {
			namespace shader {
				/// <summary>
				/// Thrown when a shader file cannot be opened.
				/// </summary>
				class CannotOpenFileException : public std::exception {
				public:
					char* what() {
						return (char*)"Cannot open file.";
					}
				};
			}

			namespace tileset {
				/// <summary>
				/// Thrown when an invalid TextureSet index is provided.
				/// </summary>
				class InvalidTextureSetIndexException : public std::exception {
				public:
					char* what() {
						return (char*)"Invalid texture set index.";
					}
				};
			}
			
			namespace texture {
				/// <summary>
				/// Thrown when a Texture cannot be loaded.
				/// </summary>
				class CannotLoadTextureException : public std::exception {
				public:
					char* what() {
						return (char*)"Cannot load texture.";
					}
				};
			}
		}
		namespace component {
			/// <summary>
			/// Thrown when provided coordinates are in an invalid position.
			/// </summary>
			class InvalidCoordinateException : public std::exception {
			public:
				char* what() {
					return (char*)"The coordinates provided were out of range.";
				}
			};
		}
		namespace serialisation {
			namespace game {
				/// <summary>
				/// Thrown when a game file is corrupted.
				/// </summary>
				class CorruptedFileException : public std::exception {
				public:
					char* what() {
						return (char*)"The provided game file is corrupted.";
					}
				};
				/// <summary>
				/// Thrown when a provided file is not a game file.
				/// </summary>
				class InvalidFileTypeException : public std::exception {
				public:
					char* what() {
						return (char*)"The provided file is not a game file.";
					}
				};
				/// <summary>
				/// Thrown when attempting to load a game without a game file.
				/// </summary>
				class NoGameFilePathException : public std::exception {
				public:
					char* what() {
						return (char*)"No game file path (asset) has been set.";
					}
				};
			}
			namespace world {
				/// <summary>
				/// Thrown when a world file is corrupted.
				/// </summary>
				class CorruptedFileException : public std::exception {
				public:
					char* what() {
						return (char*)"The provided world file is corrupted.";
					}
				};
				/// <summary>
				/// Thrown when a provided file is not a world file.
				/// </summary>
				class InvalidFileTypeException : public std::exception {
				public:
					char* what() {
						return (char*)"The provided file is not a world file.";
					}
				};
			}
			namespace asset {
				/// <summary>
				/// Thrown when an asset file is corrupted.
				/// </summary>
				class CorruptedFileException : public std::exception {
				public:
					char* what() {
						return (char*)"The provided asset file is corrupted.";
					}
				};
				/// <summary>
				/// Thrown when a provided file is not an asset file.
				/// </summary>
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