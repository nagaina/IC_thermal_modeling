#ifndef node_hpp
#define node_hpp

#include "rq_plugin.hpp"
#include "point.hpp"

#include <memory>

namespace rq {

template <typename T>
class CNode;

template <typename T>
using CNodePtr = std::shared_ptr<CNode<T>>;

template <typename T>
class CNode
{
public:
	CNode(const CPoint<T>& = 0, CNodePtr<T> = 0, CNodePtr<T> = 0);
	~CNode() = default;

	CPoint<T> m_point;
	CNodePtr<T> m_left_ptr;
	CNodePtr<T> m_right_ptr;
	size_t m_index; //unique index
};

template <typename T>
CNode<T>::CNode(const CPoint<T>& p, CNodePtr<T> left, CNodePtr<T> right)
	: m_point(p)
	, m_left_ptr(left)
	, m_right_ptr(right)
{}

}
#endif