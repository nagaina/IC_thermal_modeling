#ifndef PARSER_LIB_HPP 
#define PARSER_LIB_HPP

#ifdef PARSER_EXPORT
#	undef PARSER_EXPORT
#endif

#ifdef PARSER_LIB
#	define PARSER_EXPORT __declspec(dllexport)
#else
#	define PARSER_EXPORT __declspec(dllimport)
#endif

#endif