#ifndef IC_NODE_H
#define IC_NODE_H

//
//Includes
//

#include "parser_lib.hpp"

#include <memory>

namespace parser
{
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	class ICNode
//	implementation of the object representing IC coords	
//
class PARSER_EXPORT ICnode
{
public:
	//
	//	Methods
	//
	ICnode() {}
	~ICnode() {}

	void setX(double x);
	void setY(double y);
	void setW(double W);

	double X() const;
	double Y() const;
	double W() const;

private:
	double m_X;
	double m_Y;
	double m_W;
};

using ICnodePtr = std::shared_ptr<ICnode>;
}
#endif