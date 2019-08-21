#include "node.hpp"
#include "rq_plugin.hpp"
#include "point.hpp"
#include "RQtree.hpp"

#ifdef OS_WINDOWS
template class RQ_PLUGIN_EXPORT rq::CPoint<int>;
template class RQ_PLUGIN_EXPORT rq::CNode<int>;
template class RQ_PLUGIN_EXPORT rq::RQtree<int>;
#endif
