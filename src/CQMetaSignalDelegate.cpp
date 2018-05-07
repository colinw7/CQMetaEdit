#include <CQMetaSignalDelegate.h>
#include <CQMetaSignalTree.h>
#include <CQUtil.h>

CQMetaSignalDelegate::
CQMetaSignalDelegate(CQMetaSignalTree *tree) :
 QItemDelegate(tree), tree_(tree)
{
}

void
CQMetaSignalDelegate::
paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
  QItemDelegate::paint(painter, option, index);
}
