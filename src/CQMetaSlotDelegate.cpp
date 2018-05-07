#include <CQMetaSlotDelegate.h>
#include <CQMetaSlotTree.h>
#include <CQUtil.h>

CQMetaSlotDelegate::
CQMetaSlotDelegate(CQMetaSlotTree *tree) :
 QItemDelegate(tree), tree_(tree)
{
}

void
CQMetaSlotDelegate::
paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
  QItemDelegate::paint(painter, option, index);
}
