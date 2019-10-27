#ifndef IC_NODE_H
#define IC_NODE_H

//
//Includes
//

#include <memory>

namespace parser
{
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	class ICNode
//	implementation of the object representing IC coords	
//
class ICnode
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
	void setH(double H);
	void setP(double P);
	void setL(double L);

	double X() const;
	double Y() const;
	double W() const;
	double P() const;
	double H() const;
	double L() const;

private:
	double m_X;
	double m_Y;
	double m_W;
	double m_H;
	double m_P;
	double m_L;
};

using ICnodePtr = std::shared_ptr<ICnode>;
}
#endif