#ifndef OPGS16_COMPONENT_FONT2D_RENDERER_H
#define OPGS16_COMPONENT_FONT2D_RENDERER_H

///
/// @license BSD 2-Clause License
///
/// Copyright (c) 2018, Jongmin Yun(Neu.), All rights reserved.
/// If you want to read full statements, read LICENSE file.
///
/// @file Component/font2d_renderer.h
///
/// @brief
///
///
/// @author Jongmin Yun
/// @log
/// 2018-05-28 Create file.
///

/// ::opgs16::component::_internal::CRendererBase
#include <Component/Internal/renderer_base.h>
/// ::opgs16::component::_internal enum flags.
#include <Component/Internal/flag.h>
/// ::opgs16::element::IOriginable::Origin
#include <Element/Interface/i_originable.h>
/// ::opgs16::element::IAlignable::Alignment
#include <Element/Interface/i_alignable.h>
/// ::opgs16::manager::font namespace.
#include <Manager/font_manager.h>

/// Component macroes
#include <Component/Internal/component_macro.h>

namespace opgs16::component {

class CFont2DRenderer final : public _internal::CRendererBase {
public:
  CFont2DRenderer(element::CObject& bind_object,
                  const std::string& font_tag,
                  const std::string& shader_tag,
                  const uint32_t rendering_layer = 0);

  ///
  /// @brief The method renders given text on given position with given color.
  ///
  /// This get text rendered with relative position from origin with color by aligning.
  /// If text is multilined, text will be tokenized with '\n' return-carriage character.
  ///
  /// @param[in] text String text to be rendered.
  /// @param[in] origin Origin position from which text strings rendered.
  /// position bound is [0, screen_size], so DOWN_LEFT has position (0, 0) in Screen space.
  /// In contrast UP_RIGHT will be (width, height) in Screen space.
  ///
  /// @param[in] relatve_position Relatve position from origin position string will be rendered.
  /// Final position string rendered is (x, y) = (origin + relative_position + alignment_offset)
  ///
  /// @param[in] color The color to be rendered. R, G, B support.
  /// @param[in] alignment String alignment parameter. default value is LEFT. (left-side)
  /// @param[in] scale Scale factor value to apply it. Default value is 1.0f. (not-change)
  ///
  /// @see https://www.freetype.org/freetype2/docs/tutorial/step2.html
  ///
  void RenderTextNew (const std::string& text,
                      IOriginable::Origin origin,
                      const glm::vec2 final_position,
                      const glm::vec3 color,
                      IAlignable::Alignment alignment,
                      const float scale);

  ///
  /// @brief
  ///
  void SetDefaultFont();

  ///
  /// @brief
  ///
  void SetFont(const std::string& font_name);

private:
  ///
  /// @brief
  /// Refresh m_text_container and m_text_render_width container.
  ///
  /// @param[in] text
  ///
  void RefreshStringContainers(const std::string& text);

  glm::mat4 m_projection = glm::mat4();
  GLuint m_vao = 0;
  GLuint m_vbo = 0;

  element::CShaderWrapper m_wrapper;
  manager::font::font_raw	m_font_set = nullptr;

  /// Shader is in ShaderManager, render sprite.
  std::vector<std::string> m_text_container;
  /// Default scale is 1.0.
  std::vector<uint32_t> m_text_render_width;

  _internal::EStringCacheFlag m_dirty = _internal::EStringCacheFlag::Dirty;

SET_UP_TYPE_MEMBER(::opgs16::component::_internal::CRendererBase, CFont2DRenderer)
};

} /// ::opgs16::component namespace

#endif /// OPGS16_COMPONENT_FONT2D_RENDERER_H