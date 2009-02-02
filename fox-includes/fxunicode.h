/********************************************************************************
*                                                                               *
*                   U N I C O D E   C h a r a c t e r   I n f o                 *
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
* $Id: fxunicode.h 2291 2005-12-05 03:37:36Z lyle $                          *
********************************************************************************/
#ifndef FXUNICODE_H
#define FXUNICODE_H


namespace FX {


/// General Category
enum {
  CatNotAssigned          = 0,     /// Cn Other, Not Assigned (no characters in the file have this property)
  CatControl              = 1,     /// Cc Other, Control
  CatFormat               = 2,     /// Cf Other, Format
  CatSurrogate            = 3,     /// Cs Other, Surrogate
  CatOther                = 4,     /// Co Other, Private Use
  CatMarkNonSpacing       = 5,     /// Mn Mark, Nonspacing
  CatMarkSpacingCombining = 6,     /// Mc Mark, Spacing Combining
  CatMarkEnclosing        = 7,     /// Me Mark, Enclosing
  CatSeparatorSpace       = 8,     /// Zs Separator, Space
  CatSeparatorLine        = 9,     /// Zl Separator, Line
  CatSeparatorParagraph   = 10,    /// Zp Separator, Paragraph
  CatLetterUpper          = 11,    /// Lu Letter, Uppercase
  CatLetterLower          = 12,    /// Ll Letter, Lowercase
  CatLetterTitle          = 13,    /// Lt Letter, Titlecase
  CatLetterModifier       = 14,    /// Lm Letter, Modifier
  CatLetterOther          = 15,    /// Lo Letter, Other
  CatNumberLetter         = 16,    /// Nl Number, Letter
  CatNumberDecimal        = 17,    /// Nd Number, Decimal Digit
  CatNumberOther          = 18,    /// No Number, Other
  CatPunctConnector       = 19,    /// Pc Punctuation, Connector
  CatPunctDash            = 20,    /// Pd Punctuation, Dash
  CatPunctOpen            = 21,    /// Ps Punctuation, Open
  CatPunctClose           = 22,    /// Pe Punctuation, Close
  CatPunctInitial         = 23,    /// Pi Punctuation, Initial quote (may behave like Ps or Pe depending on usage)
  CatPunctFinal           = 24,    /// Pf Punctuation, Final quote (may behave like Ps or Pe depending on usage)
  CatPunctOther           = 25,    /// Po Punctuation, Other
  CatSymbolMath           = 26,    /// Sm Symbol, Math
  CatSymbolCurrency       = 27,    /// Sc Symbol, Currency
  CatSymbolModifier       = 28,    /// Sk Symbol, Modifier
  CatSymbolOther          = 29     /// So Symbol, Other
  };


/// Bidi types
enum {
  DirL   = 0,           /// Left-to-Right
  DirLRE = 1,           /// Left-to-Right Embedding
  DirLRO = 2,           /// Left-to-Right Override
  DirR   = 3,           /// Right-to-Left
  DirAL  = 4,           /// Right-to-Left Arabic
  DirRLE = 5,           /// Right-to-Left Embedding
  DirRLO = 6,           /// Right-to-Left Override
  DirPDF = 7,           /// Pop Directional Format
  DirEN  = 8,           /// European Number
  DirES  = 9,           /// European Number Separator
  DirET  = 10,          /// European Number Terminator
  DirAN  = 11,          /// Arabic Number
  DirCS  = 12,          /// Common Number Separator
  DirNSM = 13,          /// Non-Spacing Mark
  DirBN  = 14,          /// Boundary Neutral
  DirB   = 15,          /// Paragraph Separator
  DirS   = 16,          /// Segment Separator
  DirWS  = 17,          /// Whitespace
  DirON  = 18           /// Other Neutrals
  };


/// Arabic joining
enum {
  NonJoining   = 0,
  RightJoining = 1,
  DualJoining  = 2,
  JoinCausing  = 3
  };


/// Combining class
enum {
  CombBelowLeftAtt  = 200,     /// Below left attached
  CombBelowAtt      = 202,     /// Below attached
  CombBelowRightAtt = 204,     /// Below right attached
  CombLeftAtt       = 208,     /// Left attached (reordrant around single base character)
  CombRightAtt      = 210,     /// Right attached
  CombAboveLeftAtt  = 212,     /// Above left attached
  CombAboveAtt      = 214,     /// Above attached
  CombAboveRightAtt = 216,     /// Above right attached
  CombBelowLeft     = 218,     /// Below left
  CombBelow         = 220,     /// Below
  CombBelowRight    = 222,     /// Below right
  CombLeft          = 224,     /// Left (reordrant around single base character)
  CombRight         = 226,     /// Right
  CombAboveLeft     = 228,     /// Above left
  CombAbove         = 230,     /// Above
  CombAboveRight    = 232,     /// Above right
  CombDoubleBelow   = 233,     /// Double below
  CombDoubleAbove   = 234,     /// Double above
  CombIotaSub       = 240      /// Below (iota subscript)
  };


/// Decompose types
enum {
  DecNone      = 0,     /// Non-decomposable
  DecFont      = 1,     /// A font variant (e.g. a blackletter form)
  DecNoBreak   = 2,     /// A no-break version of a space or hyphen
  DecInitial   = 3,     /// An initial presentation form (Arabic)
  DecMedial    = 4,     /// A medial presentation form (Arabic)
  DecFinal     = 5,     /// A final presentation form (Arabic)
  DecIsolated  = 6,     /// An isolated presentation form (Arabic)
  DecCircle    = 7,     /// An encircled form
  DecSuper     = 8,     /// A superscript form
  DecSub       = 9,     /// A subscript form
  DecVertical  = 10,    /// A vertical layout presentation form
  DecWide      = 11,    /// A wide (or zenkaku) compatibility character
  DecNarrow    = 12,    /// A narrow (or hankaku) compatibility character
  DecSmall     = 13,    /// A small variant form (CNS compatibility)
  DecSquare    = 14,    /// A CJK squared font variant
  DecFraction  = 15,    /// A vulgar fraction form
  DecCompat    = 16,    /// Compatible
  DecCanonical = 17     /// Canonical (equivalent)
  };


/// Line break types
enum {
  BreakUnknown    = 0,          /// XX Unknown

