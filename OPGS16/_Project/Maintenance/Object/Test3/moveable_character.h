#pragma once
#include "../../../../System/Element/Public/object.h"

class MoveableCharacter final : public opgs16::element::CObject {
public:
    MoveableCharacter(const float size);
private:
    virtual void Render() override final;

    ShaderWrapper* m_wrapper;
};