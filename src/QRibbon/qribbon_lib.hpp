#ifndef QRIBBON_LIB_H 
#define QRIBBON_LIB_H

#ifdef QRIBBON_EXPORT
#	undef QRIBBON_EXPORT
#endif

#ifdef QRIBBON_LIB
#	define QRIBBON_EXPORT Q_DECL_EXPORT
#else
#	define QRIBBON_EXPORT Q_DECL_IMPORT
#endif

#endif
