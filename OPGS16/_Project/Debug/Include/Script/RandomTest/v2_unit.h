#ifndef DEBUG_PROJECT_SCRIPT_RANDOMTEST_V2_UNIT_H
#define DEBUG_PROJECT_SCRIPT_RANDOMTEST_V2_UNIT_H

///
/// @license BSD 2-Clause License
///
/// Copyright (c) 2018, Jongmin Yun(Neu.), All rights reserved.
/// If you want to read full statements, read LICENSE file.
///

#include <Component/script_frame.h>
#include <Frame/timer_handle.h>
#include <Helper/Type/color.h>

namespace debug::script {
class VectorDistribution;
}

namespace debug::script {

class Vector2UnitRandomTest final : public opgs16::component::CScriptFrame {
public:
  OP16_SCRIPT_GENERATE(Vector2UnitRandomTest);

private:
  opgs16::element::CObject* m_subject = nullptr;
  opgs16::element::CObject* m_object = nullptr;

  script::VectorDistribution* m_dist_obj = nullptr;

  enum class EState { Processing, Success, Failure };
  EState m_state = EState::Processing;

  opgs16::element::CTimerHandle m_timer;
  opgs16::element::CTimerHandle m_timer_return;

  const int32_t m_test_count = 1'000;

  void Initiate() override final;
  void Start() override final {};
  void Update(float delta_time) override final;
  void Destroy() override final;

  opgs16::DColor m_success = opgs16::DColor::Blue;
  opgs16::DColor m_failure = opgs16::DColor::Red;
  bool m_is_color_changed = false;

  void Tick();
  void ExecuteSuccess();
  void ExecuteFailure();
  void Exit();
};

} /// ::debug::script namespace

#endif /// DEBUG_PROJECT_SCRIPT_RANDOMTEST_V2_UNIT_H