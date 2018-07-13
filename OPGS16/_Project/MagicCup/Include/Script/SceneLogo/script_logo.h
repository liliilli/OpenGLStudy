#ifndef MAGICCUP_SCRIPT_SCENELOGO_OVERALL_H
#define MAGICCUP_SCRIPT_SCENELOGO_OVERALL_H

///
/// @license BSD 2-Clause License
///
/// Copyright (c) 2018, Jongmin Yun(Neu.), All rights reserved.
/// If you want to read full statements, read LICENSE file.
///

#include <Component/script_frame.h>
#include <Frame/timer_handle.h>

namespace magiccup {

class ScriptLogo final : public opgs16::component::CScriptFrame {
public:
  OP16_SCRIPT_GENERATE(ScriptLogo);

private:
  void Initiate() override final;
  void Update(float delta_time) override final;
  void Destroy() override final;

  void ShowLogo();
  void GotoMain();

  opgs16::element::CTimerHandle m_timer;
  opgs16::element::CObject* m_logo = nullptr;
};

} /// ::magiccup namespace

#endif /// MAGICCUP_SCRIPT_SCENELOGO_OVERALL_H