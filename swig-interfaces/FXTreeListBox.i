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

/// Tree List Box styles
enum {
  TREELISTBOX_NORMAL         = 0          /// Normal style
  };

  
class FXButton;
class FXMenuButton;
class FXTreeList;
class FXPopup;

%rename("shrinkWrap=")    FXTreeListBox::setShrinkWrap(FXbool);
%rename("shrinkWrap")     FXTreeListBox::getShrinkWrap() const;
%rename("menuShown?")			FXTreeListBox::isMenuShown() const;
%rename("menuShown=")			FXTreeListBox::showMenu(FXbool);

// Add alias for backwards compatibility with FXRuby 1.6
%alias FXTreeListBox::isMenuShown() const "paneShown?";

/**
* The Tree List Box behaves very much like a List Box, except that
* it supports a hierarchical, tree structured display of the items.
* When an item is selected it issues a SEL_COMMAND message with the
* pointer to the item.  While manipulating the tree list, it may send
* SEL_CHANGED messages to indicate which item the cursor is hovering over.
* When items are added, replaced, or removed, the list sends messages of
* the type SEL_INSERTED, SEL_REPLACED, or SEL_DELETED, with the pointer to
* the affected item as argument.
*/
class FXTreeListBox : public FXPacker {
protected:
  FXButton      *field;
  FXMenuButton  *button;
  FXTreeList    *tree;
  FXPopup       *pane;
protected:
  FXTreeListBox(){}
public:
  long onFocusUp(FXObject*,FXSelector,void* PTR_EVENT);
  long onFocusDown(FXObject*,FXSelector,void* PTR_EVENT);
  long onFocusSelf(FXObject*,FXSelector,void* PTR_EVENT);
  long onMouseWheel(FXObject*,FXSelector,void* PTR_EVENT);
  long onFieldButton(FXObject*,FXSelector,void* PTR_IGNORE);
  long onTreeUpdate(FXObject*,FXSelector,void* PTR_IGNORE);
  long onTreeForward(FXObject*,FXSelector,void* PTR_TREEITEM);
  long onTreeClicked(FXObject*,FXSelector,void* PTR_TREEITEM);
  long onTreeCommand(FXObject*,FXSelector,void* PTR_TREEITEM);
public:
  enum{
    ID_TREE=FXPacker::ID_LAST,
    ID_FIELD,
    ID_LAST
    };
public:
  
  /// Construct tree list box
  %extend {
    FXTreeListBox(FXComposite* p,FXObject* tgt=NULL,FXSelector sel=0,FXuint opts=FRAME_SUNKEN|FRAME_THICK|TREELISTBOX_NORMAL,FXint x=0,FXint y=0,FXint w=0,FXint h=0,FXint pl=DEFAULT_PAD,FXint pr=DEFAULT_PAD,FXint pt=DEFAULT_PAD,FXint pb=DEFAULT_PAD){
      return new FXRbTreeListBox(p,tgt,sel,opts,x,y,w,h,pl,pr,pt,pb);
      }
    }

  /// Return number of items
  FXint getNumItems() const;
  
  /// Return number of visible items
  FXint getNumVisible() const;
  
  /// Set number of visible items to determine default height
  void setNumVisible(FXint nvis);
  
  /// Return first top-level item
  FXTreeItem* getFirstItem() const;
  
  /// Return last top-level item
  FXTreeItem* getLastItem() const;

  /// Return true if item is the current item
  FXbool isItemCurrent(const FXTreeItem* item) const;

  /// Return current item
  FXTreeItem* getCurrentItem() const;

  /// Fill tree list box by appending items from array of strings
  FXint fillItems(FXTreeItem* father,const FXchar** strings,FXIcon* oi=NULL,FXIcon* ci=NULL,void* ITEMDATA=NULL,FXbool notify=false);

