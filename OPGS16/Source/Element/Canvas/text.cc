
///
/// @license BSD 2-Clause License
///
/// Copyright (c) 2018, Jongmin Yun(Neu.), All rights reserved.
/// If you want to read full statements, read LICENSE file.
///
/// @file Element/Canvas/text.cc
///
/// @brief
/// Definition file of ::opgs16::element::canvas::CText.
///
/// @author Jongmin Yun
/// @log
/// 2018-03-15 Unknown.
/// 2018-04-17 Move definition function body into ::opgs16::element::canvas namespace.
/// 2018-05-28 Remove pointer to implementation idiom.
///

#include <Element/Canvas/text.h>    /// Header file

/// ::opgs16::component::CFont2DRenderer
#include <Component/font2d_renderer.h>
/// ::opgs16::manager::MFontManager
#include <Manager/font_manager.h>

/// import logger in debug mode
#include <Headers/import_logger.h>

namespace opgs16::element::canvas {

using CTextImpl = _internal::CTextImpl;

CText::CText(const std::string& initial_text,
             const glm::vec3& position,
             const DColor& color) :
    m_text{initial_text}, m_color{color} {
  SetWorldPosition(position);

  auto renderer =
      AddComponent<component::CFont2DRenderer>(*this, u8"", u8"gCommonFont", 0);
  renderer->SetText(m_text);
  renderer->SetColor(color);
}

void CText::Render() {
  auto renderer = GetComponent<component::CFont2DRenderer>();

  // Set font
  auto font_name = GetFontName();
  if (font_name.empty())
    renderer->SetDefaultFont();
  else
    renderer->SetFont(font_name);

  // Render
  renderer->SetText(GetText());
  renderer->SetColor(GetColor());
  renderer->RenderText(
      GetOrigin(),
      glm::vec2{ GetFinalPosition() },
      GetAlignment(),
      GetScaleValue());
}

void CText::SetText(const std::string& new_text) {
  m_text = new_text;
}

const std::string& CText::GetText() const {
  return m_text;
}

void CText::SetFontSize(const uint32_t size) {
  const unsigned def = manager::font::GetDefaultFontSize();
  SetScaleValue(static_cast<float>(size) / static_cast<float>(def));
}

const unsigned CText::GetFontSize() const {
  return m_font_size;
}

bool CText::SetFontName(const std::string& font_tag) {
	if (!manager::font::IsFontExist(font_tag)) {
    PUSH_LOG_ERROR_EXT("Font did not find. : [Font : {0}]", font_tag);
    m_font_name = "";
    return false;
	}

  m_font_name = font_tag;
  return true;
}

const std::string& CText::GetFontName() {
  return m_font_name;
}

void CText::SetColor(const DColor& color) {
  m_color = color;
}

const DColor& CText::GetColor() {
  return m_color;
}

} /// ::opgs16::element::canvas
