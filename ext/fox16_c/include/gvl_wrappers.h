/*
 * gvl_wrappers.h - Wrapper functions for locking/unlocking the Ruby GVL
 *
 * These are some obscure preprocessor directives that allow to generate
 * drop-in replacement wrapper functions in a declarative manner.
 * These wrapper functions ensure that ruby's GVL is released on each
 * function call and reacquired at the end of the call or in callbacks.
 * This way blocking functions calls don't block concurrent ruby threads.
 *
 * The wrapper of each function is prefixed by "gvl_".
 *
 * Use "gcc -E" to retrieve the generated code.
 */

#ifndef __gvl_wrappers_h
#define __gvl_wrappers_h

extern "C" {
  #if defined(HAVE_RB_THREAD_CALL_WITH_GVL)
  extern void *rb_thread_call_with_gvl(void *(*func)(void *), void *data1);
  #endif

  #if defined(HAVE_RB_THREAD_CALL_WITHOUT_GVL)
  extern "C" void *rb_thread_call_without_gvl(void *(*func)(void *), void *data1,
          rb_unblock_function_t *ubf, void *data2);
  #endif
}

void fxrb_wakeup_fox(void *);

#define DEFINE_PARAM_LIST1(type, ref, name) \
  , name

#define DEFINE_PARAM_LIST2(type, ref, name) \
  , p->params.name

#define DEFINE_PARAM_LIST3(type, ref, name) \
  , type ref name

#define DEFINE_PARAM_LIST4(type, ref, name) \
  , typename type

#define DEFINE_PARAM_LIST5(type, ref, name) \
  , type

#define DEFINE_PARAM_DECL(type, ref, name) \
  type ref name;

#define DEFINE_GVL_WRAPPER_STRUCT(klass, name, baseclass, when_non_void, rettype, firstparamtype, firstparamname) \
  struct gvl_wrapper_##klass##_##name##_params { \
    struct { \
      firstparamtype firstparamname; \
      FOR_EACH_PARAM_OF_##baseclass##_##name(DEFINE_PARAM_DECL) \
    } params; \
    when_non_void( rettype retval; ) \
  };

#ifdef HAVE___THREAD
  extern __thread int g_fxrb_thread_has_gvl;
#endif

#if defined(HAVE_RB_THREAD_CALL_WITHOUT_GVL)
  #define DEFINE_GVL_SKELETON(klass, name, baseclass, when_non_void, rettype, firstparamtype, firstparamname) \
    static void * gvl_##klass##_##name##_skeleton( void *data ){ \
      struct gvl_wrapper_##klass##_##name##_params *p = (struct gvl_wrapper_##klass##_##name##_params*)data; \
      g_fxrb_thread_has_gvl = 0; \
      when_non_void( p->retval = ) \
        klass##_##name##_gvl( p->params.firstparamname FOR_EACH_PARAM_OF_##baseclass##_##name(DEFINE_PARAM_LIST2) ); \
      g_fxrb_thread_has_gvl = 1; \
      return NULL; \
    }

  #define DEFINE_GVL_STUB(klass, name, baseclass, when_non_void, rettype, firstparamtype, firstparamname) \
    rettype klass##_##name(firstparamtype firstparamname FOR_EACH_PARAM_OF_##baseclass##_##name(DEFINE_PARAM_LIST3)){ \
      struct gvl_wrapper_##klass##_##name##_params params = { \
        {firstparamname FOR_EACH_PARAM_OF_##baseclass##_##name(DEFINE_PARAM_LIST1)}, when_non_void((rettype)0) \
      }; \
      rb_thread_call_without_gvl(gvl_##klass##_##name##_skeleton, &params, fxrb_wakeup_fox, 0); \
      when_non_void( return params.retval; ) \
    }
#else
  #define DEFINE_GVL_SKELETON(klass, name, baseclass, when_non_void, rettype, firstparamtype, firstparamname)

  #define DEFINE_GVL_STUB(klass, name, baseclass, when_non_void, rettype, firstparamtype, firstparamname) \
    rettype klass##_##name(firstparamtype firstparamname FOR_EACH_PARAM_OF_##baseclass##_##name(DEFINE_PARAM_LIST3)){ \
      return klass##_##name##_gvl(firstparamname FOR_EACH_PARAM_OF_##baseclass##_##name(DEFINE_PARAM_LIST1)); \
    }
#endif

#define DEFINE_GVL_STUB_DECL(klass, name, baseclass, when_non_void, rettype, firstparamtype, firstparamname) \
  rettype klass##_##name( firstparamtype firstparamname FOR_EACH_PARAM_OF_##baseclass##_##name(DEFINE_PARAM_LIST3));



