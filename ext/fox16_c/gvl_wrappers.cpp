/*
 * gvl_wrappers.c - Wrapper functions for locking/unlocking the Ruby GVL
 *
 */

#include "FXRbCommon.h"

__thread int g_fxrb_thread_has_gvl = 1;

FOR_EACH_BLOCKING_FUNCTION( DEFINE_GVL_WRAPPER_STRUCT );
FOR_EACH_BLOCKING_FUNCTION( DEFINE_GVL_SKELETON );
FOR_EACH_BLOCKING_FUNCTION( DEFINE_GVL_STUB );
