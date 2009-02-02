/***********************************************************************
 * FXRuby -- the Ruby language bindings for the FOX GUI toolkit.
 * Copyright (c) 2001-2003 by J. Lyle Johnson. All Rights Reserved.
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
 * at "lyle@users.sourceforge.net".
 ***********************************************************************/

class FXDCPrint;
class FXGLObject;


// GL Viewer options
enum {
  VIEWER_LIGHTING    = 0x00008000,    /// Lighting is on
  VIEWER_FOG         = 0x00010000,    /// Fog mode on
  VIEWER_DITHER      = 0x00020000     /// Dithering
  };

  
/*******************************  Viewer  Structs  *****************************/
  

/// OpenGL Viewer Viewport
struct FXViewport {
  FXViewport();
  FXint      w,h;               // Viewport dimensions
  FXdouble   left,right;        // World box
  FXdouble   bottom,top;
  FXdouble   hither,yon;
  ~FXViewport();
  };


// OpenGL Light Source
struct FXLight {
  FXLight();
  FXVec4f    ambient;           // Ambient light color
  FXVec4f    diffuse;           // Diffuse light color
  FXVec4f    specular;          // Specular light color
  FXVec4f    position;          // Light position
  FXVec3f    direction;         // Spot direction
  FXfloat    exponent;          // Spotlight exponent
  FXfloat    cutoff;            // Spotlight cutoff angle
  FXfloat    c_attn;            // Constant attenuation factor
  FXfloat    l_attn;            // Linear attenuation factor
  FXfloat    q_attn;            // Quadratic attenuation factor
  ~FXLight();
  };


// OpenGL Material Description
struct FXMaterial {
  FXMaterial();
  FXVec4f    ambient;           // Ambient material color
  FXVec4f    diffuse;           // Diffuse material color
  FXVec4f    specular;          // Specular material color
  FXVec4f    emission;          // Emissive material color
  FXfloat    shininess;         // Specular shininess
  ~FXMaterial();
  };

  
// Feedback buffer sort routine
// typedef FXbool (*FXZSortFunc)(FXfloat*& buffer,FXint& used,FXint& size); FIXME

/********************************  Viewer  Class  ******************************/


/// Canvas, an area drawn by another object
class FXGLViewer : public FXGLCanvas {
protected:
  FXViewport      wvt;              // Window viewport transform
  FXMat4f         transform;        // Current transformation matrix
  FXMat4f         itransform;       // Inverse of current transformation matrix
  FXuint          projection;       // Projection mode
  FXQuatf         rotation;         // Viewer orientation
  FXdouble        fov;              // Field of view
  FXdouble        zoom;             // Zoom factor
  FXVec3f         center;           // Model center
  FXVec3f         scale;            // Model scale
  FXdouble        worldpx;          // Pixel size in world
  FXdouble        modelpx;          // Pixel size in model
  FXint           maxhits;          // Maximum number of hits
  FXdouble        ax,ay;            // Quick view->world coordinate mapping
  FXdouble        diameter;         // Size of model diameter ( always > 0)
  FXdouble        distance;         // Distance of PRP to target
  FXVec4f         background[2];    // Background colors
  FXVec4f         ambient;          // Global ambient light
  FXLight         light;            // Light source
  FXMaterial      material;         // Base material properties
  FXint           dial[3];          // Dial positions
  FXString        help;             // Status help
  FXString        tip;              // Tooltip for background
  FXGLObject     *dropped;          // Object being dropped on
  FXGLObject     *selection;        // Current object
  FXZSortFunc     zsortfunc;        // Routine to sort feedback buffer
  FXGLObject     *scene;            // What we're looking at
  FXbool          doesturbo;        // Doing turbo mode
  FXbool          turbomode;        // Turbo mode
  FXuchar         mode;             // Mode the widget is in
public:

  // Common DND types
  static FXDragType objectType;     // GL Object type

protected:

