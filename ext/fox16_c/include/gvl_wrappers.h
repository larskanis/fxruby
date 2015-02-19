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
	name,

#define DEFINE_PARAM_LIST2(type, name) \
	p->params.name,

#define DEFINE_PARAM_LIST3(type, name) \
	type name,

#define DEFINE_PARAM_DECL(type, name) \
	type name;

#define DEFINE_GVL_WRAPPER_STRUCT(name, when_non_void, rettype, lastparamtype, lastparamname) \
	struct gvl_wrapper_##name##_params { \
		struct { \
			FOR_EACH_PARAM_OF_##name(DEFINE_PARAM_DECL) \
			lastparamtype lastparamname; \
		} params; \
		when_non_void( rettype retval; ) \
	};

#define DEFINE_GVL_SKELETON(name, when_non_void, rettype, lastparamtype, lastparamname) \
	static void * gvl_##name##_skeleton( void *data ){ \
		struct gvl_wrapper_##name##_params *p = (struct gvl_wrapper_##name##_params*)data; \
		when_non_void( p->retval = ) \
			name##_gvl( FOR_EACH_PARAM_OF_##name(DEFINE_PARAM_LIST2) p->params.lastparamname ); \
		return NULL; \
	}

#if defined(HAVE_RB_THREAD_CALL_WITHOUT_GVL)
	#define DEFINE_GVL_STUB(name, when_non_void, rettype, lastparamtype, lastparamname) \
		rettype name(FOR_EACH_PARAM_OF_##name(DEFINE_PARAM_LIST3) lastparamtype lastparamname){ \
			struct gvl_wrapper_##name##_params params = { \
				{FOR_EACH_PARAM_OF_##name(DEFINE_PARAM_LIST1) lastparamname}, when_non_void((rettype)0) \
			}; \
			rb_thread_call_without_gvl(gvl_##name##_skeleton, &params, RUBY_UBF_IO, 0); \
			when_non_void( return params.retval; ) \
		}
#else
	#define DEFINE_GVL_STUB(name, when_non_void, rettype, lastparamtype, lastparamname) \
		rettype name(FOR_EACH_PARAM_OF_##name(DEFINE_PARAM_LIST3) lastparamtype lastparamname){ \
			return name##_gvl( FOR_EACH_PARAM_OF_##name(DEFINE_PARAM_LIST1) lastparamname ); \
		}
#endif

#define DEFINE_GVL_STUB_DECL(name, when_non_void, rettype, lastparamtype, lastparamname) \
	rettype name(FOR_EACH_PARAM_OF_##name(DEFINE_PARAM_LIST3) lastparamtype lastparamname);

#define DEFINE_GVL_TARGET_DECL(name, when_non_void, rettype, lastparamtype, lastparamname) \
  rettype name##_gvl(FOR_EACH_PARAM_OF_##name(DEFINE_PARAM_LIST3) lastparamtype lastparamname);

#define GVL_TYPE_VOID(string)
#define GVL_TYPE_NONVOID(string) string


/*
 * Definitions of blocking functions and their parameters
 */

#define FOR_EACH_PARAM_OF_FXImage_loadPixels(param) \
  param(FXImage *, self)
#define FOR_EACH_PARAM_OF_FXImage_savePixels(param) \
  param(const FXImage *, self)

#define FOR_EACH_PARAM_OF_FXBMPImage_loadPixels(param) \
  param(FXBMPImage *, self)
#define FOR_EACH_PARAM_OF_FXBMPImage_savePixels(param) \
  param(const FXBMPImage *, self)

#define FOR_EACH_PARAM_OF_FXJPGImage_loadPixels(param) \
  param(FXJPGImage *, self)
#define FOR_EACH_PARAM_OF_FXJPGImage_savePixels(param) \
  param(const FXJPGImage *, self)

#define FOR_EACH_PARAM_OF_FXGIFImage_loadPixels(param) \
  param(FXGIFImage *, self)
#define FOR_EACH_PARAM_OF_FXGIFImage_savePixels(param) \
  param(const FXGIFImage *, self)

#define FOR_EACH_PARAM_OF_FXICOImage_loadPixels(param) \
  param(FXICOImage *, self)
#define FOR_EACH_PARAM_OF_FXICOImage_savePixels(param) \
  param(const FXICOImage *, self)

#define FOR_EACH_PARAM_OF_FXPNGImage_loadPixels(param) \
  param(FXPNGImage *, self)
#define FOR_EACH_PARAM_OF_FXPNGImage_savePixels(param) \
  param(const FXPNGImage *, self)

#define FOR_EACH_PARAM_OF_FXPPMImage_loadPixels(param) \
  param(FXPPMImage *, self)
#define FOR_EACH_PARAM_OF_FXPPMImage_savePixels(param) \
  param(const FXPPMImage *, self)

#define FOR_EACH_PARAM_OF_FXPCXImage_loadPixels(param) \
  param(FXPCXImage *, self)
#define FOR_EACH_PARAM_OF_FXPCXImage_savePixels(param) \
  param(const FXPCXImage *, self)

#define FOR_EACH_PARAM_OF_FXRGBImage_loadPixels(param) \
  param(FXRGBImage *, self)
#define FOR_EACH_PARAM_OF_FXRGBImage_savePixels(param) \
  param(const FXRGBImage *, self)

#define FOR_EACH_PARAM_OF_FXTGAImage_loadPixels(param) \
  param(FXTGAImage *, self)
#define FOR_EACH_PARAM_OF_FXTGAImage_savePixels(param) \
  param(const FXTGAImage *, self)

#define FOR_EACH_PARAM_OF_FXTIFImage_loadPixels(param) \
  param(FXTIFImage *, self)
#define FOR_EACH_PARAM_OF_FXTIFImage_savePixels(param) \
  param(const FXTIFImage *, self)

#define FOR_EACH_PARAM_OF_FXXBMImage_loadPixels(param) \
  param(FXXBMImage *, self)
#define FOR_EACH_PARAM_OF_FXXBMImage_savePixels(param) \
  param(const FXXBMImage *, self)

#define FOR_EACH_PARAM_OF_FXXPMImage_loadPixels(param) \
  param(FXXPMImage *, self)
#define FOR_EACH_PARAM_OF_FXXPMImage_savePixels(param) \
  param(const FXXPMImage *, self)

/* function( name, void_or_nonvoid, returntype, lastparamtype, lastparamname ) */
#define FOR_EACH_BLOCKING_FUNCTION(function) \
  function(FXImage_loadPixels, GVL_TYPE_NONVOID, bool, FXStream&, store) \
  function(FXImage_savePixels, GVL_TYPE_NONVOID, bool, FXStream&, store) \
  function(FXBMPImage_loadPixels, GVL_TYPE_NONVOID, bool, FXStream&, store) \
  function(FXBMPImage_savePixels, GVL_TYPE_NONVOID, bool, FXStream&, store) \
  function(FXJPGImage_loadPixels, GVL_TYPE_NONVOID, bool, FXStream&, store) \
  function(FXJPGImage_savePixels, GVL_TYPE_NONVOID, bool, FXStream&, store) \
  function(FXGIFImage_loadPixels, GVL_TYPE_NONVOID, bool, FXStream&, store) \
  function(FXGIFImage_savePixels, GVL_TYPE_NONVOID, bool, FXStream&, store) \
  function(FXICOImage_loadPixels, GVL_TYPE_NONVOID, bool, FXStream&, store) \
  function(FXICOImage_savePixels, GVL_TYPE_NONVOID, bool, FXStream&, store) \
  function(FXPNGImage_loadPixels, GVL_TYPE_NONVOID, bool, FXStream&, store) \
  function(FXPNGImage_savePixels, GVL_TYPE_NONVOID, bool, FXStream&, store) \
  function(FXPPMImage_loadPixels, GVL_TYPE_NONVOID, bool, FXStream&, store) \
  function(FXPPMImage_savePixels, GVL_TYPE_NONVOID, bool, FXStream&, store) \
  function(FXPCXImage_loadPixels, GVL_TYPE_NONVOID, bool, FXStream&, store) \
  function(FXPCXImage_savePixels, GVL_TYPE_NONVOID, bool, FXStream&, store) \
  function(FXRGBImage_loadPixels, GVL_TYPE_NONVOID, bool, FXStream&, store) \
  function(FXRGBImage_savePixels, GVL_TYPE_NONVOID, bool, FXStream&, store) \
  function(FXTGAImage_loadPixels, GVL_TYPE_NONVOID, bool, FXStream&, store) \
  function(FXTGAImage_savePixels, GVL_TYPE_NONVOID, bool, FXStream&, store) \
  function(FXTIFImage_loadPixels, GVL_TYPE_NONVOID, bool, FXStream&, store) \
  function(FXTIFImage_savePixels, GVL_TYPE_NONVOID, bool, FXStream&, store) \
  function(FXXBMImage_loadPixels, GVL_TYPE_NONVOID, bool, FXStream&, store) \
  function(FXXBMImage_savePixels, GVL_TYPE_NONVOID, bool, FXStream&, store) \
  function(FXXPMImage_loadPixels, GVL_TYPE_NONVOID, bool, FXStream&, store) \
  function(FXXPMImage_savePixels, GVL_TYPE_NONVOID, bool, FXStream&, store)


FOR_EACH_BLOCKING_FUNCTION( DEFINE_GVL_STUB_DECL )
FOR_EACH_BLOCKING_FUNCTION( DEFINE_GVL_TARGET_DECL )

#endif /* end __gvl_wrappers_h */