  %extend {
    /// Insert [possibly subclassed] item under father before other item
    FXTreeItem* insertItem(FXTreeItem* other,FXTreeItem* father,FXTreeItem* item,FXbool notify=false){
      if(item->isMemberOf(FXMETACLASS(FXRbTreeItem))){
        dynamic_cast<FXRbTreeItem*>(item)->owner=self;
        }
      return self->insertItem(other,father,item,notify);
      }
  
    
    /// Insert item with given text and optional icons, and user-data pointer under father before other item
    FXTreeItem* insertItem(FXTreeItem* other,FXTreeItem* father,const FXString& text,FXIcon* oi=NULL,FXIcon* ci=NULL,void* ITEMDATA=NULL,FXbool notify=false){
      FXTreeItem* item=self->insertItem(other,father,text,oi,ci,ITEMDATA,notify);
      if(item->isMemberOf(FXMETACLASS(FXRbTreeItem))){
        dynamic_cast<FXRbTreeItem*>(item)->owner=self;
        }
      return item;
      }
    
    /// Append [possibly subclassed] item as last child of father
    FXTreeItem* appendItem(FXTreeItem* father,FXTreeItem* item,FXbool notify=false){
      if(item->isMemberOf(FXMETACLASS(FXRbTreeItem))){
        dynamic_cast<FXRbTreeItem*>(item)->owner=self;
        }
      return self->appendItem(father,item,notify);
      }
  
    /// Append item with given text and optional icons, and user-data pointer as last child of father
    FXTreeItem* appendItem(FXTreeItem* father,const FXString& text,FXIcon* oi=NULL,FXIcon* ci=NULL,void* ITEMDATA=NULL,FXbool notify=false){
      FXTreeItem* item=self->appendItem(father,text,oi,ci,ITEMDATA,notify);
      if(item->isMemberOf(FXMETACLASS(FXRbTreeItem))){
        dynamic_cast<FXRbTreeItem*>(item)->owner=self;
        }
      return item;
      }
    
    /// Prepend [possibly subclassed] item as first child of father
    FXTreeItem* prependItem(FXTreeItem* father,FXTreeItem* item,FXbool notify=false){
      if(item->isMemberOf(FXMETACLASS(FXRbTreeItem))){
        dynamic_cast<FXRbTreeItem*>(item)->owner=self;
        }
      return self->prependItem(father,item,notify);
      }
  
    /// Prepend item with given text and optional icons, and user-data pointer as first child of father
    FXTreeItem* prependItem(FXTreeItem* father,const FXString& text,FXIcon* oi=NULL,FXIcon* ci=NULL,void* ITEMDATA=NULL,FXbool notify=false){
      FXTreeItem* item=self->prependItem(father,text,oi,ci,ITEMDATA,notify);
      if(item->isMemberOf(FXMETACLASS(FXRbTreeItem))){
        dynamic_cast<FXRbTreeItem*>(item)->owner=self;
        }
      return item;
      }

    /// Remove item
    void removeItem(FXTreeItem* item,FXbool notify=false){
      // Save pointer(s) to the soon-to-be-destroyed items
      FXObjectListOf<FXTreeItem> items;
      FXRbTreeList::enumerateItem(item,items);
      
      // Do the deed
      self->removeItem(item,notify);
      
      // Now zero-out pointers held by still-alive Ruby objects
      for(FXint i=0;i<items.no();i++){
        FXRbUnregisterRubyObj(items[i]);
        }
      }
    
    /// Remove all items in range [fm...to]
    void removeItems(FXTreeItem* fm,FXTreeItem* to,FXbool notify=false){
      // Save pointer(s) to the soon-to-be-destroyed items
      FXObjectListOf<FXTreeItem> items;
      FXRbTreeList::enumerateItems(fm,to,items);

      // Do the deed
      self->removeItems(fm,to,notify);

      // Now zero-out pointers held by still-alive Ruby objects
      for(FXint i=0;i<items.no();i++){
        FXRbUnregisterRubyObj(items[i]);
        }
      }
    
    /// Remove all items from list
    void clearItems(FXbool notify=false){
      // Save pointer(s) to the soon-to-be-destroyed items
      FXObjectListOf<FXTreeItem> items;
      FXRbTreeList::enumerateItems(self->getFirstItem(),self->getLastItem(),items);

      // Do the deed
      self->clearItems();

      // Now zero-out pointers held by still-alive Ruby objects
      for(FXint i=0;i<items.no();i++){
        FXRbUnregisterRubyObj(items[i]);
        }
      }
  }
  
  /// Move item under father before other item
  FXTreeItem *moveItem(FXTreeItem* other,FXTreeItem* father,FXTreeItem* item);

  /// Extract item
  FXTreeItem* extractItem(FXTreeItem* item,FXbool notify=false);

