#include "obj_script_1.h"                           /*! Header file */

#include <glm/glm.hpp>
#include "../../../../GlobalObjects/Canvas/text.h"     /*! Canvas::Text */
#include "../../../../System/Manager/Public/scene_manager.h"  /*! MSceneManager */
#include "../../../../System/Manager/Public/time_manager.h"   /*! MTimeManager */
#include "../../../../System/Manager/Public/timer_manager.h"  /*! MTimerManager */
#include "../../../../System/Components/Public/sprite_renderer.h"    /*! CSprite2DRenderer */

#include "test_script_1.h"      /*! TestScript1 for Canvas */
#include "../../Object/Test1/test_obj.h" /*! TestObject1 for temporary */
#include "../../../../System/Shader/shader_wrapper.h"     /*! ShaderWrapper */

using opgs16::manager::MSceneManager;
using opgs16::element::CObject;

ObjectScript1::ObjectScript1(CObject& obj) : opgs16::component::CScriptFrame{ obj } {
    Initiate();
    Start();
}

void ObjectScript1::Start() {
    //M_SET_TIMER(m_timer_swap, 500, true, this, &ObjectScript1::OnTriggerSwap);
}

void ObjectScript1::DoWork(const size_t mode, const unsigned assigned_number) noexcept {
    m_mode      = mode;
    m_assigned_number = assigned_number;

    switch (m_mode) {
    default: m_moving = true; break;
    case 1: /*! If m_mode is 1, delay each object along with m_assigned_number */
        m_moving = false;
        opgs16::manager::MTimerManager::Instance().SetTimer(m_timer_1_delay, 300 * m_assigned_number,
                                             false, this, &ObjectScript1::OnWork_1Switch);
        break;
    case 4: /*! If m_mode is 4, delay each object along with m_assigned_number */
        m_moving = false;
        opgs16::manager::MTimerManager::Instance().SetTimer(m_timer_4_delay, 200 * m_assigned_number,
                                             false, this, &ObjectScript1::OnTriggered4Delay);
        break;
    case 5: /*! If m_mode is 5, delay each object along with m_assigned_number */
        m_moving = false;
        m_object_original_scale = GetObject().GetScaleValue();
        opgs16::manager::MTimerManager::Instance().SetTimer(m_timer_5_delay, 200 * m_assigned_number,
                                             false, this, &ObjectScript1::OnTriggered5Delay);
        break;
    }
}

void ObjectScript1::Update() {
    if (m_moving) {
        switch (m_mode) {
        case 1: Proceed_1NormalLocal();     break;
        case 3: Proceed_3WorldPosition();   break;
        case 4: Proceed_4AlphaBlending();   break;
        case 5: Proceed_5Scaling();         break;
        default: /*! Do nothing */ break;
        }
    }
}

void ObjectScript1::OnTriggered4Delay() {
    m_moving        = true;
    opgs16::manager::MTimerManager::Instance().SetTimer(m_timer_4_interval, 2'000,
                                         false, this,
                                         &ObjectScript1::OnTriggered4Interval);
}

void ObjectScript1::OnTriggered4Interval() {
    m_moving        = false;
    m_object_alpha  = 1.0f;
    m_elapsed_time  = 0.0f;
    opgs16::manager::MTimerManager::Instance().SetTimer(m_timer_4_waiting, 1'000,
                                         false, this,
                                         &ObjectScript1::OnTriggered4Delay);
}

void ObjectScript1::OnTriggered5Delay() {
    m_moving = true;
}

void ObjectScript1::StopAllTimers() {
    auto& timer = opgs16::manager::MTimerManager::Instance();
    timer.DetachTimer(m_timer_4_interval);
    timer.DetachTimer(m_timer_4_waiting);

    m_object_alpha = 1.0f;
    m_elapsed_time = 0.0f;
    m_moving = false;

    using opgs16::component::CSprite2DRenderer;
    CSprite2DRenderer* renderer = GetObject().GetComponent<CSprite2DRenderer>();
    auto& wrapper = renderer->Wrapper();
    wrapper.SetUniformValue("alpha", m_object_alpha);
}

