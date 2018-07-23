
///
/// @license BSD 2-Clause License
///
/// Copyright (c) 2018, Jongmin Yun(Neu.), All rights reserved.
/// If you want to read full statements, read LICENSE file.
///
/// @file Element/Canvas/canvas.cc
///
/// @brief Definition file of ./canvas.h
///
/// @log
/// 2018-04-17 Add comments and move definition functions to ::opgs16::element::canvas namespace.
/// 2018-04-17 Move file path to System/Element/Canvas/Private.
///

/// Header file
#include <Element/Canvas/canvas.h>

#include <array>
/// ::opgs16::component::CCamera
#include <Component/camera.h>
#include "Core/core_setting.h"

namespace opgs16::element::canvas {

CCanvas::CCanvas() : m_is_size_changed{ true } {
  using Camera = component::CCamera;
  AddComponent<Camera>(*this, Camera::ViewType::ORTHO, Camera::CameraType::SUB);
  m_camera = GetComponent<Camera>();
}

void CCanvas::LocalUpdate() {
  using opgs16::setting::GetScreenWidth;
  using opgs16::setting::GetScreenHeight;

	if (m_is_size_changed) {
		UpdateScreenXYWH({0, 0, GetScreenWidth(), GetScreenHeight()});
		m_is_size_changed = false;
	}

	UiObject::LocalUpdate();
}

void CCanvas::Render() {
  glDisable(GL_DEPTH_TEST);

  for (auto& child : GetGameObjectList())
    child.second->Draw();

  glEnable(GL_DEPTH_TEST);
}

const glm::mat4& CCanvas::GetUiCameraPVMatrix() const {
	return m_camera->PvMatrix();
}

const glm::mat4& CCanvas::GetUiCameraProjectMatrix() const noexcept {
  return m_camera->ProjectionMatrix();
}

const glm::mat4& CCanvas::GetUiCameraViewMatrix() const noexcept {
  return m_camera->ViewMatrix();
}

} /// ::opgs16::element::canvas namespace
