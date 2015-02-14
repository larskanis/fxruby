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

/// Matrix packing options
enum {
  MATRIX_BY_ROWS        = 0,              /// Fixed number of rows, add columns as needed
  MATRIX_BY_COLUMNS     = 0x00020000      /// Fixed number of columns, adding rows as needed
  };


/**
* The Matrix layout manager automatically arranges its child windows
* in rows and columns.  If the matrix style is MATRIX_BY_ROWS, then
* the matrix will have the given number of rows and the number of columns
* grows as more child windows are added; if the matrix style is MATRIX_BY_COLUMNS,
* then the number of columns is fixed and the number of rows grows as more children
* are added.
* If all children in a row (column) have the LAYOUT_FILL_ROW (LAYOUT_FILL_COLUMN)
* hint set, then the row (column) will be stretchable as the matrix layout manager
* itself is resized.  If more than one row (column) is stretchable, the space is
* apportioned to each stretchable row (column) proportionally.
* Within each cell of the matrix, all other layout hints are observed.
* For example, a child having LAYOUT_CENTER_Y and LAYOUT_FILL_X hints will
* be centered in the Y-direction, while being stretched in the X-direction.
* Empty cells can be obtained by simply placing a borderless FXFrame widget
* as a space-holder.
*/
class FXMatrix : public FXPacker {
public:
  long onFocusUp(FXObject*,FXSelector,void* PTR_EVENT);
  long onFocusDown(FXObject*,FXSelector,void* PTR_EVENT);
  long onFocusLeft(FXObject*,FXSelector,void* PTR_EVENT);
  long onFocusRight(FXObject*,FXSelector,void* PTR_EVENT);
public:
  %extend {
    /// Construct a matrix layout manager with n rows or columns
    FXMatrix(FXComposite *p,FXint n=1,FXuint opts=MATRIX_BY_ROWS,FXint x=0,FXint y=0,FXint w=0,FXint h=0,FXint pl=DEFAULT_SPACING,FXint pr=DEFAULT_SPACING,FXint pt=DEFAULT_SPACING,FXint pb=DEFAULT_SPACING,FXint hs=DEFAULT_SPACING,FXint vs=DEFAULT_SPACING){
      return new FXRbMatrix(p,n,opts,x,y,w,h,pl,pr,pt,pb,hs,vs);
      }
    }

  /// Obtain the child placed at a certain row and column
  FXWindow* childAtRowCol(FXint r,FXint c) const;

  /// Return the row in which the given child is placed
  FXint rowOfChild(const FXWindow* child) const;

  /// Return the column in which the given child is placed
  FXint colOfChild(const FXWindow* child) const;

  /// Change the matrix style
  void setMatrixStyle(FXuint ph);

  /// Return the current matrix style
  FXuint getMatrixStyle() const;

  /// Change the number of rows
  void setNumRows(FXint nr);

  /// Return the number of rows
  FXint getNumRows() const;

  /// Change the number of columns
  void setNumColumns(FXint nc);

  /// Return the number of columns
  FXint getNumColumns() const;

  /// Destructor
  virtual ~FXMatrix();
  };


DECLARE_FXOBJECT_VIRTUALS(FXMatrix)
DECLARE_FXID_VIRTUALS(FXMatrix)
DECLARE_FXDRAWABLE_VIRTUALS(FXMatrix)
DECLARE_FXWINDOW_VIRTUALS(FXMatrix)

