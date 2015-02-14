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
* A DebugTarget prints out every message it receives.
* To use it, simply make the DebugTarget a target of the widget
* whose messages you want to see,
*/
class FXDebugTarget : public FXObject {
public:
#ifdef SWIGRUBY
  %extend {
      static VALUE messageTypeName() {
          VALUE messageTypeNames = rb_ary_new();
          for (int i = 0; i < SEL_LAST; i++) {
              rb_ary_push(messageTypeNames,
                  to_ruby(FXDebugTarget::messageTypeName[i]));
          }
          return messageTypeNames;
      }
  }
#endif
public:
  long onMessage(FXObject*,FXSelector,void* PTR_NULL); // FIXME
public:
  %extend {
    /// Construct a debug target
    FXDebugTarget(){
      return new FXRbDebugTarget();
      }
    }
  };


DECLARE_FXOBJECT_VIRTUALS(FXDebugTarget)

