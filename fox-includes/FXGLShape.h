/********************************************************************************
*                                                                               *
*                   O p e n G L   S h a p e   O b j e c t                       *
*                                                                               *
*********************************************************************************
* Copyright (C) 1998,2005 by Jeroen van der Zijp.   All Rights Reserved.        *
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
* $Id: FXGLShape.h 2127 2005-08-07 20:21:35Z lyle $                         *
********************************************************************************/
#ifndef FXGLSHAPE_H
#define FXGLSHAPE_H

#ifndef FXGLOBJECT_H
#include "FXGLObject.h"
#endif

namespace FX {


class FXGLViewer;
class FXGLObject;


// Shape drawing options
enum {
  SURFACE_SINGLESIDED   = 0,              // Single-sided [both sides same]
  SURFACE_DUALSIDED     = 0x00000001,     // Dual-sided surface
  SHADING_NONE          = 0,              // No light source
  SHADING_SMOOTH        = 0x00000002,     // Smooth shaded
  SHADING_FLAT          = 0x00000004,     // Flag shaded
  FACECULLING_OFF       = 0,              // No face culling
  FACECULLING_ON        = 0x00000008,     // Cull backward facing surfaces
  STYLE_SURFACE         = 0x00000010,     // Draw filled surfaces
  STYLE_WIREFRAME       = 0x00000020,     // Draw wire frame
  STYLE_POINTS          = 0x00000040,     // Draw as points
  STYLE_BOUNDBOX        = 0x00000080      // Draw bounding box
  };



/// OpenGL Shape Object
class FXAPI FXGLShape : public FXGLObject {
  FXDECLARE_ABSTRACT(FXGLShape)
protected:
  FXVec3f       position;             // Middle of the Bounding Box
  FXMaterial    material[2];          // Front and back material properties
  FXRangef      range;                // Range box
  FXuint	options;              // Drawing options
  FXString	tip;
protected:
  FXGLShape();
  virtual void drawshape(FXGLViewer*){}  // To be overloaded by derived class
  void drawbox();
  void drawhandles();
public:
  long onDNDDrop(FXObject*,FXSelector,void*);
  long onDNDMotion(FXObject*,FXSelector,void*);
  long onQueryTip(FXObject*,FXSelector,void*);
  long onCmdShadeOff(FXObject*,FXSelector,void*);
  long onUpdShadeOff(FXObject*,FXSelector,void*);
  long onCmdShadeOn(FXObject*,FXSelector,void*);
  long onUpdShadeOn(FXObject*,FXSelector,void*);
  long onCmdShadeSmooth(FXObject*,FXSelector,void*);
  long onUpdShadeSmooth(FXObject*,FXSelector,void*);
  long onCmdFrontMaterial(FXObject*,FXSelector,void*);
  long onUpdFrontMaterial(FXObject*,FXSelector,void*);
  long onCmdBackMaterial(FXObject*,FXSelector,void*);
  long onUpdBackMaterial(FXObject*,FXSelector,void*);
  long onCmdDrawingStyle(FXObject*,FXSelector,void*);
  long onUpdDrawingStyle(FXObject*,FXSelector,void*);
public:
  enum {
    ID_SHADEOFF=FXGLObject::ID_LAST,
    ID_SHADEON,
    ID_SHADESMOOTH,
    ID_TOGGLE_SIDED,
    ID_TOGGLE_CULLING,
    ID_STYLE_POINTS,
    ID_STYLE_WIREFRAME,
    ID_STYLE_SURFACE,
    ID_STYLE_BOUNDINGBOX,
    ID_FRONT_MATERIAL,
    ID_BACK_MATERIAL,
    ID_LAST
    };
public:

  /// Construct with specified origin and options
  FXGLShape(FXfloat x,FXfloat y,FXfloat z,FXuint opts);

  /// Construct with specified origin, options and front and back materials
  FXGLShape(FXfloat x,FXfloat y,FXfloat z,FXuint opts,const FXMaterial& front,const FXMaterial& back);

  /// Copy constructor
  FXGLShape(const FXGLShape& orig);

  /// Called by the viewer to get bounds for this object
  virtual void bounds(FXRangef& box);

  /// Draw this object in a viewer
  virtual void draw(FXGLViewer* viewer);

  /// Draw this object for hit-testing purposes
  virtual void hit(FXGLViewer* viewer);

  /// Copy this object
  virtual FXGLObject* copy();

  /// Return true if this object can be dragged around
  virtual FXbool canDrag() const;

  /// Return true if this object can be deleted from the scene
  virtual FXbool canDelete() const;

  /// Drag this object from one position to another
  virtual FXbool drag(FXGLViewer* viewer,FXint fx,FXint fy,FXint tx,FXint ty);

  /// Set the tool tip message for this object
  void setTipText(const FXString& text){ tip=text; }

  /// Get the tool tip message for this object
  const FXString& getTipText() const { return tip; }

  /// Set the material for specified side (where side = 0 or 1)
  void setMaterial(FXint side,const FXMaterial &mtl);

  /// Get the material for specified side (where side = 0 or 1)
  void getMaterial(FXint side,FXMaterial &mtl) const;

  /// Save shape to a stream
  virtual void save(FXStream& store) const;

  /// Load shape from a stream
  virtual void load(FXStream& store);
  };

}

#endif

