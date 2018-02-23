#include "test_script_1.h"            /*! Header file */

#include <glm\glm.hpp>
#include "..\..\..\GlobalObjects\Canvas\text.h"     /*! Canvas::Text */
#include "..\..\..\System\Manager\scene_manager.h"  /*! SceneManager */
#include "..\..\..\System\Manager\timer_manager.h"  /*! TimerManager */

#include "obj_script_1.h"   /*! ObjectScript1 for TestObject1 */

TestScript1::TestScript1(Object& obj) : component::ScriptFrame{ obj } {
    Initiate();
    Start();
}

void TestScript1::Start() {
    SetTimer();
}

void TestScript1::Update() {
    if (!m_is_break) {
        switch (m_sequence) {
        default: /*! Do nothing */ break;
        case Sequence::_1_NORMAL_LOCAL:
            Proceed_1NormalLocal();
            break;
        case Sequence::_2_DEPENDENT_WORLD:
            Proceed_2DependentWorld();
            break;
        case Sequence::_3_INDEPENDENT_WORLD:
            //SetTimer(m_timer_third_test, 500, true, this, &TestScript1::ToggleObjectProperties);
            //Proceed_3WorldPosition();
            break;
        }
    }
    else {
        if (m_finished_obj == 4) {
            m_finished_obj = 0;
            SetTimer();
        }
    }
}

void TestScript1::Proceed_1NormalLocal() {
    auto scene = SceneManager::GetInstance().GetPresentScene();
    if (scene) {
        /*! Get objects */
        std::vector<Object*> obj_list{ scene->GetObject("Object").get() };
        while (*obj_list.rbegin() != nullptr) {
            auto object = *obj_list.rbegin();
            obj_list.emplace_back(object->GetChild("Object"));
        }
        obj_list.erase(--obj_list.cend());

        /*! Propagate them to do work */
        auto obj_number = 0;
        for (auto& obj_raw : obj_list) {
            ObjectScript1* script = obj_raw->GetComponent<ObjectScript1>();
            script->DoWork(1, obj_number);
            ++obj_number;
        }
    }

    m_is_break = true;
}

void TestScript1::Proceed_2DependentWorld() {
    auto scene = SceneManager::GetInstance().GetPresentScene();
    auto speed = 2.0f;

    if (scene) {
        auto& object = scene->GetObject("Object");
        auto pos = object->GetWorldPosition();
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
                ++m_switch;
                SetTimer();
            }
        }

        object->SetWorldPosition(pos);
    }
}

void TestScript1::Proceed_3WorldPosition() {
    auto scene = SceneManager::GetInstance().GetPresentScene();
    auto speed = 2.0f;

    if (scene) {
        auto& object = scene->GetObject("Object");
        auto pos = object->GetWorldPosition();
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
                ++m_switch;
                SetTimer();

            }
        }

        object->SetWorldPosition(pos);
    }
}

void TestScript1::ToggleObjectProperties() {

}

void TestScript1::SetTimer() {
    TimerManager::GetInstance().SetTimer(m_timer_break, 1'500, false, this, &TestScript1::Resume);
}

void TestScript1::Resume() {
    m_is_break  = false;
    m_switch    = 0;
    m_sequence  = static_cast<Sequence>(static_cast<size_t>(m_sequence) + 1);

    ObjectPropertiesReset();
    ChangeText();
}

void TestScript1::ObjectPropertiesReset() {
    /*! Reset all things */
    switch (m_sequence) {
    case Sequence::_3_INDEPENDENT_WORLD: {
        auto scene = SceneManager::GetInstance().GetPresentScene();

        bool translate_dependency = true;
        auto object = scene->GetObject("Object").get();
        while (object != nullptr) {
            object->SetSucceedingPositionFlag(translate_dependency);
            /*! Set translate succeeding flag */
            object = object->GetChild("Object");
            translate_dependency = !translate_dependency;
        }
    }   break;
    default: /*! Do nothing */ break;
    }
}

void TestScript1::ChangeText() {
    /*! Text statements change */
    auto text = static_cast<::Canvas::Text*>(GetObject().GetChild("Text"));
    switch (m_sequence) {
    case Sequence::_1_NORMAL_LOCAL:
        text->SetText(u8"Look for local translation of\ncenter boxes.");
        break;
    case Sequence::_2_DEPENDENT_WORLD:
        text->SetText(u8"Look for world translation of\nblue box and its children.");
        break;
    case Sequence::_3_INDEPENDENT_WORLD:
        text->SetText(u8"Look for wierd but intentional\nworld translation of center boxes.");
        break;
    default: /*! Do nothing */ break;
    }
}
