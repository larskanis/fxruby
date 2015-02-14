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

/**
* Main application window.  There may be any number of
* MainWindows in an application.
* When a MainWindow is closed, it sends a SEL_CLOSE message to
* its target; the target should return 0 if there is no objection
* against proceeding with the close, and 1 otherwise.
* After the SEL_CLOSE message has been sent and no objection was
* raised, the MainWindow will delete itself.
*/
class FXMainWindow : public FXTopWindow {
public:
  %extend {
    /// Construct a main window
    FXMainWindow(FXApp* APP,const FXString& name,FXIcon *ic=NULL,FXIcon *mi=NULL,FXuint opts=DECOR_ALL,FXint x=0,FXint y=0,FXint w=0,FXint h=0,FXint pl=0,FXint pr=0,FXint pt=0,FXint pb=0,FXint hs=0,FXint vs=0){
      return new FXRbMainWindow(APP,name,ic,mi,opts,x,y,w,h,pl,pr,pt,pb,hs,vs);
      }
    }

  /// Destructor
  virtual ~FXMainWindow();
  };


DECLARE_FXOBJECT_VIRTUALS(FXMainWindow)
DECLARE_FXID_VIRTUALS(FXMainWindow)
DECLARE_FXDRAWABLE_VIRTUALS(FXMainWindow)
DECLARE_FXWINDOW_VIRTUALS(FXMainWindow)
DECLARE_FXTOPWINDOW_VIRTUALS(FXMainWindow)

