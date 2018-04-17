#ifndef OPGS16_OBJECTS_DEBUG_DEFAULT_OBJECT_FPS_h
#define OPGS16_OBJECTS_DEBUG_DEFAULT_OBJECT_FPS_h

#include "../../System/Element/Canvas/Public/text.h" /*! ::opgs16::element:canvas::CText */

class ObjectFps : public opgs16::element::canvas::CText {
public:
    ObjectFps() : CText{ "", glm::vec3{16, -16, 0} } {
        SetColor({ 1, 1, 1 });
		SetOrigin(IOriginable::Origin::UP_LEFT);
        SetFontName("Solomon");
        SetFontSize(8u);
    }
};

#endif // !OPGS16_OBJECTS_DEBUG_DEFAULT_OBJECT_FPS_h
