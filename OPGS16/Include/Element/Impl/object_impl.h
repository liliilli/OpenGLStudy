#ifndef OPGS16_SYSTEM_OBJECT_OBJECT_PRIVATE_IMPLEMENTATION_H
#define OPGS16_SYSTEM_OBJECT_OBJECT_PRIVATE_IMPLEMENTATION_H

///
/// @license BSD 2-Clause License
///
/// Copyright (c) 2018, Jongmin Yun(Neu.), All rights reserved.
/// If you want to read full statements, read LICENSE file.
///
/// @file Element/Impl/object_impl.h
///
/// @brief Pointer to implementation file of Object.h
///
/// @author Jongmin Yun
///
/// @log
/// 2018-02-19 Refactoring, Inlining, and Removed not-used variables. add class description.
/// 2018-02-19 Add GetParentPosition() method, returns m_parent_to_position.
/// 2018-02-23 Add succeeding flag of translation, rotation, scaling from parent.
/// 2018-03-05 Add rendering layer member functions.
/// 2018-03-11 Moved implementation contents into ::opgs16::element::_internal.
/// 2018-04-14 Change CObjectImpl::SetRotationLocalAngle angle reflection mechanism, restrict bound as (-180.f, 180.f].
/// 2018-04-18 Change function and mechanism of rotation.
/// 2018-07-02 Refactoring.
/// 2018-07-31 Add AddOffset... series function.
///

#include <string>

#include <glm/glm.hpp>
#include <Phitos/Enums/activated.h>

/// ::opgs16::element::EAxis3D
#include <Helper/Math/math.h>
#include <Helper/Type/axis.h>
#include <Helper/Type/vector3.h>

namespace opgs16::element::_internal {
///
/// @class CObjectImpl
/// @brief Pointer to implementation of class Object.
///
class CObjectImpl final {
public:
  //!
  //! Position
  //!

  inline const DVector3& GetLocalPosition() const {
    return m_local_position;
  }

  inline const DVector3& GetWorldPosition() const {
    return m_world_position;
  }

  inline const DVector3& GetParentPosition() const {
    return m_parent_to_position;
  }

  inline const DVector3& GetFinalPosition() const {
    if (m_offset_model_matrix_deprecated) {
      RefreshWpRotationMatrix();
      m_offset_model_matrix_deprecated = false;
    }

    if (m_final_pos_deprecated) {
      RefreshFinalPosition();
      m_final_pos_deprecated = false;
    }

    return m_final_position;
  }

  inline void SetLocalPosition(const DVector3& position) noexcept {
    m_local_position = position;
    m_local_model_matrix_deprecated = true;
    m_final_pos_deprecated = true;
  }

  inline void SetWorldPosition(const DVector3& position) noexcept {
    m_world_position = position;
    m_parent_to_position = m_parent_from_position + m_world_position;

    m_local_model_matrix_deprecated = true;
    m_final_pos_deprecated = true;
  }

  inline void SetWorldPosWithFinalPos(const DVector3& final_position) noexcept {
    SetWorldPosition(final_position - m_parent_from_position);
  }

  inline void SetParentPosition(const DVector3& parent_position) noexcept {
    m_parent_from_position = parent_position;
    m_parent_to_position = parent_position + m_world_position;

    m_local_model_matrix_deprecated = true;
    m_final_pos_deprecated = true;
  }

  ///
  /// @brief Add offset value with axis as local position.
  ///
  void AddOffsetLocalPosition(EAxis3D axis, float value) noexcept {
    switch (axis) {
    case EAxis3D::X: m_local_position.x += value; break;
    case EAxis3D::Y: m_local_position.y += value; break;
    case EAxis3D::Z: m_local_position.z += value; break;
    }
    m_local_model_matrix_deprecated = true;
    m_final_pos_deprecated = true;
  }

  ///
  /// @brief Add offset value with axis as world position.
  ///
  void AddOffsetWorldPosition(EAxis3D axis, float value) noexcept {
    switch (axis) {
    case EAxis3D::X: m_world_position.x += value; break;
    case EAxis3D::Y: m_world_position.y += value; break;
    case EAxis3D::Z: m_world_position.z += value; break;
    }
    m_parent_to_position = m_parent_from_position + m_world_position;
    m_local_model_matrix_deprecated = true;
    m_final_pos_deprecated = true;
  }

