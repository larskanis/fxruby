/********************************************************************************
*                                                                               *
*                      G r a d i e n t B a r   W i d g e t                      *
*                                                                               *
*********************************************************************************
* Copyright (C) 2002,2005 by Jeroen van der Zijp.   All Rights Reserved.        *
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
* $Id: FXGradientBar.h 2127 2005-08-07 20:21:35Z lyle $                     *
********************************************************************************/
#ifndef FXGRADIENTBAR_H
#define FXGRADIENTBAR_H

#ifndef FXFRAME_H
#include "FXFrame.h"
#endif


namespace FX {



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


class FXImage;


/**
* The gradient bar is a control that is used to edit color gradient,
* such as used in texture mapping and shape filling.
*/
class FXAPI FXGradientBar : public FXFrame {
  FXDECLARE(FXGradientBar)
protected:
  FXImage     *bar;                     // Image containing colors
  FXGradient  *seg;                     // Segments
  FXint        nsegs;                   // Number of segments
  FXint        sellower;                // Lower selected segment
  FXint        selupper;                // Upper selected segment
  FXint        dropped;                 // Dropped segment
  FXint        current;                 // Current segment
  FXint        anchor;                  // Anchor segment
  FXint        grip;                    // Grip being dragged, if any
  FXint        where;                   // Where dropped in segment
  FXString     tip;                     // Tooltip value
  FXString     help;                    // Help value
  FXColor      selectColor;             // Select color
  FXint        offset;                  // Offset
protected:
  FXGradientBar();
  void updatebar();
  FXdouble getValue(FXint x,FXint y) const;
  FXint getSegmentLowerPos(FXint sg) const;
  FXint getSegmentUpperPos(FXint sg) const;
  FXint getSegmentMiddlePos(FXint sg) const;
  void drawUpArrow(FXDCWindow& dc,FXint x,FXint y,FXColor clr);
  void drawDnArrow(FXDCWindow& dc,FXint x,FXint y,FXColor clr);
  void drawRtArrow(FXDCWindow& dc,FXint x,FXint y,FXColor clr);
  void drawLtArrow(FXDCWindow& dc,FXint x,FXint y,FXColor clr);
  void drawBottomArrows(FXDCWindow& dc,FXint x,FXint y,FXint w,FXint h);
  void drawTopArrows(FXDCWindow& dc,FXint x,FXint y,FXint w,FXint h);
  void drawLeftArrows(FXDCWindow& dc,FXint x,FXint y,FXint w,FXint h);
  void drawRightArrows(FXDCWindow& dc,FXint x,FXint y,FXint w,FXint h);
  static FXdouble blendlinear(FXdouble middle,FXdouble pos);
  static FXdouble blendpower(FXdouble middle,FXdouble pos);
  static FXdouble blendsine(FXdouble middle,FXdouble pos);
  static FXdouble blendincreasing(FXdouble middle,FXdouble pos);
  static FXdouble blenddecreasing(FXdouble middle,FXdouble pos);
private:
  FXGradientBar(const FXGradientBar&);
  FXGradientBar &operator=(const FXGradientBar&);
public:
  enum {
    GRIP_NONE,
    GRIP_LOWER,
    GRIP_SEG_LOWER,
    GRIP_MIDDLE,
    GRIP_SEG_UPPER,
    GRIP_UPPER
    };
public:
  long onPaint(FXObject*,FXSelector,void*);
  long onLeftBtnPress(FXObject*,FXSelector,void*);
  long onLeftBtnRelease(FXObject*,FXSelector,void*);
  long onMotion(FXObject*,FXSelector,void*);
  long onDNDEnter(FXObject*,FXSelector,void*);
  long onDNDLeave(FXObject*,FXSelector,void*);
  long onDNDMotion(FXObject*,FXSelector,void*);
  long onDNDDrop(FXObject*,FXSelector,void*);
  long onCmdBlending(FXObject*,FXSelector,void*);
  long onUpdBlending(FXObject*,FXSelector,void*);
  long onUpdSegColor(FXObject*,FXSelector,void*);
  long onCmdSegColor(FXObject*,FXSelector,void*);
  long onUpdRecenter(FXObject*,FXSelector,void*);
  long onCmdRecenter(FXObject*,FXSelector,void*);
  long onUpdSplit(FXObject*,FXSelector,void*);
  long onCmdSplit(FXObject*,FXSelector,void*);
  long onUpdMerge(FXObject*,FXSelector,void*);
  long onCmdMerge(FXObject*,FXSelector,void*);
  long onUpdUniform(FXObject*,FXSelector,void*);
  long onCmdUniform(FXObject*,FXSelector,void*);
  long onCmdSetHelp(FXObject*,FXSelector,void*);
  long onCmdGetHelp(FXObject*,FXSelector,void*);
  long onCmdSetTip(FXObject*,FXSelector,void*);
  long onCmdGetTip(FXObject*,FXSelector,void*);
  long onQueryHelp(FXObject*,FXSelector,void*);
  long onQueryTip(FXObject*,FXSelector,void*);
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

