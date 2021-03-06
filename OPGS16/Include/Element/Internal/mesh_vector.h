#ifndef OPGS16_ELEMENT_INTERNAL_MESH_VECTOR_H
#define OPGS16_ELEMENT_INTERNAL_MESH_VECTOR_H

///
/// @license BSD 2-Clause License
///
/// Copyright (c) 2018, Jongmin Yun(Neu.), All rights reserved.
/// If you want to read full statements, read LICENSE file.
///
/// @file Manager/Internal/mesh_vector.h
///
/// @brief
/// Internal VAO mesh vertex structure file.
///
/// @author Jongmin Yun
///
/// @log
/// 2018-06-11 Create file.
///

#include <utility>

#include <Phitos/Enums/activated.h>

#include <Helper/include_vector.h>

namespace opgs16::element {

///
/// @class DMeshVector
///
/// @brief
///
///
class DMeshVector final {
public:
  DMeshVector() noexcept {};

  ///
  /// @param[in] position
  /// @param[in] normal
  /// @param[in] tangent
  /// @param[in] texture_coord
  ///
  DMeshVector(const DVector3& position,
              const DVector3& normal,
              const DVector3& tangent,
              const DVector2& texture_coord) noexcept;

private:
  DVector3 m_position = {};
  DVector3 m_normal = {};
  DVector3 m_tangent = {};
  DVector2 m_texture_coord = {};
};

} /// ::opgs16::element namespace

#endif /// OPGS16_ELEMENT_INTERNAL_MESH_VECTOR_H