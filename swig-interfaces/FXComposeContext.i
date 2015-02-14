/********************************************************************************
*                                                                               *
*                         C o m p o s e - C o n t e x t                         *
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
* $Id: FXComposeContext.i 2292 2005-12-06 02:22:28Z lyle $                   *
********************************************************************************/


/**
* Compose Context manages the state of an input method
* if input method support is enabled.
*/
class FXComposeContext : public FXId {
public:

  %extend {
    /// Construct compose context for given window
    FXComposeContext(FXApp* a,FXWindow* win=NULL,FXSelector sel=0){
      return new FXRbComposeContext(a,win,sel);
      }
  }

  /// Focus in
  void focusIn();

  /// Focus out
  void focusOut();

  /// Set the spot
  void setSpot(FXint x,FXint y);

  /// Set the area
  void setArea(FXint x,FXint y,FXint w,FXint h);

  /// Translate key event
  FXString translateEvent(FXRawEvent& event);

  /// Destructor
  virtual ~FXComposeContext();
  };

}

#endif
