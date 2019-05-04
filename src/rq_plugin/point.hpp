#ifndef POINT_HPP
#define POINT_HPP

namespace rq {

// change to point vector
template <typename T>
class CPoint
{
public:
	CPoint(const T& x = 0, const T& y = 0)
		: m_x(x),
		  m_y(y)
	{}

	inline T x() const
	{
		return m_x;
	}

	inline T y() const
	{
		return m_y;
	}

	inline void setX(const T& x)
	{
		m_x = x;
	}

	inline void setY(const T& y)
	{
		m_y = y;
	}

	T operator[](int i) const
	{
		if (i > 2)
			// throw;
			return -1;
		if (i == 0)
			return m_x;
		return m_y;
	}

	bool operator==(const CPoint<T>& point)
	{
		return (point.x() == m_x && point.y() == m_y);
	}

private:
	T m_x;
	T m_y;
};

}
#endif