  /// Construct a gradient bar
  FXGradientBar(FXComposite* p,FXObject* tgt=NULL,FXSelector sel=0,FXuint opts=FRAME_NORMAL,FXint x=0,FXint y=0,FXint w=0,FXint h=0,FXint pl=DEFAULT_PAD,FXint pr=DEFAULT_PAD,FXint pt=DEFAULT_PAD,FXint pb=DEFAULT_PAD);

  /// Create server-side resources
  virtual void create();

  /// Perform layout
  virtual void layout();

  /// Return default width
  virtual FXint getDefaultWidth();

  /// Return default height
  virtual FXint getDefaultHeight();

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
  FXint getNumSegments() const { return nsegs; }

  /**
   * Replace the current gradient segments.
   * The gradient bar makes a copy of the input segments array.
   */
  void setGradients(const FXGradient *segments,FXint nsegments);

  /**
   * Return a copy of the gradient segments.
   * The array of segments is allocated using FXMALLOC and should be freed
   * by the caller using FXFREE.
   */
  void getGradients(FXGradient*& segments,FXint& nsegments) const;

  /// Change current segment
  void setCurrentSegment(FXint index,FXbool notify=FALSE);

  /// Return current segment, or -1 if there is no current segment
  FXint getCurrentSegment() const { return current; }

  /// Change anchor segment
  void setAnchorSegment(FXint index);

  /// Return anchor segment, or -1 if there is no anchor segment
  FXint getAnchorSegment() const { return anchor; }

  /// Select segment(s)
  FXbool selectSegments(FXint fm,FXint to,FXbool notify=FALSE);

  /// Deselect all segments
  FXbool deselectSegments(FXbool notify);

  /// Returns TRUE if the specified segment is selected
  FXbool isSegmentSelected(FXint s) const;

  /// Set lower color of a segment
  void setSegmentLowerColor(FXint s,FXColor clr,FXbool notify=FALSE);

  /// Set upper color of a segment
  void setSegmentUpperColor(FXint s,FXColor clr,FXbool notify=FALSE);

  /// Get lower color of a segment
  FXColor getSegmentLowerColor(FXint s) const;

  /// Get upper color of a segment
  FXColor getSegmentUpperColor(FXint s) const;

  /// Move lower point of segment sg
  void moveSegmentLower(FXint sg,FXdouble val,FXbool notify=FALSE);

  /// Move middle point of segment sg
  void moveSegmentMiddle(FXint sg,FXdouble val,FXbool notify=FALSE);

  /// Move upper point of segment sg
  void moveSegmentUpper(FXint sg,FXdouble val,FXbool notify=FALSE);

  /// Move segments sglo to sghi to new position val
  void moveSegments(FXint sglo,FXint sghi,FXdouble val,FXbool notify=FALSE);

  /// Get lower value of segment sg
  FXdouble getSegmentLower(FXint sg) const;

  /// Get middle value of segment sg
  FXdouble getSegmentMiddle(FXint sg) const;

  /// Get upper value of segment sg
  FXdouble getSegmentUpper(FXint sg) const;

  /**
   * Get gradient ramp.
   * The ramp argument should be an array of size nramp, which will be
   * filled with the appropriate color values.
   */
  void gradient(FXColor *ramp,FXint nramp);

  /**
   * Get blend mode of segment, one of GRADIENT_BLEND_LINEAR,
   * GRADIENT_BLEND_POWER, GRADIENT_BLEND_SINE, GRADIENT_BLEND_INCREASING,
   * or GRADIENT_BLEND_DECREASING.
   */
  FXuint getSegmentBlend(FXint s) const;

  /// Split segment at the midpoint
  void splitSegments(FXint sglo,FXint sghi,FXbool notify=FALSE);

  /// Merge segments
  void mergeSegments(FXint sglo,FXint sghi,FXbool notify=FALSE);

  /// Make segments uniformly distributed
  void uniformSegments(FXint sglo,FXint sghi,FXbool notify=FALSE);

  /// Change blend mode of segment
  void blendSegments(FXint sglo,FXint sghi,FXuint blend=GRADIENT_BLEND_LINEAR,FXbool notify=FALSE);

  /// Get the gradient bar style
  FXuint getBarStyle() const;

  /// Change the gradient bar style
  void setBarStyle(FXuint style);

  /// Set color
  void setSelectColor(FXColor clr);

  /// Get color
  FXColor getSelectColor() const { return selectColor; }

  /// Set status line help text for this gradient bar
  void setHelpText(const FXString& text){ help=text; }

  /// Get status line help text for this gradient bar
  const FXString& getHelpText() const { return help; }

  /// Set tool tip message for this gradient bar
  void setTipText(const FXString& text){ tip=text; }

  /// Get tool tip message for this gradient bar
  const FXString& getTipText() const { return tip; }

  /// Save gradient bar to a stream
  virtual void save(FXStream& store) const;

  /// Load gradient bar from a stream
  virtual void load(FXStream& store);

  /// Destructor
  virtual ~FXGradientBar();
  };


}

#endif
