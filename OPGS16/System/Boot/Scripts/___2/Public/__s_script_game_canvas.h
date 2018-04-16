#ifndef OPGS16_SYSTEM_BOOT_SCRIPTS____2_PUBLIC___S_SCRIPT_GAME_CANVAS_H
#define OPGS16_SYSTEM_BOOT_SCRIPTS____2_PUBLIC___S_SCRIPT_GAME_CANVAS_H

/*!
 * @license BSD 2-Clause License
 *
 * Copyright (c) 2018, Jongmin Yun(Neu.)
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 *
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*!---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*
 * @file System/Scripts/Public/__s_script_game_canvas.h
 * @brief Script file of ::opgs16::builtin::sample::__S_GAME_CANVAS object class.
 * @log
 * 2018-04-15 Create file.
 *----*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*/

#include "../../../../Components/Public/script_frame.h"
#include <vector>

namespace opgs16 {
namespace builtin {
namespace sample {

class __S_SCRIPT_GAME_CANVAS final : public component::CScriptFrame {
public:
    __S_SCRIPT_GAME_CANVAS(opgs16::element::CObject& bind_object);

private:
    canvas::Text* m_score_obj;

    // Life image objects
    std::vector<canvas::Image*> m_life_objects;

    void Start() override final;
    void Update() override final;

SET_UP_TYPE_MEMBER(::opgs16::component::CScriptFrame, __S_SCRIPT_GAME_CANVAS)
};

} /*! opgs16::builtin::sample */
} /*! opgs16::builtin */
} /*! opgs16 */


#endif // OPGS16_SYSTEM_BOOT_SCRIPTS____2_PUBLIC___S_SCRIPT_GAME_CANVAS_H