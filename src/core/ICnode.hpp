#ifndef IC_NODE_H
#define IC_NODE_H

//
//Includes
//

#include <memory>
#include <string>

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
	void setWidth(double W);
	void setHeight(double H);
	void setPower(double P);
	void setLayer(double L);
	void setName(const std::string& name);

	double X() const;
	double Y() const;
	double Width() const;
	double Power() const;
	double Height() const;
	double Layer() const;
	std::string Name() const;

private:
	double m_X;
	double m_Y;
	double m_W;
	double m_H;
	double m_P;
	double m_L;
	std::string m_name;
};

using ICnodePtr = std::shared_ptr<ICnode>;
#endif