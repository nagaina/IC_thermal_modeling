#ifndef GUI_LIB_H 
#define GUI_LIB_H

#ifdef GUI_EXPORT
#	undef GUI_EXPORT
#endif

#ifdef GUI_LIB
#	define GUI_EXPORT Q_DECL_EXPORT
#else
#	define GUI_EXPORT Q_DECL_IMPORT
#endif

#endif
