// my_debug.h

#ifndef _MY_DEBUG_H_
#define _MY_DEBUG_H_

/*
 * Macros to help debugging
 */

#undef PDEBUG
#ifdef SCULLC_DEBUG
#  ifdef __KERNEL__
#    define PDEBUG(fmt, args...) printk( KERN_DEBUG "scullc: " fmt, ## args)
#  else
#    define PDEBUG(fmt, args...) fprintf( stderr, fmt, ## args)
#  endif
#else
#  define PDEBUG(fmt, args...)
#endif

#undef PDEBUGG
#define PDEBUGG(fmt, args...)

#endif
