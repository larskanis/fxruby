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

%ignore FXDataTarget::getData() const;

/**
* A Data Target allows a valuator widget such as a Slider or Text Field
* to be directly connected with a variable in the program.
* Whenever the valuator control changes, the variable connected through
* the data target is automatically updated; conversely, whenever the program
* changes a variable, all the connected valuator widgets will be updated
* to reflect this new value on the display.
* Data Targets also allow connecting Radio Buttons, Menu Commands, and so on
* to a variable.  In this case, the new value of the connected variable is computed
* by subtracting ID_OPTION from the message ID.
*/
class FXDataTarget : public FXObject {
public:
  long onCmdValue(FXObject*,FXSelector,void* PTR_IGNORE);
  long onUpdValue(FXObject*,FXSelector,void* PTR_IGNORE);
  long onCmdOption(FXObject*,FXSelector,void* PTR_IGNORE);
  long onUpdOption(FXObject*,FXSelector,void* PTR_IGNORE);
public:
  enum {
    DT_VOID=0,
    DT_CHAR,
    DT_UCHAR,
    DT_SHORT,
    DT_USHORT,
    DT_INT,
    DT_UINT,
    DT_LONG,
    DT_ULONG,
    DT_FLOAT,
    DT_DOUBLE,
    DT_STRING,
    DT_LAST
    };
public:
  enum {
    ID_VALUE=1,                   /// Will cause the FXDataTarget to ask sender for value
    ID_OPTION=ID_VALUE+10001,     /// ID_OPTION+i will set the value to i where -10000<=i<=10000
    ID_LAST=ID_OPTION+10000
    };
public:
  %extend {
    // Initialize with this value
    FXDataTarget(VALUE value=Qnil,FXObject* tgt=NULL,FXSelector sel=0){
      return new FXRbDataTarget(value,tgt,sel);
      }
    }

  /// Set the message target object for this data target
  void setTarget(FXObject *t);

  /// Get the message target object for this data target, if any
  FXObject* getTarget() const;

  /// Set the message identifier for this data target
  void setSelector(FXSelector sel);

  /// Get the message identifier for this data target
  FXSelector getSelector() const;

  /// Return type of data it's connected to
  FXuint getType() const;

  /// Return pointer to data it's connected to
  void* getData() const;

  %extend {
    // Return its current value
    VALUE getValue() const {
      FXASSERT(self->isMemberOf(FXMETACLASS(FXRbDataTarget)));
      return dynamic_cast<const FXRbDataTarget*>(self)->getValue();
      }

    // Set new value
    void setValue(VALUE value){
      FXASSERT(self->isMemberOf(FXMETACLASS(FXRbDataTarget)));
      dynamic_cast<FXRbDataTarget*>(self)->setValue(value);
      }
    }

  /// Destructor
  virtual ~FXDataTarget();
  };


DECLARE_FXOBJECT_VIRTUALS(FXDataTarget)

