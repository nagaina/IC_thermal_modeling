#ifndef TOKEN_H
#define TOKEN_H

// Includes
#include <string>

namespace parser
{
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Enum Token Type
//
enum ETokenType
{
	_NUMBER,
	_X, _Y,
	_NAME,
	_WIDTH,
	_HEIGHT,
	_POWER,
	_LAYER,
	_DELIMITER, // :
	_STRING,
	_EOF,
	_EOL
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Struct Token
//
struct Token
{
	Token(int i, ETokenType t, const std::string& l)
		: m_line(i), m_type(t), m_lexeme(l)
	{}

	size_t m_line;
	ETokenType m_type;
	std::string m_lexeme;
};
}
#endif