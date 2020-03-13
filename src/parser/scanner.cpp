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
		break;
	case '\n':
		addToken(_EOL);
		break;
	case 'x' :
	case 'X' :
		addToken(_X);
		break;
	case 'y' :
	case 'Y' :
		addToken(_Y);
		break;
	case ':':
	case '=' :
	case ';' :
	case ',' :
		addToken(_DELIMITER);
		break;
	default:
		if (isdigit(c))
			number();
		else 
			if (isalpha(c))
				identifier();
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

void CScanner::identifier()
{
	while (isalnum(peek())) advance();
	std::string text = m_source.substr(m_start, m_current - m_start);
	if (text == "layer")
		addToken(_LAYER);
	else if (text == "width")
		addToken(_WIDTH);
	else if (text == "name")
		addToken(_NAME);
	else if (text == "height")
		addToken(_HEIGHT);
	else if (text == "power")
		addToken(_POWER);
	else
		addToken(_STRING);
}
}