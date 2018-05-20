/*!---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*
 * @license BSD 2-Clause License
 *
 * Copyright (c) 2018, Jongmin Yun(Neu.), All rights reserved.
 * If you want to read full statements, read LICENSE file.
 *----*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*/

/*!---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*
 * @file System/Boot/Scripts/___2/Private/__s_script_player_bullet.cc
 * @brief Definition file of ../Public/__s_script_player_bullet.h
 * @log
 * 2018-04-15 Create file.
 *----*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*/

#include "../Public/__s_script_player_bullet.h"         /*! Header file */
#include "../../../../Element/Public/object.h"          /*! ::opgs16::element::CObject */
#include "../../../../Manager/Public/object_manager.h"  /*! ::opgs16::manager::MObjectManager */
#include "../../../Object/___2/Public/__s_player_bullet.h"
#include "../../../Object/___2/Interface/constants.h"

namespace opgs16 {
namespace builtin {
namespace sample {

__S_SCRIPT_PLAYER_BULLET::__S_SCRIPT_PLAYER_BULLET(element::CObject& bind_object) : CScriptFrame{ bind_object } {
    Start();

};

void __S_SCRIPT_PLAYER_BULLET::Start() {};

void __S_SCRIPT_PLAYER_BULLET::Update() {
    auto pos = GetObject().GetWorldPosition();
    pos.z -= k_bullet_speed;

    if (pos.z <= -100)
        manager::MObjectManager::Instance().Destroy(*static_cast<__S_PLAYER_BULLET*>(&GetObject())->GetParent());
    else
        GetObject().SetWorldPosition(pos);
};

} /*! opgs16::builtin::sample */
} /*! opgs16::builtin */
} /*! opgs16 */