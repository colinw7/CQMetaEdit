#include <CQMetaPropertyTree.h>
#include <CQMetaPropertyModel.h>
#include <CQMetaPropertyDelegate.h>

CQMetaPropertyTree::
CQMetaPropertyTree(CQMetaEdit *edit) :
 CQMetaEditTree(edit)
{
  setObjectName("propertyTree");

  setEditTriggers(QAbstractItemView::DoubleClicked | QAbstractItemView::EditKeyPressed);

  model_ = new CQMetaPropertyModel(this);

  setModel(model_);

  delegate_ = new CQMetaPropertyDelegate(this);

  setItemDelegate(delegate_);
}
