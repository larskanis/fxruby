/***********************************************************************
 * FXRuby -- the Ruby language bindings for the FOX GUI toolkit.
 * Copyright (c) 2001 by J. Lyle Johnson. All Rights Reserved.
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

/// Gradient bar orientation
enum {
  GRADIENTBAR_HORIZONTAL      = 0,                          /// Gradient bar shown horizontally
  GRADIENTBAR_VERTICAL        = 0x00008000,                 /// Gradient bar shown vertically
  GRADIENTBAR_NO_CONTROLS     = 0,                          /// No controls shown
  GRADIENTBAR_CONTROLS_TOP    = 0x00010000,                 /// Controls on top
  GRADIENTBAR_CONTROLS_BOTTOM = 0x00020000,                 /// Controls on bottom
  GRADIENTBAR_CONTROLS_LEFT   = GRADIENTBAR_CONTROLS_TOP,   /// Controls on left
  GRADIENTBAR_CONTROLS_RIGHT  = GRADIENTBAR_CONTROLS_BOTTOM /// Controls on right
  };


/// Blend modes
enum {
  GRADIENT_BLEND_LINEAR,                /// Linear blend
  GRADIENT_BLEND_POWER,                 /// Power law blend
  GRADIENT_BLEND_SINE,                  /// Sine blend
  GRADIENT_BLEND_INCREASING,            /// Quadratic increasing blend
  GRADIENT_BLEND_DECREASING             /// Quadratic decreasing blend
  };



// Gradient segment
struct FXGradient {
  FXdouble lower;                     /// Lower value
  FXdouble middle;                    /// Middle value
  FXdouble upper;                     /// Upper value
  FXColor  lowerColor;                /// Lower color
  FXColor  upperColor;                /// Upper color
  FXuchar  blend;                     /// Blend method
  };

// Enforce segment numbers -1 <= sg < numSegments.
%typemap(check) FXint SEG {
  if ($1 < -1 || $1 >= arg1->getNumSegments()) {
    rb_raise(rb_eIndexError, "segment index %d out of bounds",$1);
  }
}

// Enforce segment numbers 0 <= sg < numSegments.
%typemap(check) FXint SEG0 {
  if ($1 < 0 || $1 >= arg1->getNumSegments()) {
    rb_raise(rb_eIndexError, "segment index %d out of bounds",$1);
  }
}

// Enforce segment numbers 1 <= sg < numSegments.
%typemap(check) FXint SEG1 {
  if ($1 < 1 || $1 >= arg1->getNumSegments()) {
    rb_raise(rb_eIndexError, "segment index %d out of bounds",$1);
  }
}

// Enforce segment numbers 0 <= sg < numSegments-1.
%typemap(check) FXint SEGNM1 {
  if ($1 < 0 || $1 >= arg1->getNumSegments()-1) {
    rb_raise(rb_eIndexError, "segment index %d out of bounds",$1);
  }
}

%rename("barSize=")     FXGradientBar::setBarSize(FXint);
%rename("barSize")      FXGradientBar::getBarSize() const;
%rename("controlSize=") FXGradientBar::setControlSize(FXint);
%rename("controlSize")  FXGradientBar::getControlSize() const;

/**
* The gradient bar is a control that is used to edit color gradient,
* such as used in texture mapping and shape filling.
*/
class FXGradientBar : public FXFrame {
public:
  long onPaint(FXObject*,FXSelector,void* PTR_EVENT);
  long onLeftBtnPress(FXObject*,FXSelector,void* PTR_EVENT);
  long onLeftBtnRelease(FXObject*,FXSelector,void* PTR_EVENT);
  long onMotion(FXObject*,FXSelector,void* PTR_EVENT);
  long onDNDEnter(FXObject*,FXSelector,void* PTR_EVENT);
  long onDNDLeave(FXObject*,FXSelector,void* PTR_EVENT);
  long onDNDMotion(FXObject*,FXSelector,void* PTR_EVENT);
  long onDNDDrop(FXObject*,FXSelector,void* PTR_EVENT);
  long onCmdBlending(FXObject*,FXSelector,void* PTR_IGNORE);
  long onUpdBlending(FXObject*,FXSelector,void* PTR_IGNORE);
  long onUpdSegColor(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdSegColor(FXObject*,FXSelector,void* PTR_IGNORE);
  long onUpdRecenter(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdRecenter(FXObject*,FXSelector,void* PTR_IGNORE);
  long onUpdSplit(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdSplit(FXObject*,FXSelector,void* PTR_IGNORE);
  long onUpdMerge(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdMerge(FXObject*,FXSelector,void* PTR_IGNORE);
  long onUpdUniform(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdUniform(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdSetHelp(FXObject*,FXSelector,void* PTR_STRING);
  long onCmdGetHelp(FXObject*,FXSelector,void* PTR_IGNORE); // FIXME
  long onCmdSetTip(FXObject*,FXSelector,void* PTR_STRING);
  long onCmdGetTip(FXObject*,FXSelector,void* PTR_IGNORE); // FIXME
  long onQueryHelp(FXObject*,FXSelector,void* PTR_IGNORE);
  long onQueryTip(FXObject*,FXSelector,void* PTR_IGNORE);
public:
  enum{
    ID_LOWER_COLOR=FXFrame::ID_LAST,
    ID_UPPER_COLOR,
    ID_BLEND_LINEAR,
    ID_BLEND_POWER,
    ID_BLEND_SINE,
    ID_BLEND_INCREASING,
    ID_BLEND_DECREASING,
    ID_RECENTER,
    ID_SPLIT,
    ID_MERGE,
    ID_UNIFORM,
    ID_LAST
    };
public:
  %extend {
    /// Construct a gradient bar
    FXGradientBar(FXComposite* p,FXObject* tgt=NULL,FXSelector sel=0,FXuint opts=FRAME_NORMAL,FXint x=0,FXint y=0,FXint w=0,FXint h=0,FXint pl=DEFAULT_PAD,FXint pr=DEFAULT_PAD,FXint pt=DEFAULT_PAD,FXint pb=DEFAULT_PAD){
      return new FXRbGradientBar(p,tgt,sel,opts,x,y,w,h,pl,pr,pt,pb);
      }
    }

  /**
   * Obtain segment containing location x, y.
   * Returns -1 if no matching segment was found.
   */
  FXint getSegment(FXint x,FXint y) const;

  /**
   * Get the grip in segment sg which is closest to location (x, y),
   * one of GRIP_LOWER, GRIP_SEG_LOWER, GRIP_MIDDLE, GRIP_SEG_UPPER,
   * GRIP_UPPER or GRIP_NONE.
   */
  FXint getGrip(FXint sg,FXint x,FXint y) const;

  /// Return the number of segments
  FXint getNumSegments() const;

  /**
   * Replace the current gradient segments.
   * The gradient bar makes a copy of the input segments array.
   */
  void setGradients(const FXGradient *segments,FXint nsegments); // FIXME

  /// Return the gradient segments
  void getGradients(FXGradient*& segments,FXint& nsegments) const; // FIXME

  /// Change current segment
  void setCurrentSegment(FXint SEG,FXbool notify=false);

  /// Return current segment, or -1 if there is no current segment
  FXint getCurrentSegment() const;

  /// Change anchor segment
  void setAnchorSegment(FXint SEG);

  /// Return anchor segment, if any
  FXint getAnchorSegment() const;

  %extend {
    /// Select segment(s)
    FXbool selectSegments(FXint fm,FXint to,FXbool notify=false){
      if(fm>to){
        rb_raise(rb_eArgError,"'from' index is greater than 'to' index");
        }
      if(fm<0 || to>=self->getNumSegments()){
        rb_raise(rb_eIndexError,"segment index out of bounds");
        }
      return self->selectSegments(fm,to,notify);
      }
  }

  // Deselect all segments
  FXbool deselectSegments(FXbool notify);

  /// Returns TRUE if the specified segment is selected
  FXbool isSegmentSelected(FXint SEG0) const;

  /// Set lower color of a segment
  void setSegmentLowerColor(FXint SEG0,FXColor clr,FXbool notify=false);
  
  /// Set upper color of a segment
  void setSegmentUpperColor(FXint SEG0,FXColor clr,FXbool notify=false);

  /// Get lower color of a segment
  FXColor getSegmentLowerColor(FXint SEG0) const;
  
  /// Get upper color of a segment
  FXColor getSegmentUpperColor(FXint SEG0) const;

  /// Move lower point of segment sg
  void moveSegmentLower(FXint SEG1,FXdouble val,FXbool notify=false);

  /// Move middle point of segment sg
  void moveSegmentMiddle(FXint SEG0,FXdouble val,FXbool notify=false);

  /// Move upper point of segment sg
  void moveSegmentUpper(FXint SEGNM1,FXdouble val,FXbool notify=false);

  /// Move segments sglo to sghi to new position val
  void moveSegments(FXint sglo,FXint sghi,FXdouble val,FXbool notify=false);

  /// Get lower value of segment sg
  FXdouble getSegmentLower(FXint SEG0) const;
  
  /// Get middle value of segment sg
  FXdouble getSegmentMiddle(FXint SEG0) const;
  
  /// Get upper value of segment sg
  FXdouble getSegmentUpper(FXint SEG0) const;

  %extend {
    /**
     * Get gradient ramp.
     * The ramp argument should be an array of size nramp, which will be
     * filled with the appropriate color values.
     */
    VALUE gradient(FXint nramp){
      FXColor* ramp;
      VALUE ary;
      FXint i;
      if(nramp>0){
        if(FXMALLOC(&ramp,FXColor,nramp)){
          self->gradient(ramp,nramp);
          ary=rb_ary_new2(nramp);
  	  for(i=0; i<nramp; i++){
	    rb_ary_store(ary,i,to_ruby(ramp[i]));
	    }
	  FXFREE(&ramp);
	  return ary;
	  }
        else{
          rb_raise(rb_eNoMemError,"");
          }
        }
      else{
        return rb_ary_new();
        }
    }
  }

  /**
   * Get blend mode of segment, one of GRADIENT_BLEND_LINEAR,
   * GRADIENT_BLEND_POWER, GRADIENT_BLEND_SINE, GRADIENT_BLEND_INCREASING,
   * or GRADIENT_BLEND_DECREASING.
   */
  FXuint getSegmentBlend(FXint SEG0) const;

  /// Split segment at the midpoint
  void splitSegments(FXint sglo,FXint sghi,FXbool notify=false);

  /// Merge segments
  void mergeSegments(FXint sglo,FXint sghi,FXbool notify=false);

  /// Make segments uniformly distributed
  void uniformSegments(FXint sglo,FXint sghi,FXbool notify=false);

  /// Change blend mode of segment
  void blendSegments(FXint sglo,FXint sghi,FXuint blend=GRADIENT_BLEND_LINEAR,FXbool notify=false);

  /// Change control size
  void setControlSize(FXint cs);
  
  /// Get control size
  FXint getControlSize() const;

  /// Change bar size
  void setBarSize(FXint bs);
  
  /// Get bar size
  FXint getBarSize() const;
  
  /// Get the gradient bar style
  FXuint getBarStyle() const;

  /// Change the gradient bar style
  void setBarStyle(FXuint style);

  /// Set color
  void setSelectColor(FXColor clr);

  /// Get color
  FXColor getSelectColor() const;

  /// Set status line help text for this gradient bar
  void setHelpText(const FXString& text);

  /// Get status line help text for this gradient bar
  const FXString& getHelpText() const;

  /// Set tool tip message for this gradient bar
  void setTipText(const FXString& text);

  /// Get tool tip message for this gradient bar
  const FXString& getTipText() const;

  /// Destructor
  virtual ~FXGradientBar();
  };

DECLARE_FXOBJECT_VIRTUALS(FXGradientBar)
DECLARE_FXID_VIRTUALS(FXGradientBar)
DECLARE_FXDRAWABLE_VIRTUALS(FXGradientBar)
DECLARE_FXWINDOW_VIRTUALS(FXGradientBar)


