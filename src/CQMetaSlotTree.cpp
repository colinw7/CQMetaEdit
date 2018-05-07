#include <CQMetaSlotTree.h>
#include <CQMetaSlotModel.h>
#include <CQMetaSlotDelegate.h>

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
