#pragma once
/** \file builtInFont_MonoSpace.h

\brief Built-in data for a monospace font

\author Copyright 2016 MJG; All rights reserved.
*/
#ifndef PEGASYS_GUI_MARKUP_BUILT_IN_FONT_MONOSPACE_H
#define PEGASYS_GUI_MARKUP_BUILT_IN_FONT_MONOSPACE_H

//#include <DyDaLaS/DataAccess/dynamicRecord.h>
//
//#include <Core/Containers/sList.h>
//#include <Core/Utility/macros.h>
//#include <Core/File/debugPrint.h>
//#include <Core/Math/vec2.h>
//#include <Core/Math/vec4.h>

#include <stdio.h>

// Macros ----------------------------------------------------------------------
// Types -----------------------------------------------------------------------

//namespace PeGaSys
//{
//    namespace GuiMarkup
//    {

/// Token used to initialize a built-in monospace font.
enum BuiltInFontE { BUILT_IN_FONT_MONOSPACE };

namespace BuiltInFont_MonoSpace
{
	static const int            _numCharsPerRow = 16;
	static const int            _numCharsPerCol = 16;
	static const int            _numCharsTotal = _numCharsPerRow * _numCharsPerCol;
	static const int            _idxFirstChar = 0;
	static const int            _pixelsWidePerChar = 8;
	static const int            _pixelsHighPerChar = 8;
	static const int            _numChannelsPerPixel = 4;
	static const float          _baseline = 2.0f;
	static const int            _pixelsWideTotal = _pixelsWidePerChar * _numCharsPerRow;
	static const int            _pixelsHighTotal = _pixelsHighPerChar * _numCharsPerCol;
};

// Public variables ------------------------------------------------------------

extern const unsigned char builtInFont_MonoSpace_Rgba[BuiltInFont_MonoSpace::_numCharsPerCol][BuiltInFont_MonoSpace::_pixelsHighPerChar * BuiltInFont_MonoSpace::_pixelsWideTotal * BuiltInFont_MonoSpace::_numChannelsPerPixel];

// Public functions ------------------------------------------------------------

//    } ;
//} ;

#endif
