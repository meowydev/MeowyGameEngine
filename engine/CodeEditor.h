//
// Created by mew on 1/26/26.
//
#pragma once
#include <TextEditor.h>
#include "HLang.h"

#ifndef MEOWYGAMEENGINE_CODEEDITOR_H
#define MEOWYGAMEENGINE_CODEEDITOR_H

#endif //MEOWYGAMEENGINE_CODEEDITOR_H

class CodeEditor
{
    public:
    TextEditor editor;

    CodeEditor()
    {
        editor.SetLanguageDefinition(CreateHLang());
        editor.SetText("// Welcome!");
    }

    void Draw()
    {
        editor.Render("CodeEditor");
    }
};