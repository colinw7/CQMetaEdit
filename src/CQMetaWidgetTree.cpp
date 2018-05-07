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
  QModelIndex ind = indexAt(e->pos());

  std::cerr << "mouseDoubleClickEvent: " << ind.row() << " " << ind.column() << std::endl;

  if (ind.column() == 0) {
    QWidget *w = model_->indexWidget(ind);

    edit_->setObject(w);
  }
}
