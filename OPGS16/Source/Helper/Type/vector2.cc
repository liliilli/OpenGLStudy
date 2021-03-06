#include <precompiled.h>
///
/// @license BSD 2-Clause License
///
/// Copyright (c) 2018, Jongmin Yun(Neu.), All rights reserved.
/// If you want to read full statements, read LICENSE file.
///
/// @file Helper/Type/vector2.cc
///
/// @brief
/// Introduce opgs16 dependent vector series classes.
///
/// @author Jongmin Yun
///
/// @log
/// 2018-07-31 Create file.
///

/// Header file
#include <Helper/Type/vector2.h>
#include <Helper/Math/math.h>

namespace opgs16 {

bool DVector2::IsAllZero(const opgs16::DVector2& vector) noexcept {
  return opgs16::math::IsAllZero(vector);
}

bool DVector2::IsAllZero() const noexcept {
  return opgs16::math::IsAllZero(*this);
}

} /// ::opgs16 namespace