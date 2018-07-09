#ifndef DEBUG_PROJECT_SCRIPT_SOUNDTEST_ROOT_H
#define DEBUG_PROJECT_SCRIPT_SOUNDTEST_ROOT_H

///
/// @license BSD 2-Clause License
///
/// Copyright (c) 2018, Jongmin Yun(Neu.), All rights reserved.
/// If you want to read full statements, read LICENSE file.
///

#include <Component/script_frame.h>

namespace debug::object {
class ChoiceList;
}

namespace debug::script {

class SoundTestRoot final : public opgs16::component::CScriptFrame {
public:
  OP16_SCRIPT_GENERATE(SoundTestRoot);

  void ExecuteBgmTest();
  void ExecuteEffectTest();
  void ExecuteSurroundTest();
  void ExecuteEntireTest();
  void ExecuteLobby();

private:
  void Initiate() override final;
  void Start() override final;
  void Update(float delta_time) override final;

  bool m_is_pressed = false;

  opgs16::element::CObject* m_subject = nullptr;
  object::ChoiceList* m_list = nullptr;
  opgs16::element::canvas::CText* m_description = nullptr;

  opgs16::element::canvas::CCanvas* m_obj = nullptr;

  enum class EBigState { Lobby, BgmTest, EffectTest, SurroundTest };
  enum class EDetailedState { A, B, C, D, E, F };

  EBigState m_big_state = EBigState::Lobby;
  EDetailedState m_detailed_state = EDetailedState::A;

  void InitializeLobby();

  void InputLobby();
};

} /// ::debug::script namespace

#endif /// DEBUG_PROJECT_SCRIPT_SOUNDTEST_ROOT_H