  // Mouse actions when in viewing window
  enum {
    HOVERING,                       // Hovering mouse w/o doing anything
    PICKING,                        // Pick mode
    ROTATING,                       // Rotating camera around target
    POSTING,                        // Posting right-mouse menu
    TRANSLATING,                    // Translating camera
    ZOOMING,                        // Zooming
    FOVING,                         // Change field-of-view
    DRAGGING,                       // Dragging objects
    TRUCKING,                       // Trucking camera
    GYRATING,                       // Rotation of camera around eye
    DO_LASSOSELECT,                 // Lasso select when mouse pressed
    LASSOSELECT,                    // Anchor of lasso rectangle
    DO_LASSOZOOM,                   // Zoom when mouse pressed
    LASSOZOOM                       // Zoom rectangle
    };

protected:
  FXGLViewer();
  void glsetup();
  virtual void updateProjection();
  virtual void updateTransform();
  FXVec3fspherePoint(FXint px,FXint py);
  FXQuatf turn(FXint fx,FXint fy,FXint tx,FXint ty);
  void drawWorld(FXViewport& wv);
  void drawAnti(FXViewport& wv);
  void drawLasso(FXint x0,FXint y0,FXint x1,FXint y1);
  // FXint selectHits(FXuint*& hits,FXint& nhits,FXint x,FXint y,FXint w,FXint h);
  FXint renderFeedback(FXfloat *buffer,FXint x,FXint y,FXint w,FXint h,FXint maxbuffer);
  void drawFeedback(FXDCPrint& pdc,const FXfloat* buffer,FXint used);
  virtual FXGLObject* processHits(FXuint *pickbuffer,FXint nhits);
  void setOp(FXuint o);
public:

  // Events
  long onPaint(FXObject*,FXSelector,void* PTR_IGNORE);
  long onEnter(FXObject*,FXSelector,void* PTR_EVENT);
  long onLeave(FXObject*,FXSelector,void* PTR_EVENT);
  long onMotion(FXObject*,FXSelector,void* PTR_EVENT);
  long onMouseWheel(FXObject*,FXSelector,void* PTR_EVENT);
  long onChanged(FXObject*,FXSelector,void* PTR_GLOBJECT);
  long onPick(FXObject*,FXSelector,void* PTR_GLOBJECT); // FIXME
  long onClicked(FXObject*,FXSelector,void* PTR_GLOBJECT);
  long onDoubleClicked(FXObject*,FXSelector,void* PTR_GLOBJECT);
  long onTripleClicked(FXObject*,FXSelector,void* PTR_GLOBJECT);
  long onLassoed(FXObject*,FXSelector,void* PTR_EVENT);
  long onSelected(FXObject*,FXSelector,void* PTR_IGNORE); // FIXME
  long onDeselected(FXObject*,FXSelector,void* PTR_IGNORE); // FIXME
  long onInserted(FXObject*,FXSelector,void* PTR_IGNORE); // FIXME
  long onDeleted(FXObject*,FXSelector,void* PTR_IGNORE); // FIXME
  long onLeftBtnPress(FXObject*,FXSelector,void* PTR_EVENT);
  long onLeftBtnRelease(FXObject*,FXSelector,void* PTR_EVENT);
  long onMiddleBtnPress(FXObject*,FXSelector,void* PTR_EVENT);
  long onMiddleBtnRelease(FXObject*,FXSelector,void* PTR_EVENT);
  long onRightBtnPress(FXObject*,FXSelector,void* PTR_EVENT);
  long onRightBtnRelease(FXObject*,FXSelector,void* PTR_EVENT);
  long onUngrabbed(FXObject*,FXSelector,void* PTR_EVENT);
  long onKeyPress(FXObject*,FXSelector,void* PTR_EVENT);
  long onKeyRelease(FXObject*,FXSelector,void* PTR_EVENT);
  long onFocusIn(FXObject*,FXSelector,void* PTR_EVENT);
  long onFocusOut(FXObject*,FXSelector,void* PTR_EVENT);
  long onClipboardLost(FXObject*,FXSelector,void* PTR_EVENT);
  long onClipboardGained(FXObject*,FXSelector,void* PTR_EVENT);
  long onClipboardRequest(FXObject*,FXSelector,void* PTR_EVENT);

