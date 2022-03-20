#include <CQMetaWidgetModel.h>
#include <CQMetaWidgetTree.h>
#include <CQUtil.h>

CQMetaWidgetModel::
CQMetaWidgetModel(CQMetaWidgetTree *tree) :
 CQMetaEditModel(tree), tree_(tree)
{
}

QModelIndex
CQMetaWidgetModel::
parent(const QModelIndex &index) const
{
  if (! index.isValid())
    return QModelIndex();

  QWidget *child = indexWidget(index);

  if (! child)
    return QModelIndex();

  QWidget *parent = child->parentWidget();

  if (! parent)
    return QModelIndex();

  QWidget *parentParent = parent->parentWidget();

  if (parentParent) {
    const QObjectList &children = parentParent->children();

    for (int i = 0; i < children.size(); ++i) {
      if (children[i] == parent)
        return createIndex(i, 0, static_cast<void *>(parent));
    }
  }

  return QModelIndex();
}

int
CQMetaWidgetModel::
columnCount(const QModelIndex &) const
{
  return 2;
}

int
CQMetaWidgetModel::
rowCount(const QModelIndex &parent) const
{
  QWidget *parentObject = nullptr;

  if (parent.isValid())
    parentObject = indexWidget(parent);
  else
    parentObject = qobject_cast<QWidget *>(tree_->object());

  if (! parentObject)
    return 0;

  const QObjectList &children = parentObject->children();

  int num = 0;

  for (int i = 0; i < children.size(); ++i) {
    QWidget *w = qobject_cast<QWidget *>(children[i]);

    if (! w)
      continue;

    ++num;
  }

  return num;
}

QModelIndex
CQMetaWidgetModel::
index(int row, int column, const QModelIndex &parent) const
{
  QWidget *parentObject = nullptr;

  if (parent.isValid())
    parentObject = indexWidget(parent);
  else
    parentObject = qobject_cast<QWidget *>(tree_->object());

  if (! parentObject)
    return createIndex(row, column, nullptr);

  const QObjectList &children = parentObject->children();

  int num = 0;

  for (int i = 0; i < children.size(); ++i) {
    QWidget *w = qobject_cast<QWidget *>(children[i]);

    if (! w)
      continue;

    if (row == num)
      return createIndex(row, column, static_cast<void *>(w));

    ++num;
  }

  return createIndex(row, column);
}

QVariant
CQMetaWidgetModel::
headerData(int section, Qt::Orientation /*orientation*/, int role) const
{
  if (role == Qt::DisplayRole) {
    if      (section == 0)
      return "Name";
    else if (section == 1)
      return "Type";
  }

  return QVariant();
}

QVariant
CQMetaWidgetModel::
data(const QModelIndex &index, int role) const
{
  if (! index.isValid())
    return QVariant();

  if (role == Qt::DisplayRole) {
    if      (index.column() == 0) {
      QWidget *object = indexWidget(index);

      QString name = (object ? object->objectName() : QString());

      if (name == "")
        name = "<no name>";

      return name;
    }
    else if (index.column() == 1) {
      QWidget *object = indexWidget(index);

      QString name = (object ? CQUtil::className(object) : QString());

      if (name == "")
        name = "<no type>";

      return name;
    }
  }
  else {
    return CQMetaEditModel::data(index, role);
  }

  return QVariant();
}

QWidget *
CQMetaWidgetModel::
indexWidget(const QModelIndex &index) const
{
  if (! index.isValid())
    return nullptr;

  return static_cast<QWidget *>(index.internalPointer());
}
