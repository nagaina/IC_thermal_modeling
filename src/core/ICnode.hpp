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
	double m_X = 0;
	double m_Y = 0;
	double m_W = 0;
	double m_H = 0;
	double m_P = 0;
	double m_L = 0;
	std::string m_name;
};

using ICnodePtr = std::shared_ptr<ICnode>;
#endif