  //!
  //! Angle
  //!

  float GetRotationLocalAngle(const EAxis3D direction) const noexcept {
    switch (direction) {
    case EAxis3D::X: return m_rotation_local_angle_n[0];
    case EAxis3D::Y: return m_rotation_local_angle_n[1];
    case EAxis3D::Z: return m_rotation_local_angle_n[2];
    default:
#ifdef _DEBUG
      return std::numeric_limits<float>::signaling_NaN();
#else
      return std::numeric_limits<float>::quiet_NaN();
#endif
    }
  }

  float GetRotationFromParentAngle(const EAxis3D direction) const noexcept {
    switch (direction) {
    case EAxis3D::X: return m_rotation_parent_angle_n[0];
    case EAxis3D::Y: return m_rotation_parent_angle_n[1];
    case EAxis3D::Z: return m_rotation_parent_angle_n[2];
    default:
#ifdef _DEBUG
      return std::numeric_limits<float>::signaling_NaN();
#else
      return std::numeric_limits<float>::quiet_NaN();
#endif
    }
  }

  float GetRotationWorldAngle(const EAxis3D direction) const noexcept {
    switch (direction) {
    case EAxis3D::X: return m_rotation_world_angle_n[0];
    case EAxis3D::Y: return m_rotation_world_angle_n[1];
    case EAxis3D::Z: return m_rotation_world_angle_n[2];
    default:
#ifdef _DEBUG
      return std::numeric_limits<float>::signaling_NaN();
#else
      return std::numeric_limits<float>::quiet_NaN();
#endif
    }
  }

  float GetRotationWpAngle(const EAxis3D direction) const {
    switch (direction) {
    case EAxis3D::X: return m_rotation_wp_angle_n[0];
    case EAxis3D::Y: return m_rotation_wp_angle_n[1];
    case EAxis3D::Z: return m_rotation_wp_angle_n[2];
    default:
#ifdef _DEBUG
      return std::numeric_limits<float>::signaling_NaN();
#else
      return std::numeric_limits<float>::quiet_NaN();
#endif
    }
  }

  void SetRotationLocalAngle(const EAxis3D direction, const float angle_value) noexcept {
    const auto angle = math::GetRotationAngle(angle_value);

    switch (direction) {
    case EAxis3D::X: m_rotation_local_angle_n[0] = angle; break;
    case EAxis3D::Y: m_rotation_local_angle_n[1] = angle; break;
    case EAxis3D::Z: m_rotation_local_angle_n[2] = angle; break;
    default: break;
    }

    m_local_model_matrix_deprecated = true;
    m_local_rotation_deprecated = true;
  }

  void SetRotationWorldAngle(const EAxis3D direction, const float angle_value) noexcept {
    const auto angle = math::GetRotationAngle(angle_value);

    switch (direction) {
    case EAxis3D::X: m_rotation_world_angle_n[0] = angle; break;
    case EAxis3D::Y: m_rotation_world_angle_n[1] = angle; break;
    case EAxis3D::Z: m_rotation_world_angle_n[2] = angle; break;
    default: break;
    }

    RefreshRotationWorldParentAngle(direction);
    m_offset_model_matrix_deprecated = true;
    m_local_model_matrix_deprecated = true;
  }

  void SetRotationParentAngle(const EAxis3D direction, const float angle_value) noexcept {
    const auto angle = math::GetRotationAngle(angle_value);

    switch (direction) {
    case EAxis3D::X: m_rotation_parent_angle_n[0] = angle; break;
    case EAxis3D::Y: m_rotation_parent_angle_n[1] = angle; break;
    case EAxis3D::Z: m_rotation_parent_angle_n[2] = angle; break;
    default: break;
    }

    RefreshRotationWorldParentAngle(direction);
    m_offset_model_matrix_deprecated = true;
    m_local_model_matrix_deprecated = true;
    m_final_pos_deprecated = true;
  }

