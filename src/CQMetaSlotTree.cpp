#include <CQMetaSlotTree.h>
#include <CQMetaSlotModel.h>
#include <CQMetaSlotDelegate.h>
#include <CQMetaEdit.h>
#include <CQUtil.h>

#include <QMouseEvent>
//#include <iostream>

CQMetaSlotTree::
CQMetaSlotTree(CQMetaEdit *edit) :
 CQMetaEditTree(edit)
{
  setObjectName("slotTree");

  model_ = new CQMetaSlotModel(this);

  setModel(model_);

  delegate_ = new CQMetaSlotDelegate(this);

  setItemDelegate(delegate_);
}

void
CQMetaSlotTree::
mouseDoubleClickEvent(QMouseEvent *event)
{
  const QPoint &pos = event->pos();

  auto ind = indexAt(pos);

  if (! ind.isValid()) return;

  auto slotName = model()->data(ind).toString();
  //std::cerr << slotName.toStdString() << "\n";

  QString values; // TODO

  if (edit_->object())
    CQUtil::activateSlot(edit_->object(), slotName.toLatin1().data(), values.toLatin1().data());
}
