#ifndef OPGS16_HELPER_VECTOR_H
#define OPGS16_HELPER_VECTOR_H

///
/// @license BSD 2-Clause License
///
/// Copyright (c) 2018, Jongmin Yun(Neu.), All rights reserved.
/// If you want to read full statements, read LICENSE file.
///
/// @file Helper/vector.h
///
/// @brief
/// Introduce opgs16 dependent vector series classes.
///
/// @author Jongmin Yun
///
/// @log
/// 2018-06-30 Implement file.
///

#include <array>

/// External libraries which have dependency on DVector series.
///
#include <assimp/vector2.h>
#include <assimp/vector3.h>
#include <glm/glm.hpp>
#include <LinearMath/btVector3.h>

#include <Phitos/Dbg/assert.h>

#include <Headers/import_logger.h>

namespace opgs16 {

///
/// @struct DVector2
/// @brief Float type 2-element vector struct.
///
struct DVector2 {
  float x = 0.f;
  float y = 0.f;

  DVector2() = default;
  ~DVector2() = default;

  DVector2(const float x, const float y) noexcept :
      x{x}, y{y} {};

  explicit DVector2(const float value) noexcept :
      x{value}, y{value} { }

  DVector2(const DVector2&) = default;
  DVector2& operator=(const DVector2& value) = default;

  DVector2(DVector2&&) = default;
  DVector2& operator=(DVector2&&) = default;

  //!
  //! Constructor and assign operator for dependencies.
  //!

  explicit DVector2(const aiVector2D& value) noexcept :
      x{value.x}, y{value.y} {};

  DVector2& operator=(const aiVector2D& value) noexcept {
    x = value.x;
    y = value.y;
    return *this;
  }

  explicit DVector2(const glm::vec2& value) noexcept :
      x{value.x}, y{value.y} {};

  DVector2& operator=(const glm::vec2& value) noexcept {
    x = value.x;
    y = value.y;
    return *this;
  }

  //!
  //! Conversion operators for dependencies.
  //!

  explicit operator btVector3() const noexcept {
    return btVector3{x, y, 0.f};
  }

  //!
  //! Methods
  //!

  ///
  /// @brief Returns the length of this vector.
  /// @return Length of this DVector2.
  ///
  float GetLength() const noexcept {
    return std::sqrtf(x * x + y * y);
  }

  ///
  /// @brief Return squared length of this vector.
  /// @return Squared length of this DVector2.
  ///
  float GetSquareLength() const noexcept {
    return x * x + y * y;
  }

  ///
  /// @brief Return new DVector2 instance of normalized input vector.
  /// @return Normalized DVector2 vector.
  ///
  DVector2 Normalize() const noexcept {
    const auto length = this->GetLength();
    return {x / length, y / length};
  }

  //!
  //! Operators
  //!

  friend DVector2 operator+(DVector2 lhs, const DVector2& rhs) noexcept {
    lhs.x += rhs.x;
    lhs.y += rhs.y;
    return lhs;
  }

  friend DVector2 operator-(DVector2 lhs, const DVector2& rhs) noexcept {
    lhs.x -= rhs.x;
    lhs.y -= rhs.y;
    return lhs;
  }

  ///
  /// DVector2 $$ v = (x, y) $$ and value $$ a $$
  /// $$ av $$.
  ///
  friend DVector2 operator*(DVector2 lhs, const float rhs) noexcept {
    lhs.x *= rhs;
    lhs.y *= rhs;
    return lhs;
  }

  ///
  /// If lhs and rhs are DVector2, element multiplication happens.
  ///
  friend DVector2 operator*(DVector2 lhs, const DVector2& rhs) noexcept {
    lhs.x *= rhs.x;
    lhs.y *= rhs.y;
    return lhs;
  }

  friend DVector2 operator/(DVector2 lhs, const float rhs) noexcept {
    if (rhs == 0.0f) {
      PUSH_LOG_CRITICAL_EXT("DVector2 could not be divided by {0}.", rhs);
    }
    else {
      lhs.x /= rhs;
      lhs.y /= rhs;
    }

    return lhs;
  }