  void AddOffsetLocalAngle(EAxis3D axis, float value) noexcept {
    switch (axis) {
    case EAxis3D::X:
      m_rotation_local_angle_n[0] = math::GetRotationAngle(m_rotation_local_angle_n[0] + value);
      break;
    case EAxis3D::Y:
      m_rotation_local_angle_n[1] = math::GetRotationAngle(m_rotation_local_angle_n[1] + value);
      break;
    case EAxis3D::Z:
      m_rotation_local_angle_n[2] = math::GetRotationAngle(m_rotation_local_angle_n[2] + value);
      break;
    default: break;
    }

    m_local_model_matrix_deprecated = true;
    m_local_rotation_deprecated = true;
  }

  void AddOffsetWorldAngle(EAxis3D axis, float value) noexcept {
    switch (axis) {
    case EAxis3D::X:
      m_rotation_world_angle_n[0] = math::GetRotationAngle(m_rotation_world_angle_n[0] + value);
      break;
    case EAxis3D::Y:
      m_rotation_world_angle_n[1] = math::GetRotationAngle(m_rotation_world_angle_n[1] + value);
      break;
    case EAxis3D::Z:
      m_rotation_world_angle_n[2] = math::GetRotationAngle(m_rotation_world_angle_n[2] + value);
      break;
    default: break;
    }

    m_offset_model_matrix_deprecated = true;
    m_local_model_matrix_deprecated = true;
  }

  //!
  //! Scale
  //!

  float GetScaleLocalValue() const noexcept {
    return m_scale_local_value;
  }

  const DVector3& GetScaleLocalFactor() const noexcept {
    return m_scale_local_factor;
  }

  inline void SetScaleLocalValue(const float scale_value) noexcept {
    m_scale_local_value = scale_value;

    m_local_model_matrix_deprecated = true;
    m_scale_deprecated = true;
  }

  inline void SetScaleLocalFactor(const DVector3& scale_factor) noexcept {
    m_scale_local_factor = scale_factor;

    m_local_model_matrix_deprecated = true;
    m_scale_deprecated = true;
  }

  inline void SetScaleParentValue(const float scale_value) noexcept {
    m_scale_parent_value = scale_value;
  }

  inline void SetScaleParentFactor(const DVector3& scale_factor) noexcept {
    m_scale_parent_factor = scale_factor;
  }

  //!
  //! Matrix
  //!

  const glm::mat4& GetModelMatrix() const;

  //!
  //! Flag inline methods
  //!

  inline void SetSucceedingPositionFlag(bool value) noexcept {
    m_position_succeedable = value;
  }

  inline void SetSucceedingRotationFlag(bool value) noexcept {
    m_rotation_succeedable = value;
  }

  inline void SetSucceedingScalingFlag(bool value) noexcept {
    m_scaling_succeedable = value;
  }

  inline bool GetSucceedingPositionFlag() const noexcept {
    return m_position_succeedable;
  }

  inline bool GetSucceedingRotationFlag() const noexcept {
    return m_rotation_succeedable;
  }

  inline bool GetSucceedingScalingFlag() const noexcept {
    return m_scaling_succeedable;
  }

  ///
  /// @brief Set active option of object.
  /// If m_active is false, this object cannot update until m_active return to true.
  /// @param[in] value Active option value.
  ///
  inline void SetActive(const bool value) {
    m_is_object_activated = value ? EActivated::Activated : EActivated::Disabled;
  }

  inline phitos::enums::EActivated IsActive() const {
    return m_is_object_activated;
  }

  inline void CalculateActivation() noexcept {
    const auto previous = m_is_finally_activated;

    if (m_is_any_parent_activated == EActivated::Disabled ||
        m_is_object_activated == EActivated::Disabled) {
      m_is_finally_activated = EActivated::Disabled;
    }
    else {
      m_is_finally_activated = EActivated::Activated;
    }

    if (previous != m_is_finally_activated) {
      m_is_callback_called = false;
    }
  }

  inline void PropagateActivation(const phitos::enums::EActivated value) {
    m_is_any_parent_activated = value;
  }

  inline phitos::enums::EActivated IsAnyParentActivated() const noexcept {
    return m_is_any_parent_activated;
  }

  inline phitos::enums::EActivated IsFinallyActivated() const {
    return m_is_finally_activated;
  }

