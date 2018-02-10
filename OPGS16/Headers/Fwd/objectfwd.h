#ifndef OPGS16_HEADERS_FWD_OBJECT_FWD_H
#define OPGS16_HEADERS_FWD_OBJECT_FWD_H

#include <glm/fwd.hpp>	/** glm matrix forward declaration. */

namespace helper { class ShaderNew; }
namespace camera { class CameraObject; }
namespace texture { class Texture2D; }
namespace shading {
class PostProcessingManager;
}

struct	GLFWwindow;

class   Object;
class	ObjectImpl;
struct	ObjectImplDeleter { void operator()(ObjectImpl* p); };

struct	ObjectTree;

// Derived
namespace Canvas {
class   Canvas;
class   Text;
class   TextImpl;
struct  TextImplDeleter { void operator()(TextImpl* p); };
}

class   Scene;

class   SpriteRenderer;
class   SpriteRendererImpl;
struct  SpriteRendererImplDeleter { void operator()(SpriteRendererImpl* p); };

class   VertexArrayObject;
class   ShaderNew;
class   ShaderWrapper;

/** Managers */
class   FontManager;
class   InputManager;
class   TimeManager;

#endif /** OPGS16_HEADERS_FWD_OBJECT_FWD_H */