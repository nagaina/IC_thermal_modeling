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
		auto p = _parse();
		if (p != nullptr)
			nodes.emplace_back(p);
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
	while (!match(_EOL) && !isAtEnd())
	{
		if (match(_NAME) && match(_DELIMITER))
		{
			if (check(_STRING) || check(_NUMBER))
			{
				newNode->setName(peek().m_lexeme.c_str());
				advance();
			}
		}
		else if (match(_X) && match(_DELIMITER))
		{
			if (check(_NUMBER))
			{
				newNode->setX(atof(peek().m_lexeme.c_str()));
				advance();
			}
		}

		else if (match(_WIDTH) && match(_DELIMITER))
		{
			if (check(_NUMBER))
			{
				newNode->setWidth(atof(peek().m_lexeme.c_str()));
				advance();
			}
		}

		else if (match(_HEIGHT) && match(_DELIMITER))
		{
			if (check(_NUMBER))
			{
				newNode->setHeight(atof(peek().m_lexeme.c_str()));
				advance();
			}
		}

		else if (match(_POWER) && match(_DELIMITER))
		{
			if (check(_NUMBER))
			{
				newNode->setPower(atof(peek().m_lexeme.c_str()));
				advance();
			}
		}

		else if (match(_Y) && match(_DELIMITER))
		{
			if (check(_NUMBER))
			{
				newNode->setY(atof(peek().m_lexeme.c_str()));
				advance();
			}
		}

		else if (match(_LAYER) && match(_DELIMITER))
		{
			if (check(_NUMBER))
			{
				newNode->setLayer(atof(peek().m_lexeme.c_str()));
				advance();
			}
		}
		else
			advance();
	}
	return newNode;
}
}