#ifndef OPGS16_SYSTEM_ELEMENT_CANVAS_PUBLIC_IMAGE_H
#define OPGS16_SYSTEM_ELEMENT_CANVAS_PUBLIC_IMAGE_H

/*!
 * @license BSD 2-Clause License
 *
 * Copyright (c) 2018, Jongmin Yun(Neu.)
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 *
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*!---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*
 * @file Element\Canvas\image.h
 * @brief Image object used in Canvas hierarchy.
 *
 * @author Jongmin Yun
 * @log
 * 2018-02-19 Remove Draw(ShaderNew) obsolete method.
 *            Replace Draw(), Update() with Render() and LocalUpdate()
 * 2018-03-11 Correction of UiObject namespace hierarchy positioning, and path.
 * 2018-04-17 Move canvas::CImage into opgs16::element::canvas::CImage.
 *----*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*/

#include <Element\ui_object.h>  /// ::opgs16::element::UiObject
#include <opgs16fwd.h>          /// Forward declaration

namespace opgs16 {
namespace element {
namespace canvas {
/*!
 * @class CImage
 * @brief UI CImage to display one patched image.
 *
 * This class are able to have children, but only UiObject. unless, Run-time error will be invoked.
 * Actual display position of children(UiImage) will be constrained by Image's center position and
 * size.
 *
 * Scale binding and Rotation binding has not been implemented yet.
 *
 * @log
 * 2018-02-19 Remove Draw(ShaderNew) obsolete method.
 */
class CImage : public opgs16::element::UiObject {
public:
	CImage(const std::string& sprite_tag, const CCanvas* const ref_canvas);
	CImage(const std::string& sprite_tag, const std::unique_ptr<CCanvas>& ref_canvas);

	virtual ~CImage() = default;

	/**
	 * @brief Image instance updates x, y, w, h for each frame, referencing with Scale values.
	 * And, updates children calling Parent's Update method.
	 *
	 * This virtual methods can not override any more.
	 */
	void LocalUpdate() override final;

	/**
	 * @brief This calls callee to draw or render something it has.
	 * Afterward, it draws children calling Parent's Draw (no parameter) method.
	 *
	 * This virtual methods can not override any more.
	 */
	void Render() override final;

	/**
	 * @brief Set size.
	 */
	 void SetImageSize(const float width, const float height);

private:
    component::CSprite2DRenderer* m_renderer_ptr;
    CCanvas* const m_ref_canvas;		/** l_value reference of canvas to get projection matrix. */
};

} /*! opgs16::element::canvas */
} /*! opgs16::element */
} /*! opgs16 */

#endif /** OPGS16_SYSTEM_ELEMENT_CANVAS_PUBLIC_IMAGE_H */