  inline bool IsCallbackNotCalled() const noexcept {
    return !m_is_callback_called;
  }

  inline void SetCallbackFlagToFalse() noexcept {
    m_is_callback_called = true;
  }

  ///
  /// @brief Set tag with tag name. This method will check whether or not exist matched tag name
  /// in SettingManager. If not exist, do nothing and chagne error flag.
  /// @param[in] tag_name Tag name
  ///
  void SetTag(const std::string& tag_name);

  /*! Overloading version of SetTag(tag_name) */
  void SetTag(const unsigned tag_index);

  /*! Return tag index value of this object. */
  inline unsigned GetTagIndexOf() const noexcept {
    return m_tag_index;
  }

  ///
  /// @brief Get Tag Name of this object. (different with name of object)
  /// This methods return tag name by referencing SettingManager in body.
  /// @return Tag name string.
  ///
  std::string GetTagNameOf() const;

private:
  /// (x, y, z) local position.
  DVector3 m_local_position{};
  /// (x, y, z) world position.
  DVector3 m_world_position{};
  /// (x, y, z) final position of parent.
  DVector3 m_parent_from_position{};
  /// (x, y, z) parent position to bring child.
  mutable DVector3 m_parent_to_position{};
  /// (x, y, z) final position in hierarchy.
  mutable DVector3 m_final_position{};

  float       m_rotation_local_angle_n[3]{ 0.f, };
  float       m_rotation_world_angle_n[3]{ 0.f, };
  float       m_rotation_parent_angle_n[3]{ 0.f, };
  float       m_rotation_wp_angle_n[3]{ 0.f, };

  /// Scale value's default value is 1.0f
  float       m_scale_local_value{ 1.f };
  /// Scale value from parent
  float       m_scale_parent_value{ 1.f };
  /// Scale local factor, default is (1, 1, 1)
  DVector3 m_scale_local_factor = DVector3{ 1.f };
  /// Scale factor from parent.
  DVector3 m_scale_parent_factor = DVector3{ 1.f };
  /// (x, y, z) scale vector to apply to matrix.
  mutable DVector3 m_scale_final_vector{};

  /// Local rotation matrix.
  mutable glm::mat4 m_local_rotate_matrix{};
  /// World + Parent rotation matrix.
  mutable glm::mat4 m_wp_rotate_matrix{};
  /// Final model matrix also reflected by parent's and world rot.
  mutable glm::mat4 m_final_model{};

  using EActivated = phitos::enums::EActivated;
  /// Object all update activation variable.
  EActivated m_is_object_activated      = EActivated::Activated;
  EActivated m_is_any_parent_activated  = EActivated::Activated;
  /// Any parent all update activation variable.
  EActivated m_is_finally_activated     = EActivated::Activated;
  bool m_is_callback_called = false;

  /// Flag for succeeding parent position.
  bool m_position_succeedable{ true };
  /// Flag for succeeding parent rotation information.
  bool m_rotation_succeedable{ true };
  /// Flag for succeeding parent scaling information.
  bool m_scaling_succeedable{ true };

  /// The flag model needs to be updated.
  mutable bool m_local_model_matrix_deprecated{ true };
  /// The flag model needs to be updated.
  mutable bool m_offset_model_matrix_deprecated{ true };

  mutable bool m_final_pos_deprecated{ true };        /*! The flag final pos needs to be updated. */
  mutable bool m_local_rotation_deprecated{ true };   /*! The flag rotation needs to be updated. */
  mutable bool m_scale_deprecated{ true };            /*! The flag scale vec needs to be updated. */

  unsigned m_tag_index{ 0 };                /*! Tag index */

private:
  void RefreshFinalPosition() const;	/** Refresh Translation matrix */
  void RefreshRotateMatrix() const;	/** Refresh Rotation matrix */
  void RefreshScaleVector() const;	/** Refresh Scaling matrix */
  void RefreshWpRotationMatrix() const;

  void RefreshRotationWorldParentAngle(const EAxis3D direction);
};

} /// ::opgs16::element::_internal namespace

#endif /** OPGS16_SYSTEM_OBJECT_OBJECT_PRIVATE_IMPLEMENTATION_H */