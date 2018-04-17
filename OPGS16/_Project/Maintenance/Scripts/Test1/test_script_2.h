#pragma once

#include "..\..\..\Headers\script_common.h"     /*! component::ScriptFrame */
#include "..\..\..\System\Frame\timer_handle.h" /*! TimerHandle */

class TestScript2 final : public opgs16::component::CScriptFrame {
public:
    TestScript2(opgs16::element::CObject& obj);

    virtual void Update() override final;

private:
    opgs16::manager::MInputManager& m_input;

    virtual void Start() override final {};

    /*! Create members related to type hash value. */
SET_UP_TYPE_MEMBER(::opgs16::component::CScriptFrame, TestScript2)
};
