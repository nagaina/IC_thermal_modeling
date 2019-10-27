#include "parser.hpp"

namespace parser
{
std::vector<ICnodePtr> CParser::parse(const std::vector<Token>& tokens)
{
	m_tokens.clear();
	m_tokens = tokens;
	m_current = 0;
	std::vector<ICnodePtr> nodes;

	while (!isAtEnd())
	{
		nodes.push_back(_parse());
	}

	return nodes;
}

bool CParser::isAtEnd() const
{
	return peek().m_type == _EOF;
}

Token CParser::peek() const
{
	return m_tokens[m_current];
}

Token CParser::previous() const
{
	return m_tokens[m_current - 1];
}

Token CParser::advance() const
{
	if (!isAtEnd())
		++m_current;
	return previous();
}

bool CParser::check(ETokenType type) const
{
	if (isAtEnd())
		return false;

	return peek().m_type == type;
}

bool CParser::match(ETokenType type) const
{
	if (check(type))
	{
		advance();
		return true;
	}

	return false;
}

ICnodePtr CParser::_parse()  const
{
	ICnodePtr newNode = std::shared_ptr<ICnode>(new ICnode());
	if (match(_X) && match(_DELIMITER))
	{
		if (check(_NUMBER))
		{
			newNode->setX(atof(peek().m_lexeme.c_str()));
			advance();
		}
	}

	if (match(_Y) && match(_DELIMITER))
	{
		if (check(_NUMBER))
		{
			newNode->setY(atof(peek().m_lexeme.c_str()));
			advance();
		}
	}

	if (match(_WIDTH) && match(_DELIMITER))
	{
		if (check(_NUMBER))
		{
			newNode->setW(atof(peek().m_lexeme.c_str()));
			advance();
		}
	}

	if (match(_HEIGHT) && match(_DELIMITER))
	{
		if (check(_NUMBER))
		{
			newNode->setH(atof(peek().m_lexeme.c_str()));
			advance();
		}
	}

	if (match(_POWER) && match(_DELIMITER))
	{
		if (check(_NUMBER))
		{
			newNode->setP(atof(peek().m_lexeme.c_str()));
			advance();
		}
	}

	if (match(_LAYER) && match(_DELIMITER))
	{
		if (check(_NUMBER))
		{
			newNode->setL(atof(peek().m_lexeme.c_str()));
			advance();
		}
	}
	return newNode;
}
}