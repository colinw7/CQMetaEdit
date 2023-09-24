#include <CQMetaWidgetTree.h>
#include <CQMetaWidgetModel.h>
#include <CQMetaWidgetDelegate.h>
#include <CQMetaEdit.h>
#include <QMouseEvent>
#include <iostream>

CQMetaWidgetTree::
CQMetaWidgetTree(CQMetaEdit *edit) :
 CQMetaEditTree(edit)
{
  setObjectName("widgetTree");

  model_ = new CQMetaWidgetModel(this);

  setModel(model_);

  delegate_ = new CQMetaWidgetDelegate(this);

  setItemDelegate(delegate_);
}

void
CQMetaWidgetTree::
mouseDoubleClickEvent(QMouseEvent *e)
{
  auto ind = indexAt(e->pos());

  //std::cerr << "mouseDoubleClickEvent: " << ind.row() << " " << ind.column() << std::endl;

  auto *obj = model_->indexObject(ind);

  if      (ind.column() == 0) {
    edit_->setObject(obj);
  }
  else if (ind.column() == 1) {
    auto *w = qobject_cast<QWidget *>(obj);

    if (w)
      edit_->showWidget(w);
  }
}