  BreakMandarory  = 1,          /// BK Mandatory Break
  BreakReturn     = 2,          /// CR Carriage Return
  BreakLineFeed   = 3,          /// LF Line Feed
  BreakCombMark   = 4,          /// CM Attached Characters and Combining Marks
  BreakNextLine   = 5,          /// NL Next Line
  BreakSurrogate  = 6,          /// SG Surrogates
  BreakWordJoiner = 7,          /// WJ Word Joiner
  BreakZWSpace    = 8,          /// ZW Zero Width Space
  BreakGlue       = 9,          /// GL Non-breaking Glue
  BreakContingent = 10,         /// CB Contingent Break Opportunity
  BreakSpace      = 11,         /// SP Space

  BreakBoth       = 12,         /// B2 Break Opportunity Before and After
  BreakAfter      = 13,         /// BA Break Opportunity After
  BreakBefore     = 14,         /// BB Break Opportunity Before
  BreakHyphen     = 15,         /// HY Hyphen

  BreakOpen       = 16,         /// OP Opening Punctuation
  BreakClose      = 17,         /// CL Closing Punctuation
  BreakQuote      = 18,         /// QU Ambiguous Quotation
  BreakExclaim    = 19,         /// EX Exclamation/Interrogation
  BreakInsep      = 20,         /// IN Inseparable
  BreakNonStart   = 21,         /// NS Non Starter

  BreakInfix      = 22,         /// IS Infix Separator (Numeric)
  BreakNumeric    = 23,         /// NU Numeric
  BreakPostfix    = 24,         /// PO Postfix (Numeric)
  BreakPrefix     = 25,         /// PR Prefix (Numeric)
  BreakSymbol     = 26,         /// SY Symbols Allowing Breaks

  BreakOrdinary   = 27,         /// AL Ordinary Alphabetic and Symbol Characters
  BreakIdeograph  = 28,         /// ID Ideographic
  BreakComplex    = 29          /// SA Complex Context (South East Asian)
  };


/// Scripts
enum {
  ScriptCommon             = 0,       /// Zyyy
  ScriptInherited          = 1,       /// Qaai

  ScriptLatin              = 2,       /// Latn  European scripts
  ScriptGreek              = 3,       /// Grek
  ScriptCyrillic           = 4,       /// Cyrl (Cyrs)
  ScriptArmenian           = 5,       /// Armn
  ScriptGeorgian           = 6,       /// Geor (Geon, Geoa)
  ScriptRunic              = 7,       /// Runr
  ScriptOgham              = 8,       /// Ogam

  ScriptHebrew             = 9,       /// Hebr  Middle eastern
  ScriptArabic             = 10,      /// Arab
  ScriptSyriac             = 11,      /// Syrc (Syrj, Syrn, Syre)
  ScriptThaana             = 12,      /// Thaa

