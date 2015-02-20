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

#if defined(HAVE_RB_THREAD_CALL_WITHOUT_GVL)
extern "C" void *rb_thread_call_without_gvl(void *(*func)(void *), void *data1,
        rb_unblock_function_t *ubf, void *data2);
#endif

#define DEFINE_PARAM_LIST1(type, name) \
  , name

#define DEFINE_PARAM_LIST2(type, name) \
  , p->params.name

#define DEFINE_PARAM_LIST3(type, name) \
  , type name

#define DEFINE_PARAM_DECL(type, name) \
  type name;

#define DEFINE_GVL_WRAPPER_STRUCT(klass, name, baseclass, when_non_void, rettype, firstparamtype, firstparamname) \
  struct gvl_wrapper_##klass##_##name##_params { \
    struct { \
      firstparamtype firstparamname; \
      FOR_EACH_PARAM_OF_##baseclass##_##name(DEFINE_PARAM_DECL) \
    } params; \
    when_non_void( rettype retval; ) \
  };

extern __thread int g_fxrb_thread_has_gvl;

#define DEFINE_GVL_SKELETON(klass, name, baseclass, when_non_void, rettype, firstparamtype, firstparamname) \
  static void * gvl_##klass##_##name##_skeleton( void *data ){ \
    struct gvl_wrapper_##klass##_##name##_params *p = (struct gvl_wrapper_##klass##_##name##_params*)data; \
    g_fxrb_thread_has_gvl = 0; \
    when_non_void( p->retval = ) \
      klass##_##name##_gvl( p->params.firstparamname FOR_EACH_PARAM_OF_##baseclass##_##name(DEFINE_PARAM_LIST2) ); \
    g_fxrb_thread_has_gvl = 1; \
    return NULL; \
  }

#if defined(HAVE_RB_THREAD_CALL_WITHOUT_GVL)
  #define DEFINE_GVL_STUB(klass, name, baseclass, when_non_void, rettype, firstparamtype, firstparamname) \
    rettype klass##_##name(firstparamtype firstparamname FOR_EACH_PARAM_OF_##baseclass##_##name(DEFINE_PARAM_LIST3)){ \
      struct gvl_wrapper_##klass##_##name##_params params = { \
        {firstparamname FOR_EACH_PARAM_OF_##baseclass##_##name(DEFINE_PARAM_LIST1)}, when_non_void((rettype)0) \
      }; \
      rb_thread_call_without_gvl(gvl_##klass##_##name##_skeleton, &params, RUBY_UBF_IO, 0); \
      when_non_void( return params.retval; ) \
    }
#else
  #define DEFINE_GVL_STUB(klass, name, baseclass, when_non_void, rettype, firstparamtype, firstparamname) \
    rettype klass##_##name(firstparamtype firstparamname FOR_EACH_PARAM_OF_##baseclass##_##name(DEFINE_PARAM_LIST3)){ \
      return klass##_##name##_gvl(firstparamname FOR_EACH_PARAM_OF_##baseclass##_##name(DEFINE_PARAM_LIST1)); \
    }
#endif

#define DEFINE_GVL_STUB_DECL(klass, name, baseclass, when_non_void, rettype, firstparamtype, firstparamname) \
  rettype klass##_##name( firstparamtype firstparamname FOR_EACH_PARAM_OF_##baseclass##_##name(DEFINE_PARAM_LIST3));

#define GVL_TYPE_VOID(string)
#define GVL_TYPE_NONVOID(string) string


/*
* Definitions of blocking functions and their parameters
*/

#define FOR_EACH_PARAM_OF_FXImage_loadPixels(param) \
  param(FXStream&, store)
#define FOR_EACH_PARAM_OF_FXImage_savePixels(param) \
  param(FXStream&, store)

/* function( name, void_or_nonvoid, returntype, firstparamtype, firstparamname ) */
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
  function(FXXPMIcon, savePixels, FXImage, GVL_TYPE_NONVOID, bool, const FXXPMIcon *, self)


FOR_EACH_BLOCKING_FUNCTION( DEFINE_GVL_STUB_DECL )

#endif /* end __gvl_wrappers_h */