  friend DVector2 operator/(DVector2 lhs, const DVector2& rhs) noexcept {
    if (rhs.x == 0.0f || rhs.y == 0.0f) {
      PUSH_LOG_CRITICAL_EXT(
          "DVector2 could not be devided by 0 included DVector2, ({0}, {1})",
          rhs.x, rhs.y);
    }
    else {
      lhs.x /= rhs.x;
      lhs.y /= rhs.y;
    }

    return lhs;
  }

  DVector2& operator+=(const DVector2& value) noexcept {
    this->x += value.x;
    this->y += value.y;
    return *this;
  }

  DVector2& operator-=(const DVector2& value) noexcept {
    this->x -= value.x;
    this->y -= value.y;
    return *this;
  }

  DVector2& operator*=(const float value) noexcept {
    this->x *= value;
    this->y *= value;
    return *this;
  }

  DVector2& operator*=(const DVector2& value) noexcept {
    this->x *= value.x;
    this->y *= value.y;
    return *this;
  }

  DVector2& operator/=(const float value) noexcept {
    if (value == 0.0f) {
      PUSH_LOG_CRITICAL_EXT("DVector2 could not be divided by {0}.", value);
    }
    else {
      this->x /= value;
      this->y /= value;
    }

    return *this;
  }

  DVector2& operator/=(const DVector2& value) noexcept {
    if (value.x == 0.0f || value.y == 0.0f) {
      PUSH_LOG_CRITICAL_EXT(
          "DVector2 could not be devided by 0 included DVector2, ({0}, {1})",
          value.x, value.y);
    }
    else {
      this->x /= value.x;
      this->y /= value.y;
    }

    return *this;
  }

  friend bool operator<(const DVector2& lhs, const DVector2& rhs) noexcept {
    return lhs.GetSquareLength() < rhs.GetSquareLength();
  }

  friend bool operator>(const DVector2& lhs, const DVector2& rhs) noexcept {
    return rhs < lhs;
  }

  friend bool operator<=(const DVector2& lhs, const DVector2& rhs) noexcept {
    return !(rhs < lhs);
  }

  friend bool operator>=(const DVector2& lhs, const DVector2& rhs) noexcept {
    return !(lhs < rhs);
  }

  friend bool operator==(const DVector2& lhs, const DVector2& rhs) noexcept {
    PHITOS_NOT_IMPLEMENTED_ASSERT();
  }

  //!
  //! Static functions
  //!

  ///
  /// @brief
  ///
  static float Dot(const DVector2& lhs, const DVector2& rhs) noexcept {
    return lhs.x * rhs.x + lhs.y * rhs.y;
  }

  ///
  /// @brief
  /// @param[in]
  ///
  static DVector2 Lerp(const DVector2& lhs, const DVector2& rhs, float value) noexcept {
    return lhs * (1.0f - value) + rhs * value;
  }

  static DVector2 CompMaxLength(const DVector2& lhs, const DVector2& rhs) noexcept {
    return (lhs >= rhs) ? lhs : rhs;
  }

  static DVector2 CompMinLength(const DVector2& lhs, const DVector2& rhs) noexcept {
    return (lhs < rhs) ? lhs : rhs;
  }
};

///
/// @struct DVector3
///
/// @brief
/// Helper vector class.
///
struct DVector3 {
  float x = 0.f;
  float y = 0.f;
  float z = 0.f;

  DVector3() noexcept {};

  DVector3(float x, float y, float z) noexcept : x(x), y(y), z(z) {};

  DVector3(const aiVector3D& value) noexcept :
      x{value.x}, y{value.y}, z{value.z} {}

  ///
  /// @brief
  /// Return sequence data of this instance.
  ///
  std::array<float, 3> Data() const noexcept {
    return {x, y, z};
  }

  DVector3& operator=(const aiVector3D& value) noexcept {
    x = value.x;
    y = value.y;
    z = value.z;

    return *this;
  }

  operator btVector3() const noexcept {
    return btVector3(x, y, z);
  }
};

}

#endif /// OPGS16_HELPER_VECTOR_H