  /**
  * Search items by name, beginning from item start.  If the
  * start item is NULL the search will start at the first, top-most item
  * in the list.  Flags may be SEARCH_FORWARD or SEARCH_BACKWARD to control
  * the search direction; this can be combined with SEARCH_NOWRAP or SEARCH_WRAP
  * to control whether the search wraps at the start or end of the list.
  * The option SEARCH_IGNORECASE causes a case-insensitive match.  Finally,
  * passing SEARCH_PREFIX causes searching for a prefix of the item name.
  * Return NULL if no matching item is found.
  */
  FXTreeItem* findItem(const FXString& text,FXTreeItem* start=NULL,FXuint flags=SEARCH_FORWARD|SEARCH_WRAP) const;

  /**
  * Search items by associated user data, beginning from item start. If the
  * start item is NULL the search will start at the first, top-most item
  * in the list.  Flags may be SEARCH_FORWARD or SEARCH_BACKWARD to control
  * the search direction; this can be combined with SEARCH_NOWRAP or SEARCH_WRAP
  * to control whether the search wraps at the start or end of the list.
  */
  FXTreeItem* findItemByData(const void *ITEMDATA,FXTreeItem* start=NULL,FXuint flags=SEARCH_FORWARD|SEARCH_WRAP) const;

  /// Return TRUE if item is leaf-item, i.e. has no children
  FXbool isItemLeaf(const FXTreeItem* item) const;
  
  /// Sort the toplevel items with the sort function
  void sortRootItems();
 
  /// Sort all items recursively
  void sortItems();

  /// Sort child items of item
  void sortChildItems(FXTreeItem* item);
  
  /// Change item label
  void setItemText(FXTreeItem* item,const FXString& text);
  
  /// Return item label
  FXString getItemText(const FXTreeItem* item) const;
  
  /// Change item's closed icon, deleting the old one if owned
  void setItemOpenIcon(FXTreeItem* item,FXIcon* icon,FXbool owned=FALSE);

  /// Return item's open icon
  FXIcon* getItemOpenIcon(const FXTreeItem* item) const;

  /// Change item's closed icon, deleting the old one if it was owned
  void setItemClosedIcon(FXTreeItem* item,FXIcon* icon,FXbool owned=FALSE);
  
  /// Return item's closed icon
  FXIcon* getItemClosedIcon(const FXTreeItem* item) const;
  
  %extend {
    /// Change item's user data
    void setItemData(FXTreeItem* item,VALUE ptr){
      self->setItemData(item,(void*) ptr);
      }
  
    /// Return item's user data
    VALUE getItemData(const FXTreeItem* item) const {
      return self->getItemData(item) ? (VALUE) self->getItemData(item) : Qnil;
      }
  }
  
	/// Show or hide menu
	void showMenu(FXbool shw);

	/// Is the menu pane shown?
	FXbool isMenuShown() const;

  /// Change font
  void setFont(FXFont* fnt);
  
  /// Return font
  FXFont* getFont() const;
  
  /// Return list style
  FXuint getListStyle() const;
  
  /// Change list style
  void setListStyle(FXuint style);
  
  /// Change popup pane shrinkwrap mode
  void setShrinkWrap(FXbool flag);

  /// Return popup pane shrinkwrap mode
  FXbool getShrinkWrap() const;

  /// Change help text
  void setHelpText(const FXString& txt);
  
  /// Return help text
  const FXString& getHelpText() const;
  
  /// Change tip text
  void setTipText(const FXString& txt);
  
  /// Return tip text
  const FXString& getTipText() const;

  /// Destructor
  virtual ~FXTreeListBox();
  };


DECLARE_FXOBJECT_VIRTUALS(FXTreeListBox)
DECLARE_FXID_VIRTUALS(FXTreeListBox)
DECLARE_FXDRAWABLE_VIRTUALS(FXTreeListBox)
DECLARE_FXWINDOW_VIRTUALS(FXTreeListBox)
DECLARE_FXTREELISTBOX_VIRTUALS(FXTreeListBox)

%{
static swig_type_info *FXTreeListBox_dynamic_cast(void **ptr) {
    FXTreeListBox **ppTreeListBox = reinterpret_cast<FXTreeListBox **>(ptr);
    FXDirBox *pDirBox=dynamic_cast<FXDirBox*>(*ppTreeListBox);
    if(pDirBox){
      *ptr=reinterpret_cast<void*>(pDirBox);
      return SWIG_TypeQuery("FXDirBox *");
      }
    return 0;
}
%}

DYNAMIC_CAST(SWIGTYPE_p_FXTreeListBox, FXTreeListBox_dynamic_cast);

