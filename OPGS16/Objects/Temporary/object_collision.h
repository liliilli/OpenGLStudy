#ifndef OBJECTS_TEMPORARY_OBJECT_COLLISION_H
#define OBJECTS_TEMPORARY_OBJECT_COLLISION_H

/*!
 * @file Objects\Temporary\object_collision.h
 * @brief Temporary collision check object.
 * @author Jongmin Yun
 * @date 2018-02-14
 */

#include "..\..\System\Object\object.h"             /*! Object */
#include "..\..\System\Object\sprite_renderer.h"    /*! SpriteRenderer */

class ObjectCollidable : public Object {
public:
    ObjectCollidable(const std::string& sprite_tag);

    [[noreturn]] virtual void Update() override final;
    [[noreturn]] virtual void Draw() override final;

private:
    SpriteRenderer m_sprite_renderer;   /*! Sprite Renderer */
};

#endif // !OBJECTS_TEMPORARY_OBJECT_COLLISION_H
