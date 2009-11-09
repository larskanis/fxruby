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

/// Minimum and maximum keys
enum {
  MINKEY = 0,
  MAXKEY = 65535
  };


/// Minimum and maximum types
enum {
  MINTYPE = 0,
  MAXTYPE = 65535
  };


// Association key
typedef FXuint FXSelector;

%ignore FXObject::getClassName() const;
%ignore FXObject::isMemberOf(const FXMetaClass* metaclass) const;

/**
* Object is the base class for all objects in FOX; in order to receive
* messages from the user interface, your class must derive from Object.
* The Object class also provides serialization facilities, with which
* you can save and restore the object's state.  If you've subclassed
* from Object, you can save your subclasses' state by overloading the
* save() and load() functions and use the stream API to serialize its
* member data.
*/
class FXObject {
public:
  %extend {
    /// Constructor
    FXObject(){
      return new FXRbObject();
      }
    }

  /// Handle is actually declared (hidden) in FXRbDECLARE
  virtual long handle(FXObject* sender,FXSelector sel,void* PTR_MAGIC);

  /// Get class name of some object
  const FXchar* getClassName() const;

  /// Check if object is member of metaclass
  bool isMemberOf(const FXMetaClass* metaclass) const;

  /// Try handle message safely
  virtual long tryHandle(FXObject* sender,FXSelector sel,void* ptr);

  /// Virtual destructor
  virtual ~FXObject();
  };


DECLARE_FXOBJECT_VIRTUALS(FXObject)


%{
static swig_type_info *FXObject_dynamic_cast(void **ptr) {
    FXObject **ppObject = reinterpret_cast<FXObject **>(ptr);
    FXAccelTable *pAccelTable=dynamic_cast<FXAccelTable*>(*ppObject);
    if(pAccelTable){
      *ptr=reinterpret_cast<void*>(pAccelTable);
      return SWIG_TypeQuery("FXAccelTable *");
      }
    FXApp *pApp=dynamic_cast<FXApp*>(*ppObject);
    if(pApp){
      *ptr=reinterpret_cast<void*>(pApp);
      return SWIG_TypeQuery("FXApp *");
      }
    FXDataTarget *pDataTarget=dynamic_cast<FXDataTarget*>(*ppObject);
    if(pDataTarget){
      *ptr=reinterpret_cast<void*>(pDataTarget);
      return SWIG_TypeQuery("FXDataTarget *");
      }
    FXDebugTarget *pDebugTarget=dynamic_cast<FXDebugTarget*>(*ppObject);
    if(pDebugTarget){
      *ptr=reinterpret_cast<void*>(pDebugTarget);
      return SWIG_TypeQuery("FXDebugTarget *");
      }
    FXDelegator *pDelegator=dynamic_cast<FXDelegator*>(*ppObject);
    if(pDelegator){
      *ptr=reinterpret_cast<void*>(pDelegator);
      return SWIG_TypeQuery("FXDelegator *");
      }
    FXDict *pDict=dynamic_cast<FXDict*>(*ppObject);
    if(pDict){
      *ptr=reinterpret_cast<void*>(pDict);
      return SWIG_TypeQuery("FXDict *");
      }
    FXDocument *pDocument=dynamic_cast<FXDocument*>(*ppObject);
    if(pDocument){
      *ptr=reinterpret_cast<void*>(pDocument);
      return SWIG_TypeQuery("FXDocument *");
      }
    FXGLObject *pGLObject=dynamic_cast<FXGLObject*>(*ppObject);
    if(pGLObject){
      *ptr=reinterpret_cast<void*>(pGLObject);
      return SWIG_TypeQuery("FXGLObject *");
      }
    FXHeaderItem *pHeaderItem=dynamic_cast<FXHeaderItem*>(*ppObject);
    if(pHeaderItem){
      *ptr=reinterpret_cast<void*>(pHeaderItem);
      return SWIG_TypeQuery("FXHeaderItem *");
      }
    FXIconItem *pIconItem=dynamic_cast<FXIconItem*>(*ppObject);
    if(pIconItem){
      *ptr=reinterpret_cast<void*>(pIconItem);
      return SWIG_TypeQuery("FXIconItem *");
      }
    FXIconSource *pIconSource=dynamic_cast<FXIconSource*>(*ppObject);
    if(pIconSource){
      *ptr=reinterpret_cast<void*>(pIconSource);
      return SWIG_TypeQuery("FXIconSource *");
      }
    FXId *pId=dynamic_cast<FXId*>(*ppObject);
    if(pId){
      *ptr=reinterpret_cast<void*>(pId);
      return SWIG_TypeQuery("FXId *");
      }
    FXListItem *pListItem=dynamic_cast<FXListItem*>(*ppObject);
    if(pListItem){
      *ptr=reinterpret_cast<void*>(pListItem);
      return SWIG_TypeQuery("FXListItem *");
      }
    FXRecentFiles *pRecentFiles=dynamic_cast<FXRecentFiles*>(*ppObject);
    if(pRecentFiles){
      *ptr=reinterpret_cast<void*>(pRecentFiles);
      return SWIG_TypeQuery("FXRecentFiles *");
      }
    FXTableItem *pTableItem=dynamic_cast<FXTableItem*>(*ppObject);
    if(pTableItem){
      *ptr=reinterpret_cast<void*>(pTableItem);
      return SWIG_TypeQuery("FXTableItem *");
      }
    FXTreeItem *pTreeItem=dynamic_cast<FXTreeItem*>(*ppObject);
    if(pTreeItem){
      *ptr=reinterpret_cast<void*>(pTreeItem);
      return SWIG_TypeQuery("FXTreeItem *");
      }
    return 0;
}
%}

DYNAMIC_CAST(SWIGTYPE_p_FXObject, FXObject_dynamic_cast);

