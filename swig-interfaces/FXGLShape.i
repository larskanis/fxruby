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
class FXGLShape : public FXGLObject {
public:
  long onDNDDrop(FXObject*,FXSelector,void*);
  long onDNDMotion(FXObject*,FXSelector,void* PTR_EVENT);
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
  %extend {
    /// Construct with specified origin and options
    FXGLShape(FXfloat x,FXfloat y,FXfloat z,FXuint opts){
      return new FXRbGLShape(x,y,z,opts);
      }

    /// Construct with specified origin, options and front and back materials
    FXGLShape(FXfloat x,FXfloat y,FXfloat z,FXuint opts,const FXMaterial& front,const FXMaterial& back){
      return new FXRbGLShape(x,y,z,opts,front,back);
      }
    }

  %extend {
    /// Identify sub-object given path
    virtual FXGLObject* identify(FXuint* path,FXint n){
      return self->identify(path);
      }
    }

  /// Set the tool tip message for this object
  void setTipText(const FXString& text);

  /// Get the tool tip message for this object
  const FXString& getTipText() const;

  /// Set the material for specified side (where side = 0 or 1)
  void setMaterial(FXint side,const FXMaterial &mtl);

  %extend {
    // Get position
    FXVec3f getPosition() const {
      FXASSERT(self->isMemberOf(FXMETACLASS(FXRbGLShape)));
      return dynamic_cast<const FXRbGLShape*>(self)->getPosition();
      }

    // Set position
    void setPosition(const FXVec3f& pos) {
      FXASSERT(self->isMemberOf(FXMETACLASS(FXRbGLShape)));
      dynamic_cast<FXRbGLShape*>(self)->setPosition(pos);
      }

    // Get the material for specified side (where side = 0 or 1)
    FXMaterial getMaterial(FXint side) const {
      FXMaterial mtl;
      self->getMaterial(side, mtl);
      return mtl;
      }

    // Set the range for this shape
    void setRange(const FXRangef& box){
      FXASSERT(self->isMemberOf(FXMETACLASS(FXRbGLShape)));
      dynamic_cast<FXRbGLShape*>(self)->setRange(box);
      }
    }

  // Destructor
  virtual ~FXGLShape();
};


DECLARE_FXOBJECT_VIRTUALS(FXGLShape)
DECLARE_FXGLOBJECT_VIRTUALS(FXGLShape)
DECLARE_FXGLSHAPE_VIRTUALS(FXGLShape)

