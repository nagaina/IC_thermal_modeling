#ifndef SCANNER_H
#define SCANNER_H
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Includes
//
#include "token.hpp"

// Stl
#include <vector>
#include <memory>

namespace parser
{
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Class Scanner
//
class CScanner
{
public:
	CScanner() : 
		m_line(1) {}

	std::vector<Token> scanTokens(const std::string&);

private:
	bool isAtEnd() const;
	void scanToken();
	char advance();
	void number();
	void addToken(ETokenType);
	char peek() const;
	char peekNext() const;
	void identifier();

private:
	size_t m_line;
	std::vector<Token> m_tokens;
	std::string m_source;
	size_t m_start;
	size_t m_current;
};

using CScannerPtr = std::shared_ptr<CScanner>;

}
#endif