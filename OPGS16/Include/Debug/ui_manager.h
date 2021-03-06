#ifndef OPGS16_OBJECTS_DEBUG_SCRIPT_UI_MANAGER_H
#define OPGS16_OBJECTS_DEBUG_SCRIPT_UI_MANAGER_H

///
/// @license BSD 2-Clause License
///
/// Copyright (c) 2018, Jongmin Yun(Neu.), All rights reserved.
/// If you want to read full statements, read LICENSE file.
///

/*!
 * @file Objects\Debug\Script\ui_manager.h
 * @author Jongmin Yun
 * @date 2018-02-13
 */

#include <Component\script_frame.h>

class DebugUiManager final : public opgs16::component::CScriptFrame {
public:
    DebugUiManager(opgs16::element::CObject& obj, opgs16::element::canvas::CText* const,
                   opgs16::element::canvas::CText* const,
                   opgs16::element::canvas::CText* const);

    void Update(float delta_time) override final;

private:
    void Start() override final;

    /*! This components must not be a dangling pointer! */
    opgs16::element::canvas::CText* m_fps;
    opgs16::element::canvas::CText* m_date;
    opgs16::element::canvas::CText* m_tree;

private:
    //void SetHierarchyText(const ObjectTree* item, size_t count, std::string* const text);

    /*! Create members related to type hash value. */
SET_UP_TYPE_MEMBER(::opgs16::component::CScriptFrame, DebugUiManager)
};

#endif // !OPGS16_OBJECTS_DEBUG_SCRIPT_UI_MANAGER_H
