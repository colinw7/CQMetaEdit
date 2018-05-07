#include <CQMetaSlotModel.h>
#include <CQMetaSlotTree.h>
#include <CQMetaEdit.h>
#include <CQUtil.h>

CQMetaSlotModel::
CQMetaSlotModel(CQMetaSlotTree *tree) :
 CQMetaEditModel(tree), tree_(tree)
{
}

QModelIndex
CQMetaSlotModel::
parent(const QModelIndex &index) const
{
  if (! index.isValid())
    return QModelIndex();

  return QModelIndex();
}

int
CQMetaSlotModel::
columnCount(const QModelIndex &) const
{
  return 1;
}

int
CQMetaSlotModel::
rowCount(const QModelIndex &parent) const
{
  if (parent.isValid())
    return 0;

  if (parent.column() > 0)
    return 0;

  CQMetaEdit *edit = tree_->edit();

  return CQUtil::numSlots(tree_->object(), edit->inherited());
}

QModelIndex
CQMetaSlotModel::
index(int row, int column, const QModelIndex &parent) const
{
  if (parent.isValid())
    return QModelIndex();

  return createIndex(row, column, nullptr);
}

QVariant
CQMetaSlotModel::
headerData(int section, Qt::Orientation /*orientation*/, int role) const
{
  if (role == Qt::DisplayRole) {
    if (section == 0)
      return "Name";
  }

  return QVariant();
}

QVariant
CQMetaSlotModel::
data(const QModelIndex &index, int role) const
{
  if (! index.isValid())
    return QVariant();

  CQMetaEdit *edit = tree_->edit();

  if (role == Qt::DisplayRole) {
    if (index.column() == 0) {
      QString name = CQUtil::slotName(tree_->object(), index.row(), edit->inherited());

      return name;
    }
  }
  else {
    return CQMetaEditModel::data(index, role);
  }

  return QVariant();
}
