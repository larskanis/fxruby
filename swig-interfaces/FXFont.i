/***********************************************************************
 * FXRuby -- the Ruby language bindings for the FOX GUI toolkit.
 * Copyright (c) 2001-2009 by Lyle Johnson. All Rights Reserved.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * For further information please contact the author by e-mail
 * at "lyle@lylejohnson.name".
 ***********************************************************************/

%rename("family")  FXFont::getFamily() const;
%rename("foundry") FXFont::getFoundry() const;
%rename("flags")   FXFont::getFlags() const;
%rename("angle")   FXFont::getAngle() const;
%rename("font")    FXFont::getFont() const;

/// Font character set encoding
enum FXFontEncoding {
  FONTENCODING_DEFAULT,         /// Don't care character encoding

  FONTENCODING_ISO_8859_1   = 1,        /// West European (Latin1)
  FONTENCODING_ISO_8859_2   = 2,        /// Central and East European (Latin2)
  FONTENCODING_ISO_8859_3   = 3,        /// Esperanto (Latin3)
  FONTENCODING_ISO_8859_4   = 4,
  FONTENCODING_ISO_8859_5   = 5,                        /// Cyrillic (almost obsolete)
  FONTENCODING_ISO_8859_6   = 6,        /// Arabic
  FONTENCODING_ISO_8859_7   = 7,        /// Greek
  FONTENCODING_ISO_8859_8   = 8,        /// Hebrew
  FONTENCODING_ISO_8859_9   = 9,        /// Turkish (Latin5)
  FONTENCODING_ISO_8859_10  = 10,
  FONTENCODING_ISO_8859_11  = 11,       /// Thai
  FONTENCODING_ISO_8859_13  = 13,       /// Baltic
  FONTENCODING_ISO_8859_14  = 14,
  FONTENCODING_ISO_8859_15  = 15,
  FONTENCODING_ISO_8859_16  = 16,
  FONTENCODING_KOI8         = 17,
  FONTENCODING_KOI8_R       = 18,                       /// Russian
  FONTENCODING_KOI8_U       = 19,                       /// Ukrainian
  FONTENCODING_KOI8_UNIFIED = 20,

  FONTENCODING_CP437        = 437,      /// IBM-PC code page
  FONTENCODING_CP850        = 850,      /// IBMPC Multilingual
  FONTENCODING_CP851        = 851,      /// IBM-PC Greek
  FONTENCODING_CP852        = 852,      /// IBM-PC Latin2
  FONTENCODING_CP855        = 855,      /// IBM-PC Cyrillic
  FONTENCODING_CP856        = 856,      /// IBM-PC Hebrew
  FONTENCODING_CP857        = 857,      /// IBM-PC Turkish
  FONTENCODING_CP860        = 860,      /// IBM-PC Portugese
  FONTENCODING_CP861        = 861,      /// IBM-PC Iceland
  FONTENCODING_CP862        = 862,      /// IBM-PC Israel
  FONTENCODING_CP863        = 863,      /// IBM-PC Canadian/French
  FONTENCODING_CP864        = 864,      /// IBM-PC Arabic
  FONTENCODING_CP865        = 865,      /// IBM-PC Nordic
  FONTENCODING_CP866        = 866,      /// IBM-PC Cyrillic #2
  FONTENCODING_CP869        = 869,      /// IBM-PC Greek #2
  FONTENCODING_CP870        = 870,      /// Latin-2 Multilingual

  FONTENCODING_CP1250       = 1250,     /// Windows Central European
  FONTENCODING_CP1251       = 1251,     /// Windows Russian
  FONTENCODING_CP1252       = 1252,     /// Windows Latin1
  FONTENCODING_CP1253       = 1253,     /// Windows Greek
  FONTENCODING_CP1254       = 1254,     /// Windows Turkish
  FONTENCODING_CP1255       = 1255,     /// Windows Hebrew
  FONTENCODING_CP1256       = 1256,     /// Windows Arabic
  FONTENCODING_CP1257       = 1257,     /// Windows Baltic
  FONTENCODING_CP1258       = 1258,     /// Windows Vietnam
  FONTENCODING_CP874        = 874,      /// Windows Thai

  FONTENCODING_UNICODE      = 9999,

