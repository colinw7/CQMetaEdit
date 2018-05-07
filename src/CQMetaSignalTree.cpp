#include <CQMetaSignalTree.h>
#include <CQMetaSignalModel.h>
#include <CQMetaSignalDelegate.h>

CQMetaSignalTree::
CQMetaSignalTree(CQMetaEdit *edit) :
 CQMetaEditTree(edit)
{
  setObjectName("signalTree");

  model_ = new CQMetaSignalModel(this);

  setModel(model_);

  delegate_ = new CQMetaSignalDelegate(this);

  setItemDelegate(delegate_);
}
