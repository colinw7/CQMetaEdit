#include <CQMetaLayoutModel.h>
#include <CQMetaLayoutTree.h>
#include <CQMetaEdit.h>
#include <CQUtil.h>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>

CQMetaLayoutModel::
CQMetaLayoutModel(CQMetaLayoutTree *tree) :
 CQMetaEditModel(tree), tree_(tree)
{
}

QModelIndex
CQMetaLayoutModel::
parent(const QModelIndex &index) const
{
  if (! index.isValid())
    return QModelIndex();

  return QModelIndex();
}

int
CQMetaLayoutModel::
columnCount(const QModelIndex &) const
{
  return 3;
}

int
CQMetaLayoutModel::
rowCount(const QModelIndex &parent) const
{
  if (parent.isValid())
    return 0;

  if (parent.column() > 0)
    return 0;

  QLayout *layout = layoutObject();

  if (! layout)
    return 0;

  CQMetaEdit *edit = tree_->metaEdit();

  int numProp = CQUtil::getNumProperties(layout, edit->inherited());

  if (qobject_cast<QGridLayout *>(layout))
    numProp += 2;

  return numProp;
}

QModelIndex
CQMetaLayoutModel::
index(int row, int column, const QModelIndex &parent) const
{
  if (parent.isValid())
    return QModelIndex();

  return createIndex(row, column, nullptr);
}

QVariant
CQMetaLayoutModel::
headerData(int section, Qt::Orientation /*orientation*/, int role) const
{
  if (role == Qt::DisplayRole) {
    if      (section == 0)
      return "Name";
    else if (section == 1)
      return "Value";
    else if (section == 2)
      return "Value";
  }

  return QVariant();
}

QVariant
CQMetaLayoutModel::
data(const QModelIndex &index, int role) const
{
  if (! index.isValid())
    return QVariant();

  QLayout *layout = layoutObject();

  if (! layout)
    return QVariant();

  if (role == Qt::DisplayRole || role == Qt::EditRole) {
    CQMetaEdit *edit = tree_->metaEdit();

    int numProp = CQUtil::getNumProperties(layout, edit->inherited());

    if (index.row() < numProp) {
      if      (index.column() == 0) {
        QString name = CQUtil::getPropertyName(layout, index.row(), edit->inherited());

        return name;
      }
      else if (index.column() == 1) {
        if (CQUtil::getPropertyValueIsEnum(layout, index.row(), edit->inherited())) {
          QString name = CQUtil::getPropertyEnumName(layout, index.row(), edit->inherited());

          if (name == "")
            name = QString("%1").arg(
              CQUtil::getPropertyEnumValue(layout, index.row(), edit->inherited()));

          return name;
        }
        else {
          QString typeName = CQUtil::getPropertyTypeName(layout, index.row(), edit->inherited());

          return typeName;
        }
      }
      else if (index.column() == 2) {
        QVariant value = CQUtil::getPropertyValue(layout, index.row(), edit->inherited());

        return value;
      }
    }
    else {
      QGridLayout *gridLayout = qobject_cast<QGridLayout *>(layout);

      if (gridLayout) {
        if      (index.row() == numProp) {
          if      (index.column() == 0) return "rowCount";
          else if (index.column() == 1) return "int";
          else if (index.column() == 2) return gridLayout->rowCount();
        }
        else if (index.row() == numProp + 1) {
          if      (index.column() == 0) return "columnCount";
          else if (index.column() == 1) return "int";
          else if (index.column() == 2) return gridLayout->columnCount();
        }
      }
    }
  }
  else {
    return CQMetaEditModel::data(index, role);
  }

  return QVariant();
}

QLayout *
CQMetaLayoutModel::
layoutObject() const
{
  CQMetaEdit *edit = tree_->metaEdit();

  return (edit->widget() ? edit->widget()->layout() : 0);
}
