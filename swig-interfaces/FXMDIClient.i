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
class FXMDIClient : public FXComposite {
public:
  long onCmdActivateNext(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdActivatePrev(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdTileHorizontal(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdTileVertical(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdCascade(FXObject*,FXSelector,void* PTR_IGNORE);
  long onUpdActivateNext(FXObject*,FXSelector,void* PTR_IGNORE);
  long onUpdActivatePrev(FXObject*,FXSelector,void* PTR_IGNORE);
  long onUpdTileVertical(FXObject*,FXSelector,void* PTR_IGNORE);
  long onUpdTileHorizontal(FXObject*,FXSelector,void* PTR_IGNORE);
  long onUpdCascade(FXObject*,FXSelector,void* PTR_IGNORE);
  long onUpdClose(FXObject*,FXSelector,void* PTR_IGNORE);
  long onUpdMenuClose(FXObject*,FXSelector,void* PTR_IGNORE);
  long onUpdRestore(FXObject*,FXSelector,void* PTR_IGNORE);
  long onUpdMenuRestore(FXObject*,FXSelector,void* PTR_IGNORE);
  long onUpdMinimize(FXObject*,FXSelector,void* PTR_IGNORE);
  long onUpdMenuMinimize(FXObject*,FXSelector,void* PTR_IGNORE);
  long onUpdMaximize(FXObject*,FXSelector,void* PTR_IGNORE);
  long onUpdMenuWindow(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdWindowSelect(FXObject*,FXSelector,void* PTR_IGNORE);
  long onUpdWindowSelect(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdOthersWindows(FXObject*,FXSelector,void* PTR_IGNORE);
  long onUpdOthersWindows(FXObject*,FXSelector,void* PTR_IGNORE);
  long onUpdAnyWindows(FXObject*,FXSelector,void* PTR_IGNORE);
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
  %extend {
    /// Construct MDI Client window
    FXMDIClient(FXComposite* p,FXuint opts=0,FXint x=0,FXint y=0,FXint w=0,FXint h=0){
      return new FXRbMDIClient(p,opts,x,y,w,h);
      }
    }

  /**
  * Pass message to all MDI windows, stopping when one of
  * the MDI windows fails to handle the message.
  */
  long forallWindows(FXObject* sender,FXSelector sel,void* ITEMDATA);

  /**
  * Pass message once to all MDI windows with the same document,
  * stopping when one of the MDI windows fails to handle the message.
  */
  long forallDocuments(FXObject* sender,FXSelector sel,void* ITEMDATA);

  /**
  * Pass message to all MDI Child windows whose target is document,
  * stopping when one of the MDI windows fails to handle the message.
  */
  long forallDocWindows(FXObject* document,FXObject* sender,FXSelector sel,void* ITEMDATA);

  /// Get current active child; may be NULL!
  FXMDIChild* getActiveChild() const;

  /// Change cascade offset X
  void setCascadeX(FXint off);

  /// Change cascade offset Y
  void setCascadeY(FXint off);

  /// Get cascade offset X
  FXint getCascadeX() const;

  /// Get cascade offset Y
  FXint getCascadeY() const;

  /// Destructor
  virtual ~FXMDIClient();
  };


DECLARE_FXOBJECT_VIRTUALS(FXMDIClient)
DECLARE_FXID_VIRTUALS(FXMDIClient)
DECLARE_FXDRAWABLE_VIRTUALS(FXMDIClient)
DECLARE_FXWINDOW_VIRTUALS(FXMDIClient)
DECLARE_FXMDICLIENT_VIRTUALS(FXMDIClient)