  // Commands
  long onCmdPerspective(FXObject*,FXSelector,void* PTR_IGNORE);
  long onUpdPerspective(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdParallel(FXObject*,FXSelector,void* PTR_IGNORE);
  long onUpdParallel(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdFront(FXObject*,FXSelector,void* PTR_IGNORE);
  long onUpdFront(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdBack(FXObject*,FXSelector,void* PTR_IGNORE);
  long onUpdBack(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdLeft(FXObject*,FXSelector,void* PTR_IGNORE);
  long onUpdLeft(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdRight(FXObject*,FXSelector,void* PTR_IGNORE);
  long onUpdRight(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdTop(FXObject*,FXSelector,void* PTR_IGNORE);
  long onUpdTop(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdBottom(FXObject*,FXSelector,void* PTR_IGNORE);
  long onUpdBottom(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdResetView(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdFitView(FXObject*,FXSelector,void* PTR_IGNORE);
  long onDNDEnter(FXObject*,FXSelector,void* PTR_EVENT);
  long onDNDLeave(FXObject*,FXSelector,void* PTR_EVENT);
  long onDNDMotion(FXObject*,FXSelector,void* PTR_EVENT);
  long onDNDDrop(FXObject*,FXSelector,void* PTR_EVENT);
  long onTipTimer(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdXYZDial(FXObject*,FXSelector,void* PTR_INT);
  long onUpdXYZDial(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdRollPitchYaw(FXObject*,FXSelector,void* PTR_IGNORE);
  long onUpdRollPitchYaw(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdXYZScale(FXObject*,FXSelector,void* PTR_IGNORE);
  long onUpdXYZScale(FXObject*,FXSelector,void* PTR_IGNORE);
  long onUpdCurrent(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdCutSel(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdCopySel(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdPasteSel(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdDeleteSel(FXObject*,FXSelector,void* PTR_IGNORE);
  long onUpdDeleteSel(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdBackColor(FXObject*,FXSelector,void* PTR_COLOR);
  long onUpdBackColor(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdGradientBackColor(FXObject*,FXSelector,void* PTR_COLOR);
  long onUpdGradientBackColor(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdAmbientColor(FXObject*,FXSelector,void* PTR_COLOR);
  long onUpdAmbientColor(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdLighting(FXObject*,FXSelector,void* PTR_IGNORE);
  long onUpdLighting(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdFog(FXObject*,FXSelector,void* PTR_IGNORE);
  long onUpdFog(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdDither(FXObject*,FXSelector,void* PTR_IGNORE);
  long onUpdDither(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdFov(FXObject*,FXSelector,void* PTR_IGNORE);
  long onUpdFov(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdZoom(FXObject*,FXSelector,void* PTR_IGNORE);
  long onUpdZoom(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdLightAmbient(FXObject*,FXSelector,void* PTR_COLOR);
  long onUpdLightAmbient(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdLightDiffuse(FXObject*,FXSelector,void* PTR_COLOR);
  long onUpdLightDiffuse(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdLightSpecular(FXObject*,FXSelector,void* PTR_COLOR);
  long onUpdLightSpecular(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdTurbo(FXObject*,FXSelector,void* PTR_IGNORE);
  long onUpdTurbo(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdPrintImage(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdPrintVector(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdLassoZoom(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdLassoSelect(FXObject*,FXSelector,void* PTR_IGNORE);
  long onQueryHelp(FXObject*,FXSelector,void* PTR_IGNORE);
  long onQueryTip(FXObject*,FXSelector,void* PTR_IGNORE); // FIXME

public:
  
  // Projection modes
  enum {
    PARALLEL,		  // Parallel projection
    PERSPECTIVE		  // Perspective projection
    };

  // Messages
  enum {
    ID_PERSPECTIVE=FXGLCanvas::ID_LAST,
    ID_PARALLEL,
    ID_FRONT,
    ID_BACK,
    ID_LEFT,
    ID_RIGHT,
    ID_TOP,
    ID_BOTTOM,
    ID_RESETVIEW,
    ID_FITVIEW,
    ID_TOP_COLOR,
    ID_BOTTOM_COLOR,
    ID_BACK_COLOR,    
    ID_AMBIENT_COLOR,
    ID_LIGHT_AMBIENT,
    ID_LIGHT_DIFFUSE,
    ID_LIGHT_SPECULAR,
    ID_LIGHTING,
    ID_TURBO,
    ID_FOG,
    ID_DITHER,
    ID_SCALE_X,
    ID_SCALE_Y,
    ID_SCALE_Z,
    ID_DIAL_X,
    ID_DIAL_Y,
    ID_DIAL_Z,
    ID_ROLL,
    ID_PITCH,
    ID_YAW,
    ID_FOV,
    ID_ZOOM,
    ID_CUT_SEL,
    ID_COPY_SEL,
    ID_PASTE_SEL,
    ID_DELETE_SEL,
    ID_PRINT_IMAGE,
    ID_PRINT_VECTOR,
    ID_LASSO_ZOOM,
    ID_LASSO_SELECT,
    ID_LAST
    };

public:

  // Common DND type names
  %extend {
    static VALUE objectTypeName(){
      return to_ruby(FXGLViewer::objectTypeName);
      }
  }

public:
  %extend {
    /// Construct GL viewer widget
    FXGLViewer(FXComposite* p,FXGLVisual *vis,FXObject* tgt=NULL,FXSelector sel=0,FXuint opts=0,FXint x=0,FXint y=0,FXint w=0,FXint h=0){
      return new FXRbGLViewer(p,vis,tgt,sel,opts,x,y,w,h);
      }
  
    /// Construct GL viewer widget sharing display list with another GL viewer
    FXGLViewer(FXComposite* p,FXGLVisual *vis,FXGLViewer* sharegroup,FXObject* tgt=NULL,FXSelector sel=0,FXuint opts=0,FXint x=0,FXint y=0,FXint w=0,FXint h=0){
      return new FXRbGLViewer(p,vis,sharegroup,tgt,sel,opts,x,y,w,h);
      }
    }

  /// Return size of pixel in world coordinates
  FXdouble worldPix() const;

  /// Return size of pixel in model coordinates
  FXdouble modelPix() const;

  %extend {
    // Return a list of all objects in the given rectangle
    VALUE lasso(FXint x1,FXint y1,FXint x2,FXint y2) {
      VALUE objects = rb_ary_new();
      FXGLObject** items = self->lasso(x1, y1, x2, y2);
      if (items) {
        register FXGLObject** p = items;
        while (*p) {
          rb_ary_push(objects, to_ruby(*p));
          p++;
        }
        FXFREE(&items);
      }
      return objects;
    }
  }

  /// Fit viewer to the given bounding box
  FXbool fitToBounds(const FXRangef& box);
  
  %extend {
    /// Return the viewer's viewport
    FXViewport getViewport() const {
      FXViewport v;
      self->getViewport(v);
      return v;
    }
  }
  
  %extend {
    /// Translate eye-coordinate to screen coordinate
    VALUE eyeToScreen(FXVec3f e) {
      FXint sx, sy;
      self->eyeToScreen(sx, sy, e);
      VALUE point = rb_ary_new();
      rb_ary_push(point, INT2NUM(sx));
      rb_ary_push(point, INT2NUM(sy));
      return point;
    }
  }

  /// Translate screen coordinate to eye coordinate at the given depth
  FXVec3f screenToEye(FXint sx,FXint sy,FXfloat eyez=0.0);
  
  /// Translate screen coordinate to eye coordinate at the target point depth
  FXVec3f screenToTarget(FXint sx,FXint sy);
  
  /// Translate world coordinate to eye coordinate
  FXVec3f worldToEye(FXVec3f w);
  
  /// Translate world coordinate to eye coordinate depth
  FXfloat worldToEyeZ(FXVec3f w);
  
  /// Translate eye coordinate to eye coordinate
  FXVec3f eyeToWorld(FXVec3f e); 
  
  /// Calculate world coordinate vector from screen movement
  FXVec3f worldVector(FXint fx,FXint fy,FXint tx,FXint ty);
  
  ///  Change default object material setting
  void setMaterial(const FXMaterial &mtl);
  
  %extend {
    /// Return default object material setting
    FXMaterial getMaterial() const {
      FXMaterial mtl;
      self->getMaterial(mtl);
      return mtl;
    }
  }
  
  /// Change camera field of view angle (in degrees)
  void setFieldOfView(FXdouble fv);
  
  /// Return camera field of view angle
  FXdouble getFieldOfView() const { return fov; }

  /// Change camera zoom factor
  void setZoom(FXdouble zm);
  
  /// Return camera zoom factor
  FXdouble getZoom() const;

  /// Change target point distance
  void setDistance(FXdouble ed);
  
  /// Return target point distance
  FXdouble getDistance() const;

  /// Change unequal model scaling factors
  void setScale(FXVec3f s);
  
  /// Return current scaling factors
  const FXVec3f& getScale() const;

  /// Change camera orientation from quaternion
  void setOrientation(FXQuatf rot);
  
  /// Return current camera orientation quaternion
  const FXQuatf& getOrientation() const;

  /// Change object center (tranlation)
  void setCenter(FXVec3f cntr);
  
  /// Return object center
  const FXVec3f& getCenter() const;

  /// Translate object center
  void translate(FXVec3f vec);
  
  %extend {
    /// Return boresight vector (an array of two arrays)
    VALUE getBoreVector(FXint sx,FXint sy) {
      FXVec3f point, dir;
      self->getBoreVector(sx, sy, point, dir);

      VALUE pointArray = rb_ary_new();
      rb_ary_push(pointArray, rb_float_new(point[0]));
      rb_ary_push(pointArray, rb_float_new(point[1]));
      rb_ary_push(pointArray, rb_float_new(point[2]));

      VALUE dirArray = rb_ary_new();
      rb_ary_push(dirArray, rb_float_new(dir[0]));
      rb_ary_push(dirArray, rb_float_new(dir[1]));
      rb_ary_push(dirArray, rb_float_new(dir[2]));

      VALUE results = rb_ary_new();
      rb_ary_push(results, pointArray);
      rb_ary_push(results, dirArray);

      return results;
    }
  }

  /// Return eyesight vector
  FXVec3f getEyeVector() const;
  
  /// Return eye position 
  FXVec3f getEyePosition() const;
  
  /// Change help text
  void setHelpText(const FXString& text);
  
  /// Return help text
  const FXString& getHelpText() const;

  /// Change tip text
  void setTipText(const FXString& text);
  
  /// Return tip text
  const FXString& getTipText() const;

  /// Return the current transformation matrix
  const FXMat4f& getTransform() const;

  /// Return the inverse of the current transformation matrix
  const FXMat4f& getInvTransform() const;

  /// Change the scene, i.e. the object being displayed.
  void setScene(FXGLObject* sc);
  
  /// Return the current scene object
  FXGLObject* getScene() const;

  /// Change selection
  void setSelection(FXGLObject* sel);

  /// Returns the selection
  FXGLObject* getSelection() const;

  /// Change the projection mode, PERSPECTIVE or PARALLEL
  void setProjection(FXuint proj);
  
  /// Return the projection mode
  FXuint getProjection() const;

  /// Change top or bottom or both background colors
  void setBackgroundColor(const FXVec4f& clr,FXbool bottom=MAYBE);
 
  /// Return top or bottom window background color.
  const FXVec4f& getBackgroundColor(FXbool bottom=FALSE) const;

  /// Change global ambient light color
  void setAmbientColor(const FXVec4f& clr);
  
  /// Return global ambient light color
  const FXVec4f& getAmbientColor() const;

#ifdef SWIGRUBY
  %extend {
    /**
     * Read the pixels off the screen as array of FXColor;
     * this array can be directly passed to fxsaveBMP and other image
     * output routines.
     */
    VALUE readPixels(FXint x,FXint y,FXint w,FXint h){
      FXColor *buffer;
      VALUE pixels=Qnil;
      if(self->readPixels(buffer,x,y,w,h)){
	pixels=FXRbMakeColorArray(buffer,w,h);
	FXFREE(&buffer);
	}
      return pixels;
      }
  
    /**
     * Read the feedback buffer containing the current scene, returning used 
     * and allocated size.
     */
    VALUE readFeedback(FXint x,FXint y,FXint w,FXint h){
      FXfloat *buffer;
      FXint used, size;
      if (self->readFeedback(buffer,used,size,x,y,w,h)){
	VALUE results=rb_ary_new();
	for(FXint i=0;i<used;i++) rb_ary_push(results,rb_float_new(buffer[i]));
	FXFREE(&buffer);
	return results;
        }
      else{
	return Qnil;
        }
      }
  }
#else
  %extend {
    PyObject *readPixels(FXint x,FXint y,FXint w,FXint h) {
      FXuchar *buffer;
      if(self->readPixels(buffer,x,y,w,h)){
	char *charBuffer;
	FXint nbytes=3*w*h;
	if(FXMALLOC(&charBuffer,char,nbytes)){
	  memcpy((void*)charBuffer,(void*)buffer,nbytes);
	  FXFREE(&buffer);
          FXbool doSave=FXPyRestoreThread();
	  PyObject *result=PyString_FromString(charBuffer);
          FXPySaveThread(doSave);
	  FXFREE(&charBuffer);
	  return result;
          }
	else{
	  FXFREE(&buffer);
          FXbool doSave=FXPyRestoreThread();
          PyErr_SetString(PyExc_MemoryError,"out of memory");
          FXPySaveThread(doSave);
	  return NULL;
	  }
        }
      else{
        FXbool doSave=FXPyRestoreThread();
        PyErr_SetString(PyExc_MemoryError,"out of memory");
        FXPySaveThread(doSave);
	return NULL;
        }
      }

    PyObject *readFeedback(FXint x,FXint y,FXint w,FXint h) {
      FXfloat *buffer;
      FXint used,size;
      if(self->readFeedback(buffer,used,size,x,y,w,h)){
        FXbool doSave=FXPyRestoreThread();
	PyObject *list=PyList_New(used);
	if(!list){
	  FXFREE(&buffer);
          FXPySaveThread(doSave);
	  return NULL;
	  }
	for(FXint i=0;i<used;i++){
	  PyObject *flt=PyFloat_FromDouble(buffer[i]);
	  if(!flt){
	    FXFREE(&buffer);
	    Py_DECREF(list);
            FXPySaveThread(doSave);
	    return NULL;
	    }
	  PyList_SetItem(list,i,flt);
	  }
        FXPySaveThread(doSave);
	FXFREE(&buffer);
	return list;
	}
      else{
        PyErr_SetString(PyExc_MemoryError,"out of memory");
	return NULL;
	}
      }
  }
#endif
  
#ifdef SWIGRUBY
  /**
  * Change hidden-surface feedback buffer sorting algorithm.
  * This can be used for move/draw printed output depth sorting.
  */  
  %extend {
    void setZSortFunc(VALUE proc){
      }
  }
#endif

#ifdef SWIGRUBY
  /// Return hidden surface sorting function.
  %extend {
    VALUE getZSortFunc() const {
      return Qnil;
      }
  }
#endif

  /** 
  * Change the maximum hits, i.e. the maximum size of the pick buffer.
  * When set to less than or equal to zero, picking is essentially turned off.
  */
  void setMaxHits(FXint maxh);

  /// Return maximum pickbuffer size
  FXint getMaxHits() const;

  /**
  * When drawing a GL object, if doesTurbo() is true, the object
  * may choose to perform a reduced complexity drawing as the user is
  * interactively manipulating; another update will be done later when
  * the full complexity drawing can be performed again.
  */
  FXbool doesTurbo() const;

  /// Return turbo mode setting
  FXbool getTurboMode() const;

  /// Set turbo mode
  void setTurboMode(FXbool turbo=TRUE);
  
  %extend {
    // Return light source settings
    FXLight getLight() const {
      FXLight lite;
      self->getLight(lite);
      return lite;
    }
  }
  
  /// Change light source settings
  void setLight(const FXLight& lite);

  /// Destructor
  virtual ~FXGLViewer();
  };


DECLARE_FXOBJECT_VIRTUALS(FXGLViewer)
DECLARE_FXID_VIRTUALS(FXGLViewer)
DECLARE_FXDRAWABLE_VIRTUALS(FXGLViewer)
DECLARE_FXWINDOW_VIRTUALS(FXGLViewer)
DECLARE_FXGLCANVAS_VIRTUALS(FXGLViewer)
DECLARE_FXGLVIEWER_VIRTUALS(FXGLViewer)

