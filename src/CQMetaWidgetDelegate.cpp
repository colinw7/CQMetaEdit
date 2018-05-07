#include <CQMetaWidgetDelegate.h>
#include <CQMetaWidgetTree.h>
#include <CQUtil.h>

CQMetaWidgetDelegate::
CQMetaWidgetDelegate(CQMetaWidgetTree *tree) :
 QItemDelegate(tree), tree_(tree)
{
}

void
CQMetaWidgetDelegate::
paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
  QItemDelegate::paint(painter, option, index);
}
