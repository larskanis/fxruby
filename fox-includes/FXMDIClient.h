/********************************************************************************
*                                                                               *
*         M u l t i p l e   D o c u m e n t   C l i e n t   W i n d o w         *
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
* $Id: FXMDIClient.h 2127 2005-08-07 20:21:35Z lyle $                       *
********************************************************************************/
#ifndef FXMDICLIENT_H
#define FXMDICLIENT_H

#ifndef FXCOMPOSITE_H
#include "FXComposite.h"
#endif

namespace FX {


class FXMDIChild;


/**
* The MDI client window manages a number of MDI child windows in a multiple-document
* interface (MDI) application. MDI child windows usually receive messages from the GUI controls
* by delegation via the MDI client.  This is accomplished by making the MDI client window
* the target for most GUI controls.  The MDI client filters out messages intented for itself,
* and delegates the remaining messages to its currently active MDI child, if any.
* If you use the auto-gray or auto-hide feature available in some GUI controls, these
* controls can be automatically grayed out or hidden when there is no active MDI child.
* When delegating messages via MDI client to MDI child windows of different types, care
* should be taken that message ID's do not overlap, so that all message ID's only map to
* the intented handlers no matter which MDI child window type is active.
* The MDI client sends a SEL_CHANGED message to its target when the active MDI child is
* switched, with the void* pointer refering to the new MDI child.
* A MDI Window selection dialog can be brought up through the ID_MDI_OVER_X messages;
* a menu button connected to the MDI client with the ID_MDI_OVER_X message will be
* automatically grayed out if there are less than X MDI child windows.
*/
class FXAPI FXMDIClient : public FXComposite {
  FXDECLARE(FXMDIClient)
  friend class FXMDIChild;
protected:
  FXMDIChild *active;             // Active child
  FXint       cascadex;           // Cascade offset X
  FXint       cascadey;           // Cascade offset Y
protected:
  FXMDIClient();
private:
  FXMDIClient(const FXMDIClient&);
  FXMDIClient &operator=(const FXMDIClient&);
public:
  long onCmdActivateNext(FXObject*,FXSelector,void*);
  long onCmdActivatePrev(FXObject*,FXSelector,void*);
  long onCmdTileHorizontal(FXObject*,FXSelector,void*);
  long onCmdTileVertical(FXObject*,FXSelector,void*);
  long onCmdCascade(FXObject*,FXSelector,void*);
  long onUpdActivateNext(FXObject*,FXSelector,void*);
  long onUpdActivatePrev(FXObject*,FXSelector,void*);
  long onUpdTileVertical(FXObject*,FXSelector,void*);
  long onUpdTileHorizontal(FXObject*,FXSelector,void*);
  long onUpdCascade(FXObject*,FXSelector,void*);
  long onUpdClose(FXObject*,FXSelector,void*);
  long onUpdMenuClose(FXObject*,FXSelector,void*);
  long onUpdRestore(FXObject*,FXSelector,void*);
  long onUpdMenuRestore(FXObject*,FXSelector,void*);
  long onUpdMinimize(FXObject*,FXSelector,void*);
  long onUpdMenuMinimize(FXObject*,FXSelector,void*);
  long onUpdMaximize(FXObject*,FXSelector,void*);
  long onUpdMenuWindow(FXObject*,FXSelector,void*);
  long onCmdWindowSelect(FXObject*,FXSelector,void*);
  long onUpdWindowSelect(FXObject*,FXSelector,void*);
  long onCmdOthersWindows(FXObject*,FXSelector,void*);
  long onUpdOthersWindows(FXObject*,FXSelector,void*);
  long onUpdAnyWindows(FXObject*,FXSelector,void*);
  virtual long onDefault(FXObject*,FXSelector,void*);
public:
  enum {
    ID_MDI_ANY=65400,
    ID_MDI_1,           // Select MDI child 1
    ID_MDI_2,
    ID_MDI_3,
    ID_MDI_4,
    ID_MDI_5,
    ID_MDI_6,
    ID_MDI_7,
    ID_MDI_8,
    ID_MDI_9,
    ID_MDI_10,
    ID_MDI_OVER_1,      // Sensitize MDI menu when 1 or more children
    ID_MDI_OVER_2,
    ID_MDI_OVER_3,
    ID_MDI_OVER_4,
    ID_MDI_OVER_5,
    ID_MDI_OVER_6,
    ID_MDI_OVER_7,
    ID_MDI_OVER_8,
    ID_MDI_OVER_9,
    ID_MDI_OVER_10,
    ID_LAST
    };
public:

  /// Construct MDI Client window
  FXMDIClient(FXComposite* p,FXuint opts=0,FXint x=0,FXint y=0,FXint w=0,FXint h=0);

  /// Return default width
  virtual FXint getDefaultWidth();

  /// Return default height
  virtual FXint getDefaultHeight();

  /// Perform layout
  virtual void layout();

  /**
  * Pass message to all MDI windows, stopping when one of
  * the MDI windows fails to handle the message.
  */
  long forallWindows(FXObject* sender,FXSelector sel,void* ptr);

  /**
  * Pass message once to all MDI windows with the same document,
  * stopping when one of the MDI windows fails to handle the message.
  */
  long forallDocuments(FXObject* sender,FXSelector sel,void* ptr);

  /**
  * Pass message to all MDI Child windows whose target is document,
  * stopping when one of the MDI windows fails to handle the message.
  */
  long forallDocWindows(FXObject* document,FXObject* sender,FXSelector sel,void* ptr);

  /// Set active MDI Child
  virtual FXbool setActiveChild(FXMDIChild* child=NULL,FXbool notify=TRUE);

  /// Get current active child; may be NULL!
  FXMDIChild* getActiveChild() const { return active; }

  /// Cascade windows
  virtual void cascade(FXbool notify=FALSE);

  /// Layout horizontally
  virtual void horizontal(FXbool notify=FALSE);

  /// Layout vertically
  virtual void vertical(FXbool notify=FALSE);

  /// Change cascade offset X
  void setCascadeX(FXint off){ cascadex=off; }

  /// Change cascade offset Y
  void setCascadeY(FXint off){ cascadey=off; }

  /// Get cascade offset X
  FXint getCascadeX() const { return cascadex; }

  /// Get cascade offset Y
  FXint getCascadeY() const { return cascadey; }

  /// Save object to a stream
  virtual void save(FXStream& store) const;

  /// Load object from a stream
  virtual void load(FXStream& store);

  /// Destructor
  virtual ~FXMDIClient();
  };

}

#endif
