#ifndef PARSER_H
#define PARSER_H

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Includes
//
#include "token.hpp"
#include "../core/ICnode.hpp"

// Stl
#include <vector>
#include <memory>

namespace parser
{
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// class CParser, parse the tokens and gets the expected objects
class CParser
{
public:	
	std::vector<ICnodePtr> parse(const std::vector<Token>&);

private:
	bool isAtEnd() const;

	Token peek() const;
	Token previous() const;
	Token advance() const;

	bool check(ETokenType) const;
	bool match(ETokenType) const;

	ICnodePtr _parse() const;

private:
	std::vector<Token> m_tokens;
	mutable int m_current;
};

using CParserPtr = std::shared_ptr<CParser>;

}
#endif