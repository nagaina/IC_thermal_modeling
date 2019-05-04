#ifndef RQ_PLUGIN_LIB_HPP 
#define RQ_PLUGIN_LIB_HPP

#ifdef RQ_PLUGIN_EXPORT
#	undef RQ_PLUGIN_EXPORT
#endif

#ifdef RQ_PLUGIN_LIB
#	define RQ_PLUGIN_EXPORT __declspec(dllexport)
#else
#	define RQ_PLUGIN_EXPORT __declspec(dllimport)
#endif

#endif

