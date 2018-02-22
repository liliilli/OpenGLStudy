#ifndef OPGS16_OBJECTS_DEBUG_DEFAULT_OBJECT_DATE_h
#define OPGS16_OBJECTS_DEBUG_DEFAULT_OBJECT_DATE_h

#include "..\..\GlobalObjects\Canvas\text.h"    /*! Canvas::Text */

class ObjectDate : public Canvas::Text {
public:
    ObjectDate() : Canvas::Text{ "", glm::vec3{16, -24, 0} } {
        SetColor({ 1, 1, 1 });
		SetOrigin(IOriginable::Origin::UP_LEFT);
        SetFontName("Solomon");
        SetFontSize(8u);
    }
};

#endif // !OPGS16_OBJECTS_DEBUG_DEFAULT_OBJECT_DATE_h