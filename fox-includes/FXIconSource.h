/********************************************************************************
*                                                                               *
*                            I c o n   S o u r c e                              *
*                                                                               *
*********************************************************************************
* Copyright (C) 2005,2006 by Jeroen van der Zijp.   All Rights Reserved.        *
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
* $Id: FXIconSource.h 2344 2006-02-12 21:19:36Z lyle $                      *
********************************************************************************/
#ifndef FXICONSOURCE_H
#define FXICONSOURCE_H

#ifndef FXOBJECT_H
#include "FXObject.h"
#endif

namespace FX {

class FXApp;
class FXIcon;
class FXImage;

/**
* An icon source is a class that loads an icon of any type.
* It exists purely for convenience, to make loading icons
* simpler by concentrating the knowledge of the supported
* icon formats in a single place.
* Needless to say, this class is subclassable, allowing users
* to add additional icon types and make them available to
* all widgets which deal with icons.
* Note, the icons are loaded, but NOT created (realized) yet;
* this allows users to manipulate the pixel data prior to
* realizing the icons.
*/
class FXAPI FXIconSource : public FXObject {
  FXDECLARE(FXIconSource)
protected:
  FXApp *app;
protected:
  FXIconSource():app(NULL){}
private:
  FXIconSource(const FXIconSource&);
  FXIconSource &operator=(const FXIconSource&);
  FXImage *scaleToSize(FXImage *image,FXint size,FXint qual) const;
public:

  /// Construct an icon source
  FXIconSource(FXApp* a);

  /**
  * Load an icon from the file filename. By default, the file extension is
  * stripped and used as the icon type; if an explicit icon type is forced,
  * then that type is used and the extension is ignored.
  * For example, loadIcon("icon","gif") will try to load a CompuServe GIF
  * file, since the filename does not give any clue as to the type of the
  * icon.
  */
  virtual FXIcon *loadIconFile(const FXString& filename,const FXString& type=FXString::null) const;

  /**
  * Load an icon of a given type (e.g. "gif") from reswrapped data.
  * Returns NULL if there's some error loading the icon.  [The optional
  * parameter is actually mandatory at the time of this writing; future
  * versions will attempt to inspect the first few bytes of the stream
  * to divine the icon format if the parameter is omitted].
  */
  virtual FXIcon *loadIconData(const void *pixels,const FXString& type=FXString::null) const;

  /**
  * Load an icon of a given type (e.g. "gif") from an already open stream.
  * Returns NULL if there's some error loading the icon.  [The optional
  * parameter is actually mandatory at the time of this writing; future
  * versions will attempt to inspect the first few bytes of the stream
  * to divine the icon format if the parameter is omitted].
  */
  virtual FXIcon *loadIconStream(FXStream& store,const FXString& type=FXString::null) const;

  /**
  * Load an image from the file filename. By default, the file extension is
  * stripped and used as the image type; if an explicit image type is forced,
  * then that type is used and the extension is ignored.
  * For example, loadImage("image","gif") will try to load a CompuServe GIF
  * file, since the filename does not give any clue as to the type of the
  * image.
  */
  virtual FXImage *loadImageFile(const FXString& filename,const FXString& type=FXString::null) const;

  /**
  * Load an image of a given type (e.g. "gif") from reswrapped data.
  * Returns NULL if there's some error loading the icon.  [The optional
  * parameter is actually mandatory at the time of this writing; future
  * versions will attempt to inspect the first few bytes of the stream
  * to divine the icon format if the parameter is omitted].
  */
  virtual FXImage *loadImageData(const void *pixels,const FXString& type=FXString::null) const;

  /**
  * Load an image of a given type (e.g. "gif") from an already open stream.
  * Returns NULL if there's some error loading the image.  [The optional
  * parameter is actually mandatory at the time of this writing; future
  * versions will attempt to inspect the first few bytes of the stream
  * to divine the image format if the parameter is omitted].
  */
  virtual FXImage *loadImageStream(FXStream& store,const FXString& type=FXString::null) const;


  /// Load icon and scale it such that its dimensions does not exceed given size
  virtual FXIcon *loadScaledIconFile(const FXString& filename,FXint size=32,FXint qual=0,const FXString& type=FXString::null) const;

  /// Load icon and scale it such that its dimensions does not exceed given size
  virtual FXIcon *loadScaledIconData(const void *pixels,FXint size=32,FXint qual=0,const FXString& type=FXString::null) const;

  /// Load icon and scale it such that its dimensions does not exceed given size
  virtual FXIcon *loadScaledIconStream(FXStream& store,FXint size=32,FXint qual=0,const FXString& type=FXString::null) const;

  /// Load image and scale it such that its dimensions does not exceed given size
  virtual FXImage *loadScaledImageFile(const FXString& filename,FXint size=32,FXint qual=0,const FXString& type=FXString::null) const;

  /// Load image and scale it such that its dimensions does not exceed given size
  virtual FXImage *loadScaledImageData(const void *pixels,FXint size=32,FXint qual=0,const FXString& type=FXString::null) const;

  /// Load image and scale it such that its dimensions does not exceed given size
  virtual FXImage *loadScaledImageStream(FXStream& store,FXint size=32,FXint qual=0,const FXString& type=FXString::null) const;


  /// Save to stream
  virtual void save(FXStream& store) const;

  /// Load from stream
  virtual void load(FXStream& store);

  /// Destroy
  virtual ~FXIconSource();
  };


}

#endif
