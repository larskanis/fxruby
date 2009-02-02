/********************************************************************************
*                                                                               *
*                    A S C I I   C h a r a c t e r   I n f o                    *
*                                                                               *
*********************************************************************************
* Copyright (C) 2005 by Jeroen van der Zijp.   All Rights Reserved.             *
*********************************************************************************
* This library is free software; you can redistribute it and/or                 *
* modify it under the terms of the GNU Lesser General Public                    *
* License as published by the Free Software Foundation; either                  *
* version 2.1 of the License, or (at your option) any later version.            *
*                                                                               *
* This library is distributed in the hope that it will be useful,               *
* but WITHOUT ANY WARRANTY; without even the implied warranty of                *
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU             *
* Lesser General Public License for more details.                               *
*                                                                               *
* You should have received a copy of the GNU Lesser General Public              *
* License along with this library; if not, write to the Free Software           *
* Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA.    *
*********************************************************************************
* $Id: fxascii.h 2291 2005-12-05 03:37:36Z lyle $                            *
********************************************************************************/
#ifndef FXASCII_H
#define FXASCII_H


namespace FX {

namespace Ascii {

/// Get numeric value of character (this includes hex value)
extern FXAPI FXint digitValue(FXchar asc);

/// Ascii-only common functions
extern FXAPI bool hasCase(FXchar asc);
extern FXAPI bool isUpper(FXchar asc);
extern FXAPI bool isLower(FXchar asc);
extern FXAPI bool isTitle(FXchar asc);
extern FXAPI bool isAscii(FXchar asc);
extern FXAPI bool isLetter(FXchar asc);
extern FXAPI bool isDigit(FXchar asc);
extern FXAPI bool isAlphaNumeric(FXchar asc);
extern FXAPI bool isControl(FXchar asc);
extern FXAPI bool isSpace(FXchar asc);
extern FXAPI bool isBlank(FXchar asc);
extern FXAPI bool isPunct(FXchar asc);
extern FXAPI bool isGraph(FXchar asc);
extern FXAPI bool isPrint(FXchar asc);
extern FXAPI bool isHexDigit(FXchar asc);
extern FXAPI bool isSymbol(FXchar asc);
extern FXAPI bool isSep(FXchar asc);

/// Case conversion
extern FXAPI FXchar toUpper(FXchar asc);
extern FXAPI FXchar toLower(FXchar asc);
extern FXAPI FXchar toTitle(FXchar asc);

}

}

#endif
