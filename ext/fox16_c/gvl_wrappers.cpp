/*
 * gvl_wrappers.c - Wrapper functions for locking/unlocking the Ruby GVL
 *
 */

#include "FXRbCommon.h"

FOR_EACH_BLOCKING_FUNCTION( DEFINE_GVL_WRAPPER_STRUCT );
FOR_EACH_BLOCKING_FUNCTION( DEFINE_GVL_SKELETON );
FOR_EACH_BLOCKING_FUNCTION( DEFINE_GVL_STUB );
