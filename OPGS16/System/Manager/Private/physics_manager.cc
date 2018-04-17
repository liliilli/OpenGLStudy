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

/*!
 * @file System/Manager/Private/physics_manager.cc
 * @brief
 *
 * @author Jongmin Yun
 * @log
 * 2018-03-04 Refactoring.
 */

#include "../Public/physics_manager.h"  /*! Header file */

#include <algorithm>                    /*! std::sort */

#include "../../Components/Public/rigidbody_2d.h"        /*! opgs16::component::CRigidbody2D */
#include "../../Components/Physics2D/Collider/rectangle.h"  /*! collision::RectangleCollider2D */
#include "../Public/setting_manager.h"      /*! ::opgs16::manager::MSettingManager */
#include "../../Element/Public/object.h"    /*! ::opgs16::element::CObject */

#include "../../Core/Public/logger.h"
#include "../../Core/Internal/logger_internal.h"

namespace opgs16 {
namespace manager {
namespace {
struct MovementOffset { int x{ 0 }, y{ 0 }; };

/*! Check AABB Collision detection */
bool DetectCollisionAabbExt(const collision::RectangleCollider2D* s_collider,
                            const collision::RectangleCollider2D* d_collider,
                            const MovementOffset offset = {}) {
    using PositionType = collision::RectangleCollider2D::PositionType;
    auto s_m = s_collider->GetTipPosition(PositionType::LEFT_DOWN);
    s_m.x += offset.x;
    s_m.y += offset.y;

    auto s_M = s_collider->GetTipPosition(PositionType::RIGHT_UP);
    s_M.x += offset.x;
    s_M.y += offset.y;

    const auto d_m = d_collider->GetTipPosition(PositionType::LEFT_DOWN);
    const auto d_M = d_collider->GetTipPosition(PositionType::RIGHT_UP);
    return s_M.x >= d_m.x && d_M.x >= s_m.x && s_M.y >= d_m.y && d_M.y >= s_m.y;
}

/*! Collision flag structure */
struct CollisionFlag {
    bool x{ false };
    bool y_top{ false };
    bool y_bottom{ false };
};


void AdjustPosition(component::CRigidbody2D* src_rgd2d,
                    collision::RectangleCollider2D* src_col2d,
                    collision::RectangleCollider2D* dst_col2d) {
    CollisionFlag   collision_flag;
    const auto&     original_movement = src_rgd2d->Movement();
    MovementOffset  final_offset;

    for (auto dir = 0u; dir < 4u; ++dir) { /*! Dir :: top = 0, bottom = 1, left = 2, right = 3 */
        MovementOffset  movement_offset;
        switch (dir) {
        case 0: if (original_movement.y < 0) continue; break; case 1: if (original_movement.y > 0) continue; break;;
        case 2: if (original_movement.x < 0) continue; break; case 3: if (original_movement.x > 0) continue; break;;
        default: break;
        }

        while (DetectCollisionAabbExt(src_col2d, dst_col2d, movement_offset)) {
            switch (dir) {
            case 0: --movement_offset.y; break; case 1: ++movement_offset.y; break;
            case 2: --movement_offset.x; break; case 3: ++movement_offset.x; break;
            default: break;
            }
        }

        switch (dir) {
        case 0: case 1: final_offset.y = movement_offset.y; break;
        case 2: case 3: final_offset.x = movement_offset.x; break;
        default: break;
        }
    }

    if (original_movement.y > 0 && final_offset.y < 0) collision_flag.y_top = true;
    if (original_movement.y < 0 && final_offset.y > 0) collision_flag.y_bottom = true;
    if (abs(final_offset.x) >= 1) collision_flag.x = true;

    {
        auto& src_velocity = src_rgd2d->Velocity();
        if (collision_flag.x && src_velocity.y > 0) src_velocity.y = 0;
        if (collision_flag.x || collision_flag.y_top || collision_flag.y_bottom) {
            auto& position = const_cast<glm::vec3&>(src_rgd2d->GetObject().GetWorldPosition());
            position += glm::vec3{final_offset.x, final_offset.y, 0};
            position.x = floorf(position.x);
            position.y = floorf(position.y);
            src_col2d->ReflectPosition(position);

            if (collision_flag.y_top || collision_flag.y_bottom) src_velocity.y = 0;
            if (collision_flag.x) src_velocity.x = 0;

            final_offset.x = final_offset.y = 0;
        }
    }
}

} /*! unnamed namespace */

using _internal::Item;

void MPhysicsManager::AddCollider(collision::RectangleCollider2D* const collider,
                                 component::CRigidbody2D* const rigidbody) {
    using Type = collision::RectangleCollider2D::PositionType;
    auto ld = collider->GetTipPosition(Type::LEFT_DOWN);
    auto ru = collider->GetTipPosition(Type::RIGHT_UP);

    /*! Insert to potential list */
    m_potential.emplace_back(
        std::make_unique<Item>(collider, rigidbody, ld, Item::Type::BEGIN));
    m_potential.emplace_back(
        std::make_unique<Item>(collider, rigidbody, ru, Item::Type::END));
}

void MPhysicsManager::Update() {
    /*! Sorting */
    std::sort(m_potential.begin(), m_potential.end(),
              [](const item_ptr& lhs, const item_ptr& rhs) {
        return lhs->m_position.x < rhs->m_position.x;
    });

    /*! Processing */
    for (auto& item : m_potential) {
        switch (item->m_type) {
        case Item::Type::BEGIN:
            ProceedCollisionCheck(item);
            m_active.emplace_back(item.get());
            break;
        case Item::Type::END:
            EraseItem(item);
            break;
        }
    }

    /*! Remove All potential, active list */
    Clear();
}

void MPhysicsManager::Clear() {
    m_active.clear();
    m_potential.clear();
}

void MPhysicsManager::ProceedCollisionCheck(MPhysicsManager::item_ptr& item) {
    const auto& manager = MSettingManager::Instance();

    for (auto& active_item : m_active) {
        /*! If rigidbody is same, do not check collision. */
        auto const s_rigidbody = active_item->m_rigidbody, d_rigidbody = item->m_rigidbody;
        if (s_rigidbody == d_rigidbody) continue;
        auto const s_collider = active_item->m_collider, d_collider = item->m_collider;
        if (!manager.CollisionLayerCheck(s_collider->CollisionLayer(), d_collider->CollisionLayer())) continue;

        if (DetectCollisionAabbExt(s_collider, d_collider)) {
            /*! Check solidification */
            if (d_rigidbody->IsSolid() && !s_rigidbody->IsSolid()) {
                AdjustPosition(s_rigidbody, s_collider, d_collider);
            }
            else if (s_rigidbody->IsSolid() && !d_rigidbody->IsSolid()) {
                AdjustPosition(d_rigidbody, d_collider, s_collider);
            }

            /*! Call callback member function */
            using col_type = collision::Collider2D::ECollisionType;
            if (s_collider->CollisionType() == col_type::COLLISION)
                s_rigidbody->OnCollisionEnter(*d_rigidbody);
            else
                s_rigidbody->OnTriggerEnter(*d_rigidbody);

            if (d_collider->CollisionType() == col_type::COLLISION)
                d_rigidbody->OnCollisionEnter(*s_rigidbody);
            else
                d_rigidbody->OnTriggerEnter(*s_rigidbody);
        }
    }
}

void MPhysicsManager::EraseItem(MPhysicsManager::item_ptr& item) {
    for (auto it = m_active.cbegin(); it != m_active.cend(); ++it) {
        if ((*it)->m_collider == item->m_collider) {
            m_active.erase(it);
            break;
        }
    }
}

} /*! opgs16::manager */
} /*! opgs16 */