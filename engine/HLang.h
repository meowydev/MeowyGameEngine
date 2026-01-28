//
// Created by mew on 1/26/26.
//

#pragma once
#include <TextEditor.h>

#ifndef MEOWYGAMEENGINE_MEOWYLANG_H
#define MEOWYGAMEENGINE_MEOWYLANG_H

#endif //MEOWYGAMEENGINE_MEOWYLANG_H

inline TextEditor::LanguageDefinition CreateHLang()
{
    TextEditor::LanguageDefinition lang;

    lang.mName = "H"; // what if we connect me (meowy engine) and H? meh
    lang.mKeywords.insert("print"); // Test func

    //COMMENTS
    lang.mSingleLineComment = "//";
    lang.mCommentStart = "/*";
    lang.mCommentEnd = "*/";

    // IDK something ChatGPT said to add probably to make strings look like strings
    lang.mTokenRegexStrings.push_back(
    { R"("(?:\\.|[^"])*")", TextEditor::PaletteIndex::String }
);
    return lang;
}