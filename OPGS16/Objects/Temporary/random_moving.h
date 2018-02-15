#ifndef OPGS16_OBJECTS_TEMPORARY_RANDOM_MOVING_OBJECT_H
#define OPGS16_OBJECTS_TEMPORARY_RANDOM_MOVING_OBJECT_H

/*!
 * @file Objects\Temporary\random_moving.h
 * @brief Temporary collision check object. this object moves randomly.
 * @author Jongmin Yun
 * @date 2018-02-15
 */

#include "..\..\System\Object\object.h"             /*! Object */
#include "..\..\System\Object\sprite_renderer.h"    /*! SpriteRenderer */

class RandomMoveObject : public Object {
public:
    RandomMoveObject(const std::string& sprite_tag);

    [[noreturn]] virtual void Update() override final;
    [[noreturn]] virtual void Draw() override final;

private:
    SpriteRenderer m_sprite_renderer;   /*! Sprite Renderer */
};

#endif // !OBJECTS_TEMPORARY_RANDOM_MOVING_OBJECT_H
