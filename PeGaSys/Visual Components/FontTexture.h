#pragma once
#include "stdafx.h"
#include "builtInFont_MonoSpace.h"

class FontTexture
{
	//typedef VECTOR< FontElement > FontElementContainer; 
	typedef vector< FontElement > FontElementContainer;
	static const size_t INVALID_FIRST_CHAR = ~size_t(0);

private:
	//FontCommon fontCommon; /// Information common to all characters in font
	size_t idxFirstChar; /// Index of first character in font
	FontElementContainer fontElements; /// Container of FontElements
public:
	//FontTexture();
	//~FontTexture();

	FontTexture() : /*fontCommon(),*/ idxFirstChar(INVALID_FIRST_CHAR) { }

	FontTexture(BuiltInFontE builtInFont) : /*fontCommon(builtInFont),*/ idxFirstChar(BuiltInFont_MonoSpace::_idxFirstChar)
	{
		Allocate(BuiltInFont_MonoSpace::_numCharsTotal);
		// Populate each element in _fontElements.
		for (int idxChar = 0; idxChar < BuiltInFont_MonoSpace::_numCharsTotal; ++idxChar)
		{
			FontElement fontEl(idxChar, builtInFont);
			fontElements.push_back(fontEl);
		}
	}

	void Allocate(size_t numChars) { fontElements.reserve(numChars); }
	/// Given character index, return associated FontElement.
	const FontElement & GetElement(size_t characterIndex) const { return fontElements[characterIndex/* TODO: -Z */]; }
	//const FontCommon & GetCommon() const { return fontCommon; }
	const size_t & GetIdxFirstChar() const { return idxFirstChar; }
	const FontElementContainer & GetFontElements() const { return fontElements; }
};