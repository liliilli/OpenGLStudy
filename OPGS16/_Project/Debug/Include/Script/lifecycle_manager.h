#ifndef DEBUG_SCRIPT_LIFECYCLE_MANAGER_H
#define DEBUG_SCRIPT_LIFECYCLE_MANAGER_H

///
/// @license BSD 2-Clause License
///
/// Copyright (c) 2018, Jongmin Yun(Neu.), All rights reserved.
/// If you want to read full statements, read LICENSE file.
///
/// @file Debug/Script/lifecycle_manager.h
///

/// ::opgs16::component::CScriptFrame
#include <Component/script_frame.h>
/// ::opgs16::element::CTimerHandle
#include <Frame/timer_handle.h>

namespace debug::script {

class LifecycleManager final : public opgs16::component::CScriptFrame {
public:
  LifecycleManager(opgs16::element::CObject& bind_object) :
      CScriptFrame { bind_object } {};

private:
  void Initiate() override final;
  void Start() override final;
  void Update(float delta_time) override final;
  void Destroy() override final;

  void SpawnObject();

  inline static bool s_instantiated = false;
  opgs16::element::CTimerHandle m_spawn_timer;

SET_UP_TYPE_MEMBER(::opgs16::component::CScriptFrame, LifecycleManager)
};

} /// ::debug::script

#endif /// DEBUG_SCRIPT_LIFECYCLE_MANAGER_H