#include <CQMetaLayoutDelegate.h>
#include <CQMetaLayoutTree.h>
#include <CQUtil.h>

CQMetaLayoutDelegate::
CQMetaLayoutDelegate(CQMetaLayoutTree *tree) :
 QItemDelegate(tree), tree_(tree)
{
}

void
CQMetaLayoutDelegate::
paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
  QItemDelegate::paint(painter, option, index);
}
