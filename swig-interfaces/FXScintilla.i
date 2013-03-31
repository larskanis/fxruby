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

// Struct definition from Scintilla.h
struct NotifyHeader {
  %immutable;
  unsigned int idFrom;
  unsigned int code;
  %mutable;
};

// Struct definition from Scintilla.h
struct SCNotification {
  %immutable;
  struct NotifyHeader nmhdr;
  int position;	// SCN_STYLENEEDED, SCN_MODIFIED, SCN_DWELLSTART, SCN_DWELLEND
  int ch;		// SCN_CHARADDED, SCN_KEY
  int modifiers;	// SCN_KEY
  int modificationType;	// SCN_MODIFIED
  %extend {
    // Need to be careful about when this field's value is actually defined
    VALUE text() const {
      if (self->nmhdr.code==SCN_MODIFIED){
        return (self->text) ? to_ruby(self->text,self->length) : Qnil;
        }
      else if (self->nmhdr.code==SCN_USERLISTSELECTION || self->nmhdr.code==SCN_URIDROPPED){
        return (self->text) ? to_ruby(self->text) : Qnil;
      } else {
        return Qnil;
      }
    }
  }
  int length;		// SCN_MODIFIED
  int linesAdded;	// SCN_MODIFIED
  int message;	// SCN_MACRORECORD
  int line;		// SCN_MODIFIED
  int foldLevelNow;	// SCN_MODIFIED
  int foldLevelPrev;	// SCN_MODIFIED
  int margin;		// SCN_MARGINCLICK
  int listType;	// SCN_USERLISTSELECTION
  int x;			// SCN_DWELLSTART, SCN_DWELLEND
  int y;		// SCN_DWELLSTART, SCN_DWELLEND
  %mutable;
  %extend {
    VALUE wParam() const {
      return INT2NUM(self->wParam);
    }
    VALUE lParam() const {
      return INT2NUM(self->lParam);
    }
  }
};

struct TextRange {
  %immutable;
  char *lpstrText;
  %mutable;
  %extend {
    // "Construct" a TextRange instance
    TextRange(int start,int last,size_t size){
      TextRange *tr=new TextRange;
      tr->chrg.cpMin=start;
      tr->chrg.cpMax=last;
      FXMALLOC(&tr->lpstrText,char,size);
      return tr;
      }

    // Destructor
    ~TextRange(){
      FXFREE(&self->lpstrText);
      delete self;
      }
  }
};


class FXScintilla : public FXScrollArea {
public:
  enum{
    ID_TICK,
    };
public:
  long onScintillaCommand(FXObject*, FXSelector, void* PTR_IGNORE);
  long onPaint(FXObject*, FXSelector, void* PTR_EVENT);
  long onConfigure(FXObject*, FXSelector, void* PTR_EVENT);
  long onTimeoutTicking(FXObject*, FXSelector, void* PTR_IGNORE);
  long onFocusIn(FXObject*, FXSelector, void* PTR_EVENT);
  long onFocusOut(FXObject*, FXSelector, void* PTR_EVENT);
  long onMotion(FXObject*, FXSelector, void* PTR_EVENT);
  long onLeftBtnPress(FXObject*, FXSelector, void* PTR_EVENT);
  long onLeftBtnRelease(FXObject*, FXSelector, void* PTR_EVENT);
  long onRightBtnPress(FXObject*, FXSelector, void* PTR_EVENT);
  long onMiddleBtnPress(FXObject*, FXSelector, void* PTR_EVENT);
  long onBeginDrag(FXObject*, FXSelector, void* PTR_EVENT);
  long onDragged(FXObject*, FXSelector, void* PTR_EVENT);
  long onEndDrag(FXObject*, FXSelector, void* PTR_EVENT);
  long onDNDEnter(FXObject*, FXSelector, void* PTR_EVENT);
  long onDNDLeave(FXObject*, FXSelector, void* PTR_EVENT);
  long onDNDMotion(FXObject*, FXSelector, void* PTR_EVENT);
  long onDNDDrop(FXObject*, FXSelector, void* PTR_EVENT);
  long onDNDRequest(FXObject*, FXSelector, void* PTR_EVENT);
  long onSelectionLost(FXObject*, FXSelector, void* PTR_EVENT);
  long onSelectionRequest(FXObject*, FXSelector, void* PTR_EVENT);
  long onClipboardLost(FXObject*, FXSelector, void* PTR_EVENT);
  long onClipboardRequest(FXObject*, FXSelector, void* PTR_EVENT);
  long onKeyPress(FXObject*, FXSelector, void* PTR_EVENT);
public:
  // Constructor
  %extend {
    FXScintilla(FXComposite* p,FXObject* tgt=NULL,FXSelector sel=0,FXuint opts=0,FXint x=0,FXint y=0,FXint w=0,FXint h=0){
      return new FXRbScintilla(p,tgt,sel,opts,x,y,w,h);
      }
    }

  // Scintilla messaging
  void setScintillaID(int id);

  %extend {
    VALUE sendMessage(unsigned int iMsg, VALUE wParam = Qnil, VALUE lParam = Qnil){
      // Convert wParam argument
      uptr_t wp;
      switch(TYPE(wParam)){
        case T_BIGNUM:
        case T_FIXNUM:
          wp=static_cast<uptr_t>(NUM2SIZET(wParam));
          break;
        case T_STRING:
          wp=static_cast<uptr_t>(reinterpret_cast<FXuval>(RSTRING_PTR(wParam)));
          break;
        case T_TRUE:
        case T_FALSE:
          wp=(wParam==Qtrue) ? 1 : 0;
          break;
        default:
          wp=0;
          break;
        }

      // Convert lParam argument
      sptr_t lp;
      switch(TYPE(lParam)){
        case T_BIGNUM:
        case T_FIXNUM:
          lp=static_cast<sptr_t>(NUM2SIZET(lParam));
          break;
        case T_STRING:
          lp=static_cast<sptr_t>(reinterpret_cast<FXival>(RSTRING_PTR(lParam)));
          break;
        case T_TRUE:
        case T_FALSE:
          lp=(lParam==Qtrue) ? 1 : 0;
          break;
        case T_DATA:
          lp=reinterpret_cast<sptr_t>(DATA_PTR(lParam));
          break;
        default:
          lp=0;
          break;
        }
      sptr_t result=self->sendMessage(iMsg,wp,lp);
      return INT2NUM(result);
      }
  }

  /// Destructor
  virtual ~FXScintilla();
  };


DECLARE_FXOBJECT_VIRTUALS(FXScintilla)
DECLARE_FXID_VIRTUALS(FXScintilla)
DECLARE_FXDRAWABLE_VIRTUALS(FXScintilla)
DECLARE_FXWINDOW_VIRTUALS(FXScintilla)
DECLARE_FXSCROLLAREA_VIRTUALS(FXScintilla)

