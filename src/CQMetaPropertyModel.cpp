#include <CQMetaPropertyModel.h>
#include <CQMetaPropertyTree.h>
#include <CQMetaEdit.h>
#include <CQUtil.h>

CQMetaPropertyModel::
CQMetaPropertyModel(CQMetaPropertyTree *tree) :
 CQMetaEditModel(tree), tree_(tree)
{
}

QModelIndex
CQMetaPropertyModel::
parent(const QModelIndex &index) const
{
  if (! index.isValid())
    return QModelIndex();

  return QModelIndex();
}

int
CQMetaPropertyModel::
columnCount(const QModelIndex &) const
{
  return 3;
}

int
CQMetaPropertyModel::
rowCount(const QModelIndex &parent) const
{
  if (parent.isValid())
    return 0;

  if (parent.column() > 0)
    return 0;

  CQMetaEdit *edit = tree_->edit();

  return CQUtil::getNumProperties(tree_->object(), edit->inherited());
}

QModelIndex
CQMetaPropertyModel::
index(int row, int column, const QModelIndex &parent) const
{
  if (parent.isValid())
    return QModelIndex();

  return createIndex(row, column, nullptr);
}

QVariant
CQMetaPropertyModel::
headerData(int section, Qt::Orientation /*orientation*/, int role) const
{
  if (role == Qt::DisplayRole) {
    if      (section == 0)
      return "Name";
    else if (section == 1)
      return "Type";
    else if (section == 2)
      return "Value";
  }

  return QVariant();
}

QVariant
CQMetaPropertyModel::
data(const QModelIndex &index, int role) const
{
  if (! index.isValid())
    return QVariant();

  if (role == Qt::DisplayRole || role == Qt::EditRole) {
    CQMetaEdit *edit = tree_->edit();

    if      (index.column() == 0) {
      QString name = CQUtil::getPropertyName(tree_->object(), index.row(), edit->inherited());

      return name;
    }
    else if (index.column() == 1) {
      if (CQUtil::getPropertyValueIsEnum(tree_->object(), index.row(), edit->inherited())) {
        QString name = CQUtil::getPropertyEnumName(tree_->object(), index.row(), edit->inherited());

        if (name == "")
          name = QString("%1").arg(
            CQUtil::getPropertyEnumValue(tree_->object(), index.row(), edit->inherited()));

        return name;
      }
      else {
        QString typeName =
          CQUtil::getPropertyTypeName(tree_->object(), index.row(), edit->inherited());

        return typeName;
      }
    }
    else if (index.column() == 2) {
      QVariant value = CQUtil::getPropertyValue(tree_->object(), index.row(), edit->inherited());

      return value;
    }
  }
  else {
    return CQMetaEditModel::data(index, role);
  }

  return QVariant();
}

bool
CQMetaPropertyModel::
setData(const QModelIndex &index, const QVariant &value, int role)
{
  if (! index.isValid())
    return false;

  if (role == Qt::DisplayRole || role == Qt::EditRole) {
    CQMetaEdit *edit = tree_->edit();

    if (index.column() == 2) {
      return CQUtil::setPropertyValue(tree_->object(), index.row(), value, edit->inherited());
    }
    else {
      return false;
    }
  }
  else {
    return false;
  }
}

Qt::ItemFlags
CQMetaPropertyModel::
flags(const QModelIndex &index) const
{
  if (index.column() == 2)
    return CQMetaEditModel::flags(index) | Qt::ItemIsEditable;
  else
    return CQMetaEditModel::flags(index);
}