  ScriptDevanagari         = 13,      /// Deva  Indic
  ScriptBengali            = 14,      /// Beng
  ScriptGurmukhi           = 15,      /// Guru
  ScriptGujarati           = 16,      /// Gujr
  ScriptOriya              = 17,      /// Orya
  ScriptTamil              = 18,      /// Taml
  ScriptTelugu             = 19,      /// Telu
  ScriptKannada            = 20,      /// Knda
  ScriptMalayalam          = 21,      /// Mlym
  ScriptSinhala            = 22,      /// Sinh
  ScriptThai               = 23,      /// Thai
  ScriptLao                = 24,      /// Laoo
  ScriptTibetan            = 25,      /// Tibt
  ScriptMyanmar            = 26,      /// Mymr
  ScriptKhmer              = 27,      /// Khmr

  ScriptHan                = 28,      /// Hani  Asian
  ScriptHiragana           = 29,      /// Hira
  ScriptKatakana           = 30,      /// Kana
  ScriptHangul             = 31,      /// Hang
  ScriptBopomofo           = 32,      /// Bopo
  ScriptYi                 = 33,      /// Yiii

  ScriptEthiopic           = 34,      /// Ethi  Misc
  ScriptCherokee           = 35,      /// Cher
  ScriptCanadianAboriginal = 36,      /// Cans
  ScriptMongolian          = 37,      /// Mong
  ScriptGothic             = 38,      /// Goth

  ScriptTagalog            = 39,      /// Tglg
  ScriptHanunoo            = 40,      /// Hano
  ScriptBuhid              = 41,      /// Buhd
  ScriptTagbanwa           = 42,      /// Tagb
  ScriptLimbu              = 43,      /// Limb
  ScriptTaiLe              = 44,      /// Tale
  ScriptUgaritic           = 45,      /// Ugar
  ScriptOsmanya            = 46,      /// Osma
  ScriptCypriot            = 47,      /// Cprt
  ScriptShavian            = 48,      /// Shaw
  ScriptDeseret            = 49,      /// Dsrt
  ScriptKatakanaHiragana   = 50       /// Hrkt
  };


/// Unicode versions of common character functions
namespace Unicode {

/// Character wide character category
extern FXAPI FXuint charCategory(FXwchar ucs);

/// Get character wide character direction
extern FXAPI FXuint charDirection(FXwchar ucs);

/// Get wide character decompose type
extern FXAPI FXuint decomposeType(FXwchar ucs);

/// Return number of wide characters in decomposition
extern FXAPI FXuint charNumDecompose(FXwchar ucs);

/// Return wide character decomposition
extern FXAPI const FXwchar* charDecompose(FXwchar ucs);

/// Return wide character composition from ucsa and ucsb
extern FXAPI FXwchar charCompose(FXwchar ucsa,FXwchar ucsb);

/// Get wide character joining
extern FXAPI FXuint joiningType(FXwchar ucs);

/// Get wide character symmetry
extern FXAPI FXuint isSymmetric(FXwchar ucs);

/// Get wide character combining type; zero means starter
extern FXAPI FXuint charCombining(FXwchar ucs);

/// Get numeric value of wide character (this includes hex value)
extern FXAPI FXint digitValue(FXwchar ucs);

/// Get linebreak type of wide character
extern FXAPI FXuint lineBreakType(FXwchar ucs);


/// Get mirror image of wide character or character itself
extern FXAPI FXwchar mirrorImage(FXwchar ucs);

/// Script type of wide character
extern FXAPI FXuint scriptType(FXwchar ucs);


/// Unicode flavor of common functions
extern FXAPI bool hasCase(FXwchar ucs);
extern FXAPI bool isUpper(FXwchar ucs);
extern FXAPI bool isLower(FXwchar ucs);
extern FXAPI bool isTitle(FXwchar ucs);
extern FXAPI bool isAscii(FXwchar ucs);
extern FXAPI bool isLetter(FXwchar ucs);
extern FXAPI bool isDigit(FXwchar ucs);
extern FXAPI bool isAlphaNumeric(FXwchar ucs);
extern FXAPI bool isControl(FXwchar ucs);
extern FXAPI bool isSpace(FXwchar ucs);
extern FXAPI bool isBlank(FXwchar ucs);
extern FXAPI bool isPunct(FXwchar ucs);
extern FXAPI bool isGraph(FXwchar ucs);
extern FXAPI bool isPrint(FXwchar ucs);
extern FXAPI bool isHexDigit(FXwchar ucs);
extern FXAPI bool isSymbol(FXwchar ucs);
extern FXAPI bool isMark(FXwchar ucs);
extern FXAPI bool isSep(FXwchar ucs);

/// Case conversion
extern FXAPI FXwchar toUpper(FXwchar ucs);
extern FXAPI FXwchar toLower(FXwchar ucs);
extern FXAPI FXwchar toTitle(FXwchar ucs);

}


}

#endif
