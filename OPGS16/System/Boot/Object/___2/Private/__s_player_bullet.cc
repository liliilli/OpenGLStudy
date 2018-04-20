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
 * @file System/Boot/Object/___2/Private/__s_player_bullet.cc
 * @brief Definition and Implementation file of ../Public/__s_player_bullet.h
 * @log
 * 2018-04-15 Create file.
 * 2018-04-19 Change mechanism to bind it with __S_OBJECT_AXIS object.
 *----*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*/

#include "../Public/__s_player_bullet.h"    /*! ::opgs16::builtin::sample::__S_PLAYER_BULLET */
#include "../../../../Manager/Public/scene_manager.h"       /*! ::opgs16::manager::SceneManager */
#include "../../../../Components/Public/camera.h"           /*! ::opgs16::component::Camera */
#include "../../../../Components/Public/sprite_renderer.h"  /*! ::opgs16::component::CSprite2DRenderer */
#include "../../../../Shader/shader_wrapper.h"
#include "../../../Scripts/___2/Public/__s_script_player_bullet.h"
#include "../Interface/constants.h"

namespace opgs16 {
namespace builtin {
namespace sample {

__S_PLAYER_BULLET::__S_PLAYER_BULLET(CObject* parent,
                                     float init_x, float init_y, float init_z,
                                     float init_angle) : m_parent{ *parent }, m_angle{ init_angle } {
    // Init setting.
    SetScaleValue(16.f);
    SetWorldPosition({ init_x, init_y, init_z });

    // Add components.
    renderer = AddComponent<component::CSprite2DRenderer>(*this, "System", "gQuad");
    renderer->SetTextureIndex(15);

    AddComponent<__S_SCRIPT_PLAYER_BULLET>(*this);
}

void __S_PLAYER_BULLET::Render() {
    if (!m_flag) { // Check world angle setting flag.
        m_parent.SetRotationWorldAngle(element::_internal::EDirection::Z, m_angle);
        m_flag = true;
    }

    if (renderer) {
        using manager::MSceneManager;
        using component::CSprite2DRenderer;

        const float angle = m_parent.GetRotationWorldAngle(element::_internal::EDirection::Z) * k_pi180;
        const float end_z = (GetFinalPosition().z - k_end) / k_z_length;
        const float x = (std::sinf(angle) * k_circle_radius) * end_z;
        const float y = (std::cosf(angle) * -k_circle_radius) * end_z;

        auto model_matrix = GetModelMatrix();
        model_matrix[0] *= end_z;
        model_matrix[1] *= end_z;
        model_matrix[2] *= end_z;
        model_matrix[3][0] = k_center_pos[0] + x;
        model_matrix[3][1] = k_center_pos[1] + y;

        const auto pvm = MSceneManager::Instance().PresentScene()->GetMainCamera()->PvMatrix() * model_matrix;
        renderer->Wrapper().SetUniformValue<glm::mat4>("projection", pvm);
        renderer->RenderSprite();
    }
}

} /*! opgs16::builtin::sample */
} /*! opgs16::builtin */
} /*! ogps16 */