#define DEFINE_GVLCB_WRAPPER_STRUCT(name, when_non_void, rettype, firstparamtype, firstparamname, paramcount) \
  template<typename firstparamtype FOR_EACH_PARAM_OF_##name##_##paramcount(DEFINE_PARAM_LIST4)> \
        struct gvl_wrapper_##name##_##paramcount##_params { \
    struct { \
      firstparamtype firstparamname; \
      FOR_EACH_PARAM_OF_##name##_##paramcount(DEFINE_PARAM_DECL) \
    } params; \
    when_non_void( rettype retval; ) \
  };

#define DEFINE_GVLCB_STUB_DECL(name, when_non_void, rettype, firstparamtype, firstparamname, paramcount) \
  template<typename firstparamtype FOR_EACH_PARAM_OF_##name##_##paramcount(DEFINE_PARAM_LIST4)> \
        rettype name( firstparamtype firstparamname FOR_EACH_PARAM_OF_##name##_##paramcount(DEFINE_PARAM_LIST3));

#define DEFINE_GVLCB_SKELETON(name, when_non_void, rettype, firstparamtype, firstparamname, paramcount) \
  template<typename firstparamtype FOR_EACH_PARAM_OF_##name##_##paramcount(DEFINE_PARAM_LIST4)> \
        static void * gvl_##name##_##paramcount##_skeleton( void *data ){ \
    struct gvl_wrapper_##name##_##paramcount##_params<firstparamtype FOR_EACH_PARAM_OF_##name##_##paramcount(DEFINE_PARAM_LIST5)>  *p = \
        (struct gvl_wrapper_##name##_##paramcount##_params<firstparamtype FOR_EACH_PARAM_OF_##name##_##paramcount(DEFINE_PARAM_LIST5)>*)data; \
    when_non_void( p->retval = ) \
      name##_gvlcb( p->params.firstparamname FOR_EACH_PARAM_OF_##name##_##paramcount(DEFINE_PARAM_LIST2) ); \
    return NULL; \
  }

#if defined(HAVE_RB_THREAD_CALL_WITH_GVL)
  #define DEFINE_GVLCB_STUB(name, when_non_void, rettype, firstparamtype, firstparamname, paramcount) \
    template<typename firstparamtype FOR_EACH_PARAM_OF_##name##_##paramcount(DEFINE_PARAM_LIST4)> \
          rettype name(firstparamtype firstparamname FOR_EACH_PARAM_OF_##name##_##paramcount(DEFINE_PARAM_LIST3)){ \
      if( g_fxrb_thread_has_gvl ){ \
        return name##_gvlcb( firstparamname FOR_EACH_PARAM_OF_##name##_##paramcount(DEFINE_PARAM_LIST1) ); \
      } else { \
        struct gvl_wrapper_##name##_##paramcount##_params<firstparamtype FOR_EACH_PARAM_OF_##name##_##paramcount(DEFINE_PARAM_LIST5)> params = { \
          {firstparamname FOR_EACH_PARAM_OF_##name##_##paramcount(DEFINE_PARAM_LIST1)} \
        }; \
        g_fxrb_thread_has_gvl = 1; \
        rb_thread_call_with_gvl(gvl_##name##_##paramcount##_skeleton<firstparamtype FOR_EACH_PARAM_OF_##name##_##paramcount(DEFINE_PARAM_LIST5)>, &params); \
        g_fxrb_thread_has_gvl = 0; \
        when_non_void( return params.retval; ) \
      } \
    }
#else
  #define DEFINE_GVLCB_STUB(name, when_non_void, rettype, firstparamtype, firstparamname, paramcount) \
    template<typename firstparamtype FOR_EACH_PARAM_OF_##name##_##paramcount(DEFINE_PARAM_LIST4)> \
          rettype name(firstparamtype firstparamname FOR_EACH_PARAM_OF_##name##_##paramcount(DEFINE_PARAM_LIST3)){ \
      return name##_gvlcb( firstparamname FOR_EACH_PARAM_OF_##name##_##paramcount(DEFINE_PARAM_LIST1) ); \
    }
#endif

#define GVL_TYPE_VOID(string)
#define GVL_TYPE_NONVOID(string) string


/*
* Definitions of blocking functions and their parameters
*/

#define FOR_EACH_PARAM_OF_FXImage_loadPixels(param) \
  param(FXStream, &, store)
#define FOR_EACH_PARAM_OF_FXImage_savePixels(param) \
  param(FXStream, &, store)

#define FOR_EACH_PARAM_OF_FXDialogBox_execute(param) \
  param(FXuint, , placement)

#define FOR_EACH_PARAM_OF_FXApp_run(param)

#define FOR_EACH_PARAM_OF_FXApp_runOneEvent(param) \
  param(bool, , blocking)

#define FOR_EACH_PARAM_OF_FXApp_runUntil(param) \
  param(FXuint, &, condition)

#define FOR_EACH_PARAM_OF_FXApp_runWhileEvents(param)

#define FOR_EACH_PARAM_OF_FXApp_runModalWhileEvents(param) \
  param(FXWindow*, , window)

#define FOR_EACH_PARAM_OF_FXApp_runModal(param)

#define FOR_EACH_PARAM_OF_FXApp_runModalFor(param) \
  param(FXWindow*, , window)

#define FOR_EACH_PARAM_OF_FXApp_runModalWhileShown(param) \
  param(FXWindow*, , window)

#define FOR_EACH_PARAM_OF_FXApp_runPopup(param) \
  param(FXWindow*, , owner)



/* function( class, name, baseclass, void_or_nonvoid, returntype, firstparamtype, firstparamname ) */
#define FOR_EACH_BLOCKING_FUNCTION(function) \
  function(FXImage, loadPixels, FXImage, GVL_TYPE_NONVOID, bool, FXImage *, self) \
  function(FXImage, savePixels, FXImage, GVL_TYPE_NONVOID, bool, const FXImage *, self) \
  function(FXBMPImage, loadPixels, FXImage, GVL_TYPE_NONVOID, bool, FXBMPImage *, self) \
  function(FXBMPImage, savePixels, FXImage, GVL_TYPE_NONVOID, bool, const FXBMPImage *, self) \
  function(FXJPGImage, loadPixels, FXImage, GVL_TYPE_NONVOID, bool, FXJPGImage *, self) \
  function(FXJPGImage, savePixels, FXImage, GVL_TYPE_NONVOID, bool, const FXJPGImage *, self) \
  function(FXGIFImage, loadPixels, FXImage, GVL_TYPE_NONVOID, bool, FXGIFImage *, self) \
  function(FXGIFImage, savePixels, FXImage, GVL_TYPE_NONVOID, bool, const FXGIFImage *, self) \
  function(FXICOImage, loadPixels, FXImage, GVL_TYPE_NONVOID, bool, FXICOImage *, self) \
  function(FXICOImage, savePixels, FXImage, GVL_TYPE_NONVOID, bool, const FXICOImage *, self) \
  function(FXPNGImage, loadPixels, FXImage, GVL_TYPE_NONVOID, bool, FXPNGImage *, self) \
  function(FXPNGImage, savePixels, FXImage, GVL_TYPE_NONVOID, bool, const FXPNGImage *, self) \
  function(FXPPMImage, loadPixels, FXImage, GVL_TYPE_NONVOID, bool, FXPPMImage *, self) \
  function(FXPPMImage, savePixels, FXImage, GVL_TYPE_NONVOID, bool, const FXPPMImage *, self) \
  function(FXPCXImage, loadPixels, FXImage, GVL_TYPE_NONVOID, bool, FXPCXImage *, self) \
  function(FXPCXImage, savePixels, FXImage, GVL_TYPE_NONVOID, bool, const FXPCXImage *, self) \
  function(FXRGBImage, loadPixels, FXImage, GVL_TYPE_NONVOID, bool, FXRGBImage *, self) \
  function(FXRGBImage, savePixels, FXImage, GVL_TYPE_NONVOID, bool, const FXRGBImage *, self) \
  function(FXTGAImage, loadPixels, FXImage, GVL_TYPE_NONVOID, bool, FXTGAImage *, self) \
  function(FXTGAImage, savePixels, FXImage, GVL_TYPE_NONVOID, bool, const FXTGAImage *, self) \
  function(FXTIFImage, loadPixels, FXImage, GVL_TYPE_NONVOID, bool, FXTIFImage *, self) \
  function(FXTIFImage, savePixels, FXImage, GVL_TYPE_NONVOID, bool, const FXTIFImage *, self) \
  function(FXXBMImage, loadPixels, FXImage, GVL_TYPE_NONVOID, bool, FXXBMImage *, self) \
  function(FXXBMImage, savePixels, FXImage, GVL_TYPE_NONVOID, bool, const FXXBMImage *, self) \
  function(FXXPMImage, loadPixels, FXImage, GVL_TYPE_NONVOID, bool, FXXPMImage *, self) \
  function(FXXPMImage, savePixels, FXImage, GVL_TYPE_NONVOID, bool, const FXXPMImage *, self) \
  function(FXIcon, loadPixels, FXImage, GVL_TYPE_NONVOID, bool, FXIcon *, self) \
  function(FXIcon, savePixels, FXImage, GVL_TYPE_NONVOID, bool, const FXIcon *, self) \
  function(FXBMPIcon, loadPixels, FXImage, GVL_TYPE_NONVOID, bool, FXBMPIcon *, self) \
  function(FXBMPIcon, savePixels, FXImage, GVL_TYPE_NONVOID, bool, const FXBMPIcon *, self) \
  function(FXJPGIcon, loadPixels, FXImage, GVL_TYPE_NONVOID, bool, FXJPGIcon *, self) \
  function(FXJPGIcon, savePixels, FXImage, GVL_TYPE_NONVOID, bool, const FXJPGIcon *, self) \
  function(FXGIFIcon, loadPixels, FXImage, GVL_TYPE_NONVOID, bool, FXGIFIcon *, self) \
  function(FXGIFIcon, savePixels, FXImage, GVL_TYPE_NONVOID, bool, const FXGIFIcon *, self) \
  function(FXICOIcon, loadPixels, FXImage, GVL_TYPE_NONVOID, bool, FXICOIcon *, self) \
  function(FXICOIcon, savePixels, FXImage, GVL_TYPE_NONVOID, bool, const FXICOIcon *, self) \
  function(FXPNGIcon, loadPixels, FXImage, GVL_TYPE_NONVOID, bool, FXPNGIcon *, self) \
  function(FXPNGIcon, savePixels, FXImage, GVL_TYPE_NONVOID, bool, const FXPNGIcon *, self) \
  function(FXPPMIcon, loadPixels, FXImage, GVL_TYPE_NONVOID, bool, FXPPMIcon *, self) \
  function(FXPPMIcon, savePixels, FXImage, GVL_TYPE_NONVOID, bool, const FXPPMIcon *, self) \
  function(FXPCXIcon, loadPixels, FXImage, GVL_TYPE_NONVOID, bool, FXPCXIcon *, self) \
  function(FXPCXIcon, savePixels, FXImage, GVL_TYPE_NONVOID, bool, const FXPCXIcon *, self) \
  function(FXRGBIcon, loadPixels, FXImage, GVL_TYPE_NONVOID, bool, FXRGBIcon *, self) \
  function(FXRGBIcon, savePixels, FXImage, GVL_TYPE_NONVOID, bool, const FXRGBIcon *, self) \
  function(FXTGAIcon, loadPixels, FXImage, GVL_TYPE_NONVOID, bool, FXTGAIcon *, self) \
  function(FXTGAIcon, savePixels, FXImage, GVL_TYPE_NONVOID, bool, const FXTGAIcon *, self) \
  function(FXTIFIcon, loadPixels, FXImage, GVL_TYPE_NONVOID, bool, FXTIFIcon *, self) \
  function(FXTIFIcon, savePixels, FXImage, GVL_TYPE_NONVOID, bool, const FXTIFIcon *, self) \
  function(FXXBMIcon, loadPixels, FXImage, GVL_TYPE_NONVOID, bool, FXXBMIcon *, self) \
  function(FXXBMIcon, savePixels, FXImage, GVL_TYPE_NONVOID, bool, const FXXBMIcon *, self) \
  function(FXXPMIcon, loadPixels, FXImage, GVL_TYPE_NONVOID, bool, FXXPMIcon *, self) \
  function(FXXPMIcon, savePixels, FXImage, GVL_TYPE_NONVOID, bool, const FXXPMIcon *, self) \
  function(FXChoiceBox, execute, FXDialogBox, GVL_TYPE_NONVOID, FXuint, FXChoiceBox *, self) \
  function(FXColorDialog, execute, FXDialogBox, GVL_TYPE_NONVOID, FXuint, FXColorDialog *, self) \
  function(FXDialogBox, execute, FXDialogBox, GVL_TYPE_NONVOID, FXuint, FXDialogBox *, self) \
  function(FXDirDialog, execute, FXDialogBox, GVL_TYPE_NONVOID, FXuint, FXDirDialog *, self) \
  function(FXFileDialog, execute, FXDialogBox, GVL_TYPE_NONVOID, FXuint, FXFileDialog *, self) \
  function(FXFontDialog, execute, FXDialogBox, GVL_TYPE_NONVOID, FXuint, FXFontDialog *, self) \
  function(FXInputDialog, execute, FXDialogBox, GVL_TYPE_NONVOID, FXuint, FXInputDialog *, self) \
  function(FXMessageBox, execute, FXDialogBox, GVL_TYPE_NONVOID, FXuint, FXMessageBox *, self) \
  function(FXPrintDialog, execute, FXDialogBox, GVL_TYPE_NONVOID, FXuint, FXPrintDialog *, self) \
  function(FXProgressDialog, execute, FXDialogBox, GVL_TYPE_NONVOID, FXuint, FXProgressDialog *, self) \
  function(FXReplaceDialog, execute, FXDialogBox, GVL_TYPE_NONVOID, FXuint, FXReplaceDialog *, self) \
  function(FXSearchDialog, execute, FXDialogBox, GVL_TYPE_NONVOID, FXuint, FXSearchDialog *, self) \
  function(FXWizard, execute, FXDialogBox, GVL_TYPE_NONVOID, FXuint, FXWizard *, self) \
  function(FXApp, run, FXApp, GVL_TYPE_NONVOID, FXint, FXApp *, self) \
  function(FXApp, runOneEvent, FXApp, GVL_TYPE_NONVOID, bool, FXApp *, self) \
  function(FXApp, runUntil, FXApp, GVL_TYPE_NONVOID, FXint, FXApp *, self) \
  function(FXApp, runWhileEvents, FXApp, GVL_TYPE_NONVOID, FXint, FXApp *, self) \
  function(FXApp, runModalWhileEvents, FXApp, GVL_TYPE_NONVOID, FXint, FXApp *, self) \
  function(FXApp, runModal, FXApp, GVL_TYPE_NONVOID, FXint, FXApp *, self) \
  function(FXApp, runModalFor, FXApp, GVL_TYPE_NONVOID, FXint, FXApp *, self) \
  function(FXApp, runModalWhileShown, FXApp, GVL_TYPE_NONVOID, FXint, FXApp *, self) \
  function(FXApp, runPopup, FXApp, GVL_TYPE_NONVOID, FXint, FXApp *, self) \



FOR_EACH_BLOCKING_FUNCTION( DEFINE_GVL_STUB_DECL )

/*
 * Definitions of callback functions and their parameters
 */

#define FOR_EACH_PARAM_OF_FXRbCallVoidMethod_2(param) \
  param(ID, , func)

#define FOR_EACH_PARAM_OF_FXRbCallVoidMethod_3(param) \
  param(ID, , func) \
  param(TYPE1, &, arg1)

#define FOR_EACH_PARAM_OF_FXRbCallVoidMethod_4(param) \
  param(ID, , func) \
  param(TYPE1, , arg1) \
  param(TYPE2, , arg2)

#define FOR_EACH_PARAM_OF_FXRbCallVoidMethod_5(param) \
  param(ID, , func) \
  param(TYPE1, , arg1) \
  param(TYPE2, , arg2) \
  param(TYPE3, , arg3)

#define FOR_EACH_PARAM_OF_FXRbCallVoidMethod_6(param) \
  param(ID, , func) \
  param(TYPE1, , arg1) \
  param(TYPE2, , arg2) \
  param(TYPE3, , arg3) \
  param(TYPE4, , arg4)

#define FOR_EACH_PARAM_OF_FXRbCallVoidMethod_7(param) \
  param(ID, , func) \
  param(TYPE1, &, arg1) \
  param(TYPE2, , arg2) \
  param(TYPE3, , arg3) \
  param(TYPE4, , arg4) \
  param(TYPE5, , arg5)

#define FOR_EACH_PARAM_OF_FXRbCallVoidMethod_8(param) \
  param(ID, , func) \
  param(TYPE1, , arg1) \
  param(TYPE2, &, arg2) \
  param(TYPE3, , arg3) \
  param(TYPE4, , arg4) \
  param(TYPE5, , arg5) \
  param(TYPE6, , arg6)

#define FOR_EACH_PARAM_OF_FXRbCallVoidMethod_9(param) \
  param(ID, , func) \
  param(TYPE1, , arg1) \
  param(TYPE2, , arg2) \
  param(TYPE3, , arg3) \
  param(TYPE4, , arg4) \
  param(TYPE5, , arg5) \
  param(TYPE6, , arg6) \
  param(TYPE7, , arg7)

#define FOR_EACH_PARAM_OF_FXRbCallVoidMethod_11(param) \
  param(ID, , func) \
  param(TYPE1, , arg1) \
  param(TYPE2, , arg2) \
  param(TYPE3, , arg3) \
  param(TYPE4, , arg4) \
  param(TYPE5, , arg5) \
  param(TYPE6, , arg6) \
  param(TYPE7, , arg7) \
  param(TYPE8, , arg8) \
  param(TYPE9, , arg9)

#define FOR_EACH_PARAM_OF_FXRbCallBoolMethod_2(param) \
  param(ID, , func)

#define FOR_EACH_PARAM_OF_FXRbCallBoolMethod_3(param) \
  param(ID, , func) \
  param(TYPE1, &, arg1)

#define FOR_EACH_PARAM_OF_FXRbCallBoolMethod_4(param) \
  param(ID, , func) \
  param(TYPE1, , arg1) \
  param(TYPE2, , arg2)

#define FOR_EACH_PARAM_OF_FXRbCallBoolMethod_5(param) \
  param(ID, , func) \
  param(TYPE1, , arg1) \
  param(TYPE2, , arg2) \
  param(TYPE3, , arg3)

#define FOR_EACH_PARAM_OF_FXRbCallBoolMethod_7(param) \
  param(ID, , func) \
  param(TYPE1, , arg1) \
  param(TYPE2, , arg2) \
  param(TYPE3, , arg3) \
  param(TYPE4, , arg4) \
  param(TYPE5, , arg5)

#define FOR_EACH_PARAM_OF_FXRbCallIntMethod_2(param) \
  param(ID, , func)

#define FOR_EACH_PARAM_OF_FXRbCallIntMethod_3(param) \
  param(ID, , func) \
  param(TYPE1, , arg1)

#define FOR_EACH_PARAM_OF_FXRbCallIntMethod_4(param) \
  param(ID, , func) \
  param(TYPE1, , arg1) \
  param(TYPE2, , arg2)

#define FOR_EACH_PARAM_OF_FXRbCallIntMethod_7(param) \
  param(ID, , func) \
  param(TYPE1, , arg1) \
  param(TYPE2, , arg2) \
  param(TYPE3, , arg3) \
  param(TYPE4, , arg4) \
  param(TYPE5, , arg5)

#define FOR_EACH_PARAM_OF_FXRbCallLongMethod_5(param) \
  param(ID, , func) \
  param(TYPE1, , arg1) \
  param(TYPE2, , arg2) \
  param(TYPE3, , arg3)

#define FOR_EACH_PARAM_OF_FXRbCallUIntMethod_3(param) \
  param(ID, , func) \
  param(TYPE1, , arg1)

#define FOR_EACH_PARAM_OF_FXRbCallGLObjectMethod_2(param) \
  param(ID, , func)

#define FOR_EACH_PARAM_OF_FXRbCallGLObjectMethod_3(param) \
  param(ID, , func) \
  param(TYPE1, , arg1)

#define FOR_EACH_PARAM_OF_FXRbCallGLObjectMethod_4(param) \
  param(ID, , func) \
  param(TYPE1, , arg1) \
  param(TYPE2, , arg2)

#define FOR_EACH_PARAM_OF_FXRbCallStringMethod_2(param) \
  param(ID, , func)

#define FOR_EACH_PARAM_OF_FXRbCallCStringMethod_4(param) \
  param(ID, , func) \
  param(TYPE1, , arg1) \
  param(TYPE2, , arg2)

#define FOR_EACH_PARAM_OF_FXRbCallCStringMethod_5(param) \
  param(ID, , func) \
  param(TYPE1, , arg1) \
  param(TYPE2, , arg2) \
  param(TYPE3, , arg3)

#define FOR_EACH_PARAM_OF_FXRbCallGLObjectArrayMethod_6(param) \
  param(ID, , func) \
  param(TYPE1, , arg1) \
  param(TYPE2, , arg2) \
  param(TYPE3, , arg3) \
  param(TYPE4, , arg4)

#define FOR_EACH_PARAM_OF_FXRbCallTableItemMethod_5(param) \
  param(ID, , func) \
  param(TYPE1, , arg1) \
  param(TYPE2, , arg2) \
  param(TYPE3, , arg3)

#define FOR_EACH_PARAM_OF_FXRbCallFileAssocMethod_3(param) \
  param(ID, , func) \
  param(TYPE1, , arg1)

#define FOR_EACH_PARAM_OF_FXRbCallIconMethod_2(param) \
  param(ID, , func)

#define FOR_EACH_PARAM_OF_FXRbCallIconMethod_4(param) \
  param(ID, , func) \
  param(TYPE1, &, arg1) \
  param(TYPE2, &, arg2)

#define FOR_EACH_PARAM_OF_FXRbCallIconMethod_6(param) \
  param(ID, , func) \
  param(TYPE1, &, arg1) \
  param(TYPE2, &, arg2) \
  param(TYPE3, &, arg3) \
  param(TYPE4, &, arg4)

#define FOR_EACH_PARAM_OF_FXRbCallImageMethod_4(param) \
  param(ID, , func) \
  param(TYPE1, &, arg1) \
  param(TYPE2, &, arg2)

#define FOR_EACH_PARAM_OF_FXRbCallImageMethod_6(param) \
  param(ID, , func) \
  param(TYPE1, &, arg1) \
  param(TYPE2, &, arg2) \
  param(TYPE3, &, arg3) \
  param(TYPE4, &, arg4)

#define FOR_EACH_PARAM_OF_FXRbCallWindowMethod_3(param) \
  param(ID, , func) \
  param(TYPE1, , arg1)

#define FOR_EACH_PARAM_OF_FXRbCallColorMethod_4(param) \
  param(ID, , func) \
  param(TYPE1, , arg1) \
  param(TYPE2, , arg2)

#define FOR_EACH_PARAM_OF_FXRbCallRangeMethod_2(param) \
  param(ID, , func)

#define FOR_EACH_PARAM_OF_FXRbCallWCharMethod_2(param) \
  param(ID, , func)

#define FOR_EACH_PARAM_OF_FXRbCallSetDashes_5(param) \
  param(ID, , func) \
  param(TYPE1, , arg1) \
  param(TYPE2, , arg2) \
  param(TYPE3, , arg3)

#define FOR_EACH_PARAM_OF_FXRbLookupHandler_2(param) \
  param(ITEMB, , itemb)

#define FOR_EACH_PARAM_OF_FXRbHandleMessage_5(param) \
  param(ID, , func) \
  param(TYPE1, , arg1) \
  param(TYPE2, , arg2) \
  param(TYPE3, , arg3)

#define FOR_EACH_PARAM_OF_FXRbComboBox_sortFunc_2(param) \
  param(ITEMB, , itemb)

#define FOR_EACH_PARAM_OF_FXRbFoldingList_sortFunc_2(param) \
  param(ITEMB, , itemb)

#define FOR_EACH_PARAM_OF_FXRbIconList_sortFunc_2(param) \
  param(ITEMB, , itemb)

#define FOR_EACH_PARAM_OF_FXRbList_sortFunc_2(param) \
  param(ITEMB, , itemb)

#define FOR_EACH_PARAM_OF_FXRbListBox_sortFunc_2(param) \
  param(ITEMB, , itemb)

#define FOR_EACH_PARAM_OF_FXRbTreeList_sortFunc_2(param) \
  param(ITEMB, , itemb)

#define FOR_EACH_PARAM_OF_FXRbCallDCDrawMethod_5(param) \
  param(ID, , func) \
  param(TYPE1, , arg1) \
  param(TYPE2, , arg2) \
  param(TYPE3, &, arg3)

#define FOR_EACH_PARAM_OF_FXRbCallDCDrawMethod_6(param) \
  param(ID, , func) \
  param(TYPE1, , arg1) \
  param(TYPE2, , arg2) \
  param(TYPE3, , arg3) \
  param(TYPE4, , arg4)

#define FOR_EACH_PARAM_OF_FXRbCallTreeItemMethod_4(param) \
  param(ID, , func) \
  param(TYPE1, , arg1) \
  param(TYPE2, , arg2)

#define FOR_EACH_PARAM_OF_FXRbCallFoldingItemMethod_4(param) \
  param(ID, , func) \
  param(TYPE1, , arg1) \
  param(TYPE2, , arg2)

#define FOR_EACH_PARAM_OF_FXRbApp_onChoreThreads_4(param) \
  param(ID, , func) \
  param(TYPE1, , arg1) \
  param(TYPE2, , arg2)


/* function( name, void_or_nonvoid, returntype, firstparamtype, firstparamname, paramcount ) */
#define FOR_EACH_CALLBACK_FUNCTION(function) \
  function(FXRbCallVoidMethod, GVL_TYPE_VOID, void, RECV, recv, 2) \
  function(FXRbCallVoidMethod, GVL_TYPE_VOID, void, RECV, recv, 3) \
  function(FXRbCallVoidMethod, GVL_TYPE_VOID, void, RECV, recv, 4) \
  function(FXRbCallVoidMethod, GVL_TYPE_VOID, void, RECV, recv, 5) \
  function(FXRbCallVoidMethod, GVL_TYPE_VOID, void, RECV, recv, 6) \
  function(FXRbCallVoidMethod, GVL_TYPE_VOID, void, RECV, recv, 7) \
  function(FXRbCallVoidMethod, GVL_TYPE_VOID, void, RECV, recv, 8) \
  function(FXRbCallVoidMethod, GVL_TYPE_VOID, void, RECV, recv, 9) \
  function(FXRbCallVoidMethod, GVL_TYPE_VOID, void, RECV, recv, 11) \
  function(FXRbCallBoolMethod, GVL_TYPE_NONVOID, bool, RECV, recv, 2) \
  function(FXRbCallBoolMethod, GVL_TYPE_NONVOID, bool, RECV, recv, 3) \
  function(FXRbCallBoolMethod, GVL_TYPE_NONVOID, bool, RECV, recv, 4) \
  function(FXRbCallBoolMethod, GVL_TYPE_NONVOID, bool, RECV, recv, 5) \
  function(FXRbCallBoolMethod, GVL_TYPE_NONVOID, bool, RECV, recv, 7) \
  function(FXRbCallIntMethod, GVL_TYPE_NONVOID, FXint, RECV, recv, 2) \
  function(FXRbCallIntMethod, GVL_TYPE_NONVOID, FXint, RECV, recv, 3) \
  function(FXRbCallIntMethod, GVL_TYPE_NONVOID, FXint, RECV, recv, 4) \
  function(FXRbCallIntMethod, GVL_TYPE_NONVOID, FXint, RECV, recv, 7) \
  function(FXRbCallLongMethod, GVL_TYPE_NONVOID, FXint, RECV, recv, 5) \
  function(FXRbCallUIntMethod, GVL_TYPE_NONVOID, FXint, RECV, recv, 3) \
  function(FXRbCallGLObjectMethod, GVL_TYPE_NONVOID, FXGLObject*, RECV, recv, 2) \
  function(FXRbCallGLObjectMethod, GVL_TYPE_NONVOID, FXGLObject*, RECV, recv, 3) \
  function(FXRbCallGLObjectMethod, GVL_TYPE_NONVOID, FXGLObject*, RECV, recv, 4) \
  function(FXRbCallStringMethod, GVL_TYPE_NONVOID, FXString, RECV, recv, 2) \
  function(FXRbCallCStringMethod, GVL_TYPE_NONVOID, const FXchar*, RECV, recv, 4) \
  function(FXRbCallCStringMethod, GVL_TYPE_NONVOID, const FXchar*, RECV, recv, 5) \
  function(FXRbCallGLObjectArrayMethod, GVL_TYPE_NONVOID, FXGLObject**, RECV, recv, 6) \
  function(FXRbCallTableItemMethod, GVL_TYPE_NONVOID, FXTableItem*, RECV, recv, 5) \
  function(FXRbCallFileAssocMethod, GVL_TYPE_NONVOID, FXFileAssoc*, RECV, recv, 3) \
  function(FXRbCallIconMethod, GVL_TYPE_NONVOID, FXIcon*, RECV, recv, 2) \
  function(FXRbCallIconMethod, GVL_TYPE_NONVOID, FXIcon*, RECV, recv, 4) \
  function(FXRbCallIconMethod, GVL_TYPE_NONVOID, FXIcon*, RECV, recv, 6) \
  function(FXRbCallImageMethod, GVL_TYPE_NONVOID, FXImage*, RECV, recv, 4) \
  function(FXRbCallImageMethod, GVL_TYPE_NONVOID, FXImage*, RECV, recv, 6) \
  function(FXRbCallWindowMethod, GVL_TYPE_NONVOID, FXWindow*, RECV, recv, 3) \
  function(FXRbCallColorMethod, GVL_TYPE_NONVOID, FXColor, RECV, recv, 4) \
  function(FXRbCallRangeMethod, GVL_TYPE_NONVOID, FXRangef, RECV, recv, 2) \
  function(FXRbCallWCharMethod, GVL_TYPE_NONVOID, FXwchar, RECV, recv, 2) \
  function(FXRbCallSetDashes, GVL_TYPE_VOID, void, RECV, recv, 5) \
  function(FXRbLookupHandler, GVL_TYPE_NONVOID, ID, RECV, recv, 2) \
  function(FXRbHandleMessage, GVL_TYPE_NONVOID, long, RECV, recv, 5) \
  function(FXRbComboBox_sortFunc, GVL_TYPE_NONVOID, FXint, ITEMA, itema, 2) \
  function(FXRbFoldingList_sortFunc, GVL_TYPE_NONVOID, FXint, ITEMA, itema, 2) \
  function(FXRbIconList_sortFunc, GVL_TYPE_NONVOID, FXint, ITEMA, itema, 2) \
  function(FXRbList_sortFunc, GVL_TYPE_NONVOID, FXint, ITEMA, itema, 2) \
  function(FXRbListBox_sortFunc, GVL_TYPE_NONVOID, FXint, ITEMA, itema, 2) \
  function(FXRbTreeList_sortFunc, GVL_TYPE_NONVOID, FXint, ITEMA, itema, 2) \
  function(FXRbCallDCDrawMethod, GVL_TYPE_VOID, void, RECV, recv, 5) \
  function(FXRbCallDCDrawMethod, GVL_TYPE_VOID, void, RECV, recv, 6) \
  function(FXRbCallTreeItemMethod, GVL_TYPE_NONVOID, FXTreeItem*, RECV, recv, 4) \
  function(FXRbCallFoldingItemMethod, GVL_TYPE_NONVOID, FXFoldingItem*, RECV, recv, 4) \
  function(FXRbApp_onChoreThreads, GVL_TYPE_NONVOID, long, RECV, recv, 4) \


FOR_EACH_CALLBACK_FUNCTION( DEFINE_GVLCB_STUB_DECL )
FOR_EACH_CALLBACK_FUNCTION( DEFINE_GVLCB_WRAPPER_STRUCT )
FOR_EACH_CALLBACK_FUNCTION( DEFINE_GVLCB_SKELETON )
FOR_EACH_CALLBACK_FUNCTION( DEFINE_GVLCB_STUB )

#endif /* end __gvl_wrappers_h */
