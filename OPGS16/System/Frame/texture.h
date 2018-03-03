#ifndef OPGS16_SYSTEM_FRAME_TEXTURE_H
#define OPGS16_SYSTEM_FRAME_TEXTURE_H

/*!
 * @file System\Frame\m_texture.h
 * @author Jongmin Yun
 * @date 2018-02-28
 *
 * @log
 * 2018-02-23   m_texture::Texture2D Refactoring
 * 2018-02-28   Add GetTextureWidth, GetTextureHeight inline functions.
 */

#include <string>       /*! std::string */
#include <vector>       /*! std::vector */
#include <GL/glew.h>    /*! GL specific types */
#include "..\..\Headers\Fwd\objectfwd.h"    /*! resource::Texture2D structure */

/**
 * @namespace m_texture
 * @brief Namespace for m_texture resource class.
 */
namespace texture {

/**
 * @class Texture2D
 * @brief The class for binding Texture id and can set m_texture's parameters.
 * @date 2018-02-28
 *
 * @log
 * 2018-02-23   m_texture::Texture2D Refactoring
 * 2018-02-28   Add GetTextureWidth, GetTextureHeight inline functions.
 */
class Texture2D {
private:
	/*! Inner struct used in class Texture2D methods, SetTextureParameterI. */
	struct TextureParameter {
		GLint option;   /*! Option of m_texture parameter, such as GL_TEXTURE_MIN_FILTER, etc. */
		GLint mode;     /*! Mode of m_texture parameter option, like a GL_NEAREST, GL_REPEAT. */
	};

    using cell_size = std::pair<float, float>;

public:
    ~Texture2D();

	/**
	 * @brief Constructor get path and m_texture mode as arguments, build and set them.
	 * @param[in] texture_path path to get m_texture data.
	 * @param[in] bind_mode mode to bind m_texture as what m_texture's color data type is.
	 * bind_mode is limited in GL_RGB, GL_RGBA, and so on.
	 */
	Texture2D(const opgs16::resource::Texture2D& texture_container);

	/**
	 * @brief Create m_texture with no m_texture path, but for later use.
	 * @param[in] internal_format color format or internal format to set up each pixel.
	 * @param[in] format format of entire texture.
	 * @param[in] type type.
	 * @param[in] width texture width size to create.
	 * @param[in] height texture height size to create.
	 */
	Texture2D(const GLint internal_format, GLenum format, GLenum type,
              GLsizei width = 256, GLsizei height = 224);

	/**
	 * @brief Set texture's rendering option. (one item version)
	 * @param[in] option Option of texture parameter, such as GL_TEXTURE_MIN_FILTER, etc
	 * @param[in] mode Mode for option of texture parameter, like a GL_NEAREST, GL_REPEAT
	 */
	void SetTextureParameterI(const GLint option, const GLint mode);

	/**
	 * @brief Set texture's rendering options. (multiple item version)
	 * @param[in] THe list of texture parameters.
	 */
	void SetTextureParameterI(const std::vector<TextureParameter>& lists);

	/**
	 * @brief Set border color of texture.
	 * @param[in] border_color array of border color which consists of R, G, B, A.
	 */
	void SetBorderColor(const std::array<GLfloat, 4>& border_color);

	/*! Get Texture id */
	inline GLuint GetId() const {
        return m_texture;
    }

    /*! Get Texture overall width */
    inline int GetTextureWidth() const noexcept {
        return m_width;
    }

    /*! Get Texture overall height */
    inline int GetTextureHeight() const noexcept {
        return m_height;
    }

    /*! Get Texture cell size ranges [0, 1] */
    inline cell_size GetTextureCellSize() const noexcept {
        return m_texture_cell_size;
    }

private:
	mutable GLuint m_texture;           /*! Texture binding id */

    int m_width;                        /*! Texture int width */
    int m_height;                       /*! Texture int height */

    cell_size m_texture_cell_size{};    /*! Texture coordinate cell size */
};

}

#endif // OPGS16_SYSTEM_FRAME_TEXTURE_H