#include "parser_helper.hpp"

#include <cstdio>

namespace parser
{
#ifdef OS_LINUX
void fopen_s(FILE **f, const char *name, const char *mode) {
    *f = fopen(name, mode);
    return;
}
#endif    
    
ParserHelper::ParserHelper()
{
	m_scanner = std::shared_ptr<CScanner>(new CScanner);
	m_parser = std::shared_ptr<CParser>(new CParser);
}

std::vector<ICnodePtr> ParserHelper::parseFile(const std::string& filePath)
{
	// staff file loading
	std::FILE* fptr;
	fopen_s(&fptr, filePath.c_str(), "r");
	if (fptr == nullptr)
		//exception
		return std::vector<ICnodePtr>();

	std::fseek(fptr, 0, SEEK_END);
	size_t len = std::ftell(fptr);
	std::fseek(fptr, 0, SEEK_SET);
	std::string data(len + 1, '\0');
	std::fread(&data[0], 1, len, fptr);
	fclose(fptr);

	//	parse
	return m_parser->parse(m_scanner->scanTokens(data));
}
}
