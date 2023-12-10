#ifndef PPMINT_EXCEPTIONS_H
#define PPMINT_EXCEPTIONS_H

#include <iostream>
#include <format>

namespace peppermint {
	namespace exceptions {
		namespace gameObject {
			/// <summary>
			/// Thrown when a GameObject already has a Component of a certain type, and thus cannot have another of that type added.
			/// </summary>
			class AlreadyHasComponentException : public std::exception {
			public:
				virtual const char* what() const noexcept override {
					return "This game object already has a component of that type.";
				}
			};
			/// <summary>
			/// Thrown when a Component of a certain type cannot be found on a GameObject.
			/// </summary>
			class ComponentNotFoundException : public std::exception {
			public:
				virtual const char* what() const noexcept override {
					return "This game object does not have a component of that type.";
				}
			};
			/// <summary>
			/// Thrown when the provided type does not inherit from peppermint::game::Component.
			/// </summary>
			class IsNotComponentException : public std::exception {
			public:
				virtual const char* what() const noexcept override {
					return "The provided type was not a component.";
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
					virtual const char* what() const noexcept override {
						return "Cannot open file.";
					}
				};
			}

			namespace tileset {
				/// <summary>
				/// Thrown when an invalid TextureSet index is provided.
				/// </summary>
				class InvalidTextureSetIndexException : public std::exception {
				public:
					virtual const char* what() const noexcept override {
						return "Invalid texture set index.";
					}
				};
			}
			
			namespace texture {
				/// <summary>
				/// Thrown when a Texture cannot be loaded.
				/// </summary>
				class CannotLoadTextureException : public std::exception {
				public:
					virtual const char* what() const noexcept override {
						return "Cannot load texture.";
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
				virtual const char* what() const noexcept override {
					return "The coordinates provided were out of range.";
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
					virtual const char* what() const noexcept override {
						return "The provided game file is corrupted.";
					}
				};
				/// <summary>
				/// Thrown when a provided file is not a game file.
				/// </summary>
				class InvalidFileTypeException : public std::exception {
				public:
					virtual const char* what() const noexcept override {
						return "The provided file is not a game file.";
					}
				};
				/// <summary>
				/// Thrown when attempting to load a game without a game file.
				/// </summary>
				class NoGameFilePathException : public std::exception {
				public:
					virtual const char* what() const noexcept override {
						return "No game file path (asset) has been set.";
					}
				};
			}
			namespace world {
				/// <summary>
				/// Thrown when a world file is corrupted.
				/// </summary>
				class CorruptedFileException : public std::exception {
				public:
					virtual const char* what() const noexcept override {
						return "The provided world file is corrupted.";
					}
				};
				/// <summary>
				/// Thrown when a provided file is not a world file.
				/// </summary>
				class InvalidFileTypeException : public std::exception {
				public:
					virtual const char* what() const noexcept override {
						return "The provided file is not a world file.";
					}
				};
			}
			namespace asset {
				/// <summary>
				/// Thrown when an asset file is corrupted.
				/// </summary>
				class CorruptedFileException : public std::exception {
				public:
					virtual const char* what() const noexcept override {
						return "The provided asset file is corrupted.";
					}
				};
				/// <summary>
				/// Thrown when a provided file is not an asset file.
				/// </summary>
				class InvalidFileTypeException : public std::exception {
				public:
					virtual const char* what() const noexcept override {
						return "The provided file is not an asset file.";
					}
				};
			}
		}
		namespace sound {
			namespace device {
				/// <summary>
				/// Thrown when there is no device available with a specified name.
				/// </summary>
				class NoDeviceAvailableException : public std::exception {
				public:
					virtual const char* what() const noexcept override {
						return "There is no audio device available.";
					}
				};
				/// <summary>
				/// Thrown when a sound context cannot be created.
				/// </summary>
				class CannotCreateContextException : public std::exception {
				public:
					virtual const char* what() const noexcept override {
						return "Could not create a sound context.";
					}
				};
				/// <summary>
				/// Thrown when a sound context cannot be removed.
				/// </summary>
				class CannotRemoveContextException : public std::exception {
				public:
					virtual const char* what() const noexcept override {
						return "Could not remove sound context.";
					}
				};
				/// <summary>
				/// Thrown when a sound device cannot be closed.
				/// </summary>
				class CannotCloseDeviceException : public std::exception {
				public:
					virtual const char* what() const noexcept override {
						return "Could not close sound device.";
					}
				};
			}
			namespace file {
				/// <summary>
				/// Thrown when a sound file cannot be opened.
				/// </summary>
				class CannotOpenFileException : public std::exception {
				public:
					virtual const char* what() const noexcept override {
						return "Could not open a sound file.";
					}
				};
				/// <summary>
				/// Thrown when a sound file has either less than 1 sample or more samples than can be used.
				/// </summary>
				class BadSampleCountException : public std::exception {
				public:
					virtual const char* what() const noexcept override {
						return "Unusable number of samples in a sound file.";
					}
				};
				/// <summary>
				/// Thrown when a sound file has less than 1 or more than 4 channels.
				/// </summary>
				class UnsupportedChannelCountException : public std::exception {
				public:
					virtual const char* what() const noexcept override {
						return "An audio file has an unsupported number of channels.";
					}
				};
				/// <summary>
				/// Thrown when the samples in a sound file could not be read.
				/// </summary>
				class CouldNotReadSamplesException : public std::exception {
				public:
					virtual const char* what() const noexcept override {
						return "Could not read the samples in a sound file.";
					}
				};
			}
			namespace openal {
				/// <summary>
				/// Catch-all exception for OpenAL errors.
				/// </summary>
				class GenericException : public std::exception {
				public:
					std::string message;
					GenericException(std::string message) { this->message = "OpenAL Error: " + message; };
					virtual const char* what() const noexcept override {
						return message.c_str();
					}
				};
			}
		}
	}
}

#endif