void ObjectScript1::Proceed_1NormalLocal() {
    auto speed = 2.0f;
    auto local_pos = GetObject().GetLocalPosition();

    if (m_switch == 0) {        /*! Right */
        local_pos.x += speed;
        if (static_cast<int>(local_pos.x) >= 64) ++m_switch;
    }
    else if (m_switch == 1) {   /*! Down */
        local_pos.y -= speed;
        if (static_cast<int>(local_pos.y) <= -64) ++m_switch;
    }
    else if (m_switch == 2) {   /*! Left */
        local_pos.x -= speed;
        if (static_cast<int>(local_pos.x) <= -64) ++m_switch;
    }
    else if (m_switch == 3) {   /*! Up */
        local_pos.y += speed;
        if (static_cast<int>(local_pos.y) >= 64) ++m_switch;
    }
    else if (m_switch == 4) {   /*! Up */
        local_pos.x += speed;
        if (static_cast<int>(local_pos.x) >= 64) ++m_switch;
    }
    else if (m_switch == 5) {
        local_pos.y -= speed;
        if (static_cast<int>(local_pos.y) <= 0) ++m_switch;
    }
    else if (m_switch == 6) {
        local_pos.x -= speed;
        if (static_cast<int>(local_pos.x) <= 0) {
            m_switch = 0;
            m_moving = false;

            auto& canvas = MSceneManager::Instance().PresentScene()->GetObject("GameCanvas");
            if (canvas) {
                TestScript1* canvas_script = canvas->GetComponent<TestScript1>();
                canvas_script->TriggerProcessFinish();
            }
        }
    }

    GetObject().SetLocalPosition(local_pos);
}

void ObjectScript1::Proceed_3WorldPosition() {
    auto pos = GetObject().GetWorldPosition();
    auto speed = 2.0f;

    if (m_switch == 0) {        /*! Right */
        pos.x += speed;
        if (static_cast<int>(pos.x) >= 128+64) ++m_switch;
    }
    else if (m_switch == 1) {   /*! Down */
        pos.y -= speed;
        if (static_cast<int>(pos.y) <= 112-64) ++m_switch;
    }
    else if (m_switch == 2) {   /*! Left */
        pos.x -= speed;
        if (static_cast<int>(pos.x) <= 128-64) ++m_switch;
    }
    else if (m_switch == 3) {   /*! Up */
        pos.y += speed;
        if (static_cast<int>(pos.y) >= 112+64) ++m_switch;
    }
    else if (m_switch == 4) {   /*! Up */
        pos.x += speed;
        if (static_cast<int>(pos.x) >= 128+64) ++m_switch;
    }
    else if (m_switch == 5) {
        pos.y -= speed;
        if (static_cast<int>(pos.y) <= 112) ++m_switch;
    }
    else if (m_switch == 6) {
        pos.x -= speed;
        if (static_cast<int>(pos.x) <= 128) {
            m_switch = 0;
            m_moving = false;

            auto& canvas = MSceneManager::Instance().PresentScene()->GetObject("GameCanvas");
            if (canvas) {
                TestScript1* canvas_script = canvas->GetComponent<TestScript1>();
                canvas_script->TriggerProcessFinish();
            }
        }
    }

    GetObject().SetWorldPosition(pos);
}

void ObjectScript1::Proceed_4AlphaBlending() {
    m_elapsed_time += opgs16::manager::MTimeManager::Instance().GetDeltaTime();
    m_object_alpha = (std::cosf(m_2pi * m_elapsed_time) + 1.0f) / 2;

    using opgs16::component::CSprite2DRenderer;
    CSprite2DRenderer* renderer = GetObject().GetComponent<CSprite2DRenderer>();
    auto& wrapper = renderer->Wrapper();
    wrapper.SetUniformValue("alpha", m_object_alpha);
}

void ObjectScript1::Proceed_5Scaling() {
    m_elapsed_time += opgs16::manager::MTimeManager::Instance().GetDeltaTime();
    m_object_scale_offset = (std::sinf(m_2pi * m_elapsed_time) / 2) + 0.5f;

    GetObject().SetScaleValue(m_object_original_scale * m_object_scale_offset);
}

void ObjectScript1::OnTriggerSwap() {
    using opgs16::component::CSprite2DRenderer;
    CSprite2DRenderer* renderer = GetObject().GetComponent<CSprite2DRenderer>();
    const auto index = renderer->TextureIndex();
    auto value = index + 1;
    if (value > 15)
        value = 0;

    renderer->SetTextureIndex(value);
}