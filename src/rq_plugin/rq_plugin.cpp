#include "node.hpp"
#include "point.hpp"
#include "RQtree.hpp"

#ifndef OS_LINUX
template class  rq::CPoint<int>;
template class  rq::CNode<int>;
template class  rq::RQtree<int>;
#endif