  FONTENCODING_LATIN1      = FONTENCODING_ISO_8859_1,   /// Latin 1 (West European)
  FONTENCODING_LATIN2      = FONTENCODING_ISO_8859_2,   /// Latin 2 (East European)
  FONTENCODING_LATIN3      = FONTENCODING_ISO_8859_3,   /// Latin 3 (South European)
  FONTENCODING_LATIN4      = FONTENCODING_ISO_8859_4,   /// Latin 4 (North European)
  FONTENCODING_LATIN5      = FONTENCODING_ISO_8859_9,   /// Latin 5 (Turkish)
  FONTENCODING_LATIN6      = FONTENCODING_ISO_8859_10,  /// Latin 6 (Nordic)
  FONTENCODING_LATIN7      = FONTENCODING_ISO_8859_13,  /// Latin 7 (Baltic Rim)
  FONTENCODING_LATIN8      = FONTENCODING_ISO_8859_14,  /// Latin 8 (Celtic)
  FONTENCODING_LATIN9      = FONTENCODING_ISO_8859_15,  /// Latin 9 AKA Latin 0
  FONTENCODING_LATIN10     = FONTENCODING_ISO_8859_16,  /// Latin 10

  FONTENCODING_USASCII     = FONTENCODING_ISO_8859_1,   /// Latin 1
  FONTENCODING_WESTEUROPE  = FONTENCODING_ISO_8859_1,   /// Latin 1 (West European)
  FONTENCODING_EASTEUROPE  = FONTENCODING_ISO_8859_2,   /// Latin 2 (East European)
  FONTENCODING_SOUTHEUROPE = FONTENCODING_ISO_8859_3,   /// Latin 3 (South European)
  FONTENCODING_NORTHEUROPE = FONTENCODING_ISO_8859_4,   /// Latin 4 (North European)
  FONTENCODING_CYRILLIC    = FONTENCODING_ISO_8859_5,   /// Cyrillic
  FONTENCODING_RUSSIAN     = FONTENCODING_KOI8,         /// Cyrillic
  FONTENCODING_ARABIC      = FONTENCODING_ISO_8859_6,   /// Arabic
  FONTENCODING_GREEK       = FONTENCODING_ISO_8859_7,   /// Greek
  FONTENCODING_HEBREW      = FONTENCODING_ISO_8859_8,   /// Hebrew
  FONTENCODING_TURKISH     = FONTENCODING_ISO_8859_9,   /// Latin 5 (Turkish)
  FONTENCODING_NORDIC      = FONTENCODING_ISO_8859_10,  /// Latin 6 (Nordic)
  FONTENCODING_THAI        = FONTENCODING_ISO_8859_11,  /// Thai
  FONTENCODING_BALTIC      = FONTENCODING_ISO_8859_13,  /// Latin 7 (Baltic Rim)
  FONTENCODING_CELTIC      = FONTENCODING_ISO_8859_14   /// Latin 8 (Celtic)
  };


/// Font style
struct FXFontDesc {
  FXFontDesc();
  FXchar          face[116];                /// Face name
  FXushort        size;                     /// Size in deci-points
  FXushort        weight;                   /// Weight [light, normal, bold, ...]
  FXushort        slant;                    /// Slant [normal, italic, oblique, ...]
  FXushort        setwidth;                 /// Set width [normal, condensed, expanded, ...]
  FXushort        encoding;                 /// Encoding of character set
  FXushort        flags;                    /// Flags
  ~FXFontDesc();
  };


/// Font class
class FXFont : public FXId {
public:

  /// Font pitch hints
  enum {
    Fixed          = 1,         /// Fixed pitch, mono-spaced
    Variable       = 2          /// Variable pitch, proportional spacing
    };

  /// Font style hints
  enum {
    Decorative     = 4,         /// Fancy fonts
    Modern         = 8,         /// Monospace typewriter font
    Roman          = 16,        /// Variable width times-like font, serif
    Script         = 32,        /// Script or cursive
    Swiss          = 64,        /// Helvetica/swiss type font, sans-serif
    System         = 128,       /// System font
    X11            = 256,       /// Raw X11 font string
    Scalable       = 512,       /// Scalable fonts
    Polymorphic    = 1024,      /// Polymorphic fonts, e.g. parametric weight, slant, etc.
    Rotatable      = 2048       /// Rotatable fonts
    };

  /// Font slant options
  enum {
    ReverseOblique = 1,         /// Reversed oblique
    ReverseItalic  = 2,         /// Reversed italic
    Straight       = 5,         /// Straight, not slanted
    Italic         = 8,         /// Italics
    Oblique        = 9          /// Oblique slant
    };

