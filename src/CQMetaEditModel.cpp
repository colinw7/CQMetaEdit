#include <CQMetaEditModel.h>
#include <CQMetaEditTree.h>

CQMetaEditModel::
CQMetaEditModel(CQMetaEditTree *tree) :
 tree_(tree)
{
  setObjectName("metaEditModel");
}

void
CQMetaEditModel::
beginResetModel()
{
  QAbstractItemModel::beginResetModel();
}

void
CQMetaEditModel::
endResetModel()
{
  QAbstractItemModel::endResetModel();

  int nr = rowCount(QModelIndex());

  beginInsertRows(QModelIndex(), 0, nr);
  endInsertRows  ();
}

QVariant
CQMetaEditModel::
data(const QModelIndex &index, int role) const
{
  if (! index.isValid())
    return QVariant();

  if (role == Qt::SizeHintRole) {
    QVariant var = data(index, Qt::DisplayRole);

    if (var.isValid()) {
      QFontMetrics fm(tree_->font());

      return QSize(fm.horizontalAdvance(var.toString()) + 8, fm.height() + 2);
    }
  }

  return QVariant();
}
