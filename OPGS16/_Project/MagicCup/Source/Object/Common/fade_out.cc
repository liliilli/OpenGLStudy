
///
/// @license BSD 2-Clause License
///
/// Copyright (c) 2018, Jongmin Yun(Neu.), All rights reserved.
/// If you want to read full statements, read LICENSE file.
///

/// Header file
#include "../../../Include/Object/Common/fade_out.h"

#include <Component/procedural2d_renderer.h>
#include <Element/Canvas/canvas.h>
#include <Manager/Internal/shader_builtin_keywords.h>

#include "../../../Include/Script/Common/script_fade_out.h"

namespace magiccup {

UiFadeOut::UiFadeOut(int32_t time,
                     std::function<void()> callback,
                     opgs16::element::canvas::CCanvas* canvas_ref,
                     float intensity) :
    m_canvas_ref{canvas_ref} {
  using opgs16::component::CProcedural2DRenderer;
  using opgs16::component::DTexelInfo;
  SetScaleFactor({128.f, 112.f, 0});

  auto renderer = AddComponent<CProcedural2DRenderer>(*this, "opQuad2d");
  renderer->SetSize(1, 1);
  renderer->UpdateBuffer(DTexelInfo{
      opgs16::DVectorInt2{0, 0},
      opgs16::DColor32::Black}
  );
  renderer->SetRenderingLayer("Foremost");

  using opgs16::builtin::s_uniform_alpha;
	renderer->GetWrapper()->SetUniformValue<float>(s_uniform_alpha, 0.0f);

  m_renderer = renderer;

  auto script = AddComponent<ScriptFadeOut>(*this);
  script->SetTimer(time);
  script->SetCallback(callback);
  script->SetIntensity(intensity);
  script->Execute();
}

void UiFadeOut::Render() {
  using namespace opgs16::builtin;

  auto wrapper = m_renderer->GetWrapper();
  wrapper->SetUniformMat4(s_uniform_proj, m_canvas_ref->GetUiCameraProjectMatrix());
	wrapper->SetUniformMat4(s_uniform_view, m_canvas_ref->GetUiCameraViewMatrix());
	wrapper->SetUniformMat4(s_uniform_model, GetModelMatrix());

  m_renderer->RenderSprite();
}

} /// ::magiccup namespace