  /// Font weight options
  enum {
    Thin           = 10,        /// Thin
    ExtraLight     = 20,        /// Extra light
    Light          = 30,        /// Light
    Normal         = 40,        /// Normal or regular weight
    Medium         = 50,        /// Medium bold face
    DemiBold       = 60,        /// Demi bold face
    Bold           = 70,        /// Bold face
    ExtraBold      = 80,        /// Extra
    Black          = 90         /// Black
    };

  /// Condensed or expanded options
  enum {
    UltraCondensed = 50,        /// Ultra condensed printing
    ExtraCondensed = 63,        /// Extra condensed
    Condensed      = 75,        /// Condensed
    SemiCondensed  = 87,        /// Semi-condensed
    NonExpanded    = 100,       /// Regular printing
    SemiExpanded   = 113,       /// Semi expanded
    Expanded       = 125,       /// Expanded
    ExtraExpanded  = 150,       /// Extra expanded
    UltraExpanded  = 200        /// Ultra expanded
    };

public:
  %extend {
    /**
    * Construct a font with given font description of the form:
    *
    *     fontname [ "[" foundry "]" ] ["," size ["," weight ["," slant ["," setwidth ["," encoding ["," hints]]]]]]
    *
    * For example:
    *
    *     "helvetica [bitstream],120,bold,italic,normal,iso8859-1,0"
    *
    * Typically, at least the font name, and size must be given for
    * normal font matching.  As a special case, raw X11 fonts can also be
    * passed, for example:
    *
    *     "9x15bold"
    *
    * Note: use of the raw X11 fonts is stronly discouraged.
    */
    FXFont(FXApp* a,const FXString& string){
      return new FXRbFont(a,string);
      }

    /**
    * Construct a font with given name, size in points, weight, slant, character set
    * encoding, setwidth, and hints.
    * The font name may be comprised of a family name and optional foundry name enclosed in
    * square brackets, for example, "helvetica [bitstream]".
    */
    FXFont(FXApp* a,const FXString& face,FXuint sz,FXuint wt=FXFont::Normal,FXuint slant=FXFont::Straight,FXuint encoding=FONTENCODING_DEFAULT,FXuint setwidth=FXFont::NonExpanded,FXuint h=0){
      return new FXRbFont(a,face,sz,wt,slant,encoding,setwidth,h);
      }

    /// Construct font from font description
    FXFont(FXApp* a,const FXFontDesc& fontdesc){
      return new FXRbFont(a,fontdesc);
      }
    }

  /// Return family part of name
  FXString getFamily() const;

  /// Return foundry part of name
  FXString getFoundry() const;

  /// Get font family name
  const FXString& getName() const;

  /// Get actual family name
  const FXString& getActualName() const;

  /// Get size in deci-points
  FXuint getSize() const;

  /// Get actual size in deci-points
  FXuint getActualSize() const;

  /// Get font weight
  FXuint getWeight() const;

  /// Get actual font weight
  FXuint getActualWeight() const;

  /// Get slant
  FXuint getSlant() const;

  /// Get actual slant
  FXuint getActualSlant() const;

  /// Get character set encoding
  FXuint getEncoding() const;

  /// Get actual character set encoding
  FXuint getActualEncoding() const;

  /// Get setwidth
  FXuint getSetWidth() const;

  /// Get actual setwidth
  FXuint getActualSetWidth() const;

  /// Get hints
  FXuint getHints() const;

  /// Get flags
  FXuint getFlags() const;

  %extend {
    // Get font description
    FXFontDesc getFontDesc() const {
      FXFontDesc fontdesc;
      self->getFontDesc(fontdesc);
      return fontdesc;
    }
  }

  /// Return angle
  FXint getAngle() const;

  /**
  * Return the font description as a string suitable for
  * parsing with setFont(), see above.
  */
  FXString getFont() const;

  %extend {
    // List all fonts matching hints (returns an array of FXFontDesc objects)
    static VALUE listFonts(const FXString& face,FXuint wt=0,FXuint sl=0,FXuint sw=0,FXuint en=0,FXuint h=0) {
      FXFontDesc* fonts;
      FXuint numfonts;
      VALUE results = rb_ary_new();
      if (FXFont::listFonts(fonts, numfonts, face, wt, sl, sw, en, h)) {
        for (FXuint i = 0; i < numfonts; i++)
          rb_ary_push(results, to_ruby(new FXFontDesc(fonts[i])));
        FXFREE(&fonts);
      }
      return results;
    }
  }

  /// Destroy font
  virtual ~FXFont();
  };


DECLARE_FXOBJECT_VIRTUALS(FXFont)
DECLARE_FXID_VIRTUALS(FXFont)
DECLARE_FXFONT_VIRTUALS(FXFont)

