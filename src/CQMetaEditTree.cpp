#include <CQMetaEditTree.h>
#include <CQMetaEdit.h>
#include <CQMetaEditModel.h>
#include <QHeaderView>

CQMetaEditTree::
CQMetaEditTree(CQMetaEdit *edit) :
 CQTreeView(edit), edit_(edit)
{
  setAlternatingRowColors(true);

  setUniformRowHeights(true);

  header()->setStretchLastSection(true);
}

CQMetaEdit *
CQMetaEditTree::
metaEdit() const
{
  return edit_.data();
}

QObject *
CQMetaEditTree::
object() const
{
  return (edit_ ? edit_->object() : nullptr);
}

void
CQMetaEditTree::
updateObject()
{
  CQMetaEditModel *model = qobject_cast<CQMetaEditModel *>(this->model());

  model->beginResetModel();

  model->endResetModel();
}
