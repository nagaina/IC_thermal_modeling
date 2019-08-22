#ifndef PARSER_HELPER_HPP
#define PARSER_HELPER_HPP

#include "ICnode.hpp"
#include "scanner.hpp"
#include "parser.hpp"

#include <string>
#include <vector>

namespace parser
{
class ParserHelper
{
public:
	ParserHelper();

	std::vector<ICnodePtr> parseFile(const std::string&);

private:
	CScannerPtr m_scanner = nullptr;
	CParserPtr m_parser = nullptr;
};

using ParserHelperPtr = std::shared_ptr<ParserHelper>;

}

#endif