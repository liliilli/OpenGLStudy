#pragma once

#include "..\..\..\System\Frame\scene.h"    /*! Scene */

class Maintenance : public Scene {
public:
    virtual void Initiate() override final;

    virtual void Draw() override final;
};