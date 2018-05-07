#include <CQMetaLayoutTree.h>
#include <CQMetaLayoutModel.h>
#include <CQMetaLayoutDelegate.h>

CQMetaLayoutTree::
CQMetaLayoutTree(CQMetaEdit *edit) :
 CQMetaEditTree(edit)
{
  setObjectName("signalTree");

  model_ = new CQMetaLayoutModel(this);

  setModel(model_);

  delegate_ = new CQMetaLayoutDelegate(this);

  setItemDelegate(delegate_);
}
