#include "scanner.hpp"

namespace parser
{
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Scanner implementation
//
std::vector<Token> CScanner::scanTokens(const std::string& source)
{
	m_tokens.clear();
	m_source = source;
	m_start = 0;
	m_current = 0;
	while (!isAtEnd())
	{
		m_start = m_current;
		scanToken();
		++m_line; //?
	}
	m_tokens.push_back(Token(m_line, _EOF, "End of line"));
	++m_line;
	return m_tokens;
}

bool CScanner::isAtEnd() const
{
	return m_current >= m_source.length();
}

void CScanner::scanToken()
{
	char c = advance();
	switch (c)
	{
	case ' ':
	case '\t':
	case '\n':
		break;
	case 'x' :
	case 'X' :
		addToken(_X);
		break;
	case 'y' :
	case 'Y' :
		addToken(_Y);
		break;
	case 'w':
	case 'W':
		addToken(_WIDTH);
		break;
	case 'h':
	case 'H':
		addToken(_HEIGHT);
		break;
	case 'p':
	case 'P':
		addToken(_POWER);
		break;
	case 'l':
	case 'L':
		addToken(_LAYER);
		break;
	case ':':
		addToken(_DELIMITER);
		break;
	default:
		if (isdigit(c))
		{
			number();
		} 
		else
		{
			// Throw error;
		}
	}
}

char CScanner::advance()
{
	++m_current;
	return m_source.at(m_current - 1);
}

void CScanner::number()
{
	while (isdigit(peek()))
		advance();
	if (peek() == '.' && isdigit(peekNext()))
	{
		advance();
		while (isdigit(peek()))
			advance();
	}
	addToken(_NUMBER);
}

char CScanner::peek() const
{
	if (isAtEnd())
		return '\0';
	return m_source.at(m_current);
}

char CScanner::peekNext() const
{
	if (m_current + 1 >= m_source.length())
		return '\0';
	return m_source.at(m_current + 1);
}

void CScanner::addToken(ETokenType type)
{
	std::string text(m_source.substr(m_start, m_current - m_start));
	m_tokens.push_back(Token(m_line, type, text));
}
}