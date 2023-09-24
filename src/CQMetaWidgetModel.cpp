#include <CQMetaWidgetModel.h>
#include <CQMetaWidgetTree.h>
#include <CQUtil.h>
#include <QAbstractProxyModel>

CQMetaWidgetModel::
CQMetaWidgetModel(CQMetaWidgetTree *tree) :
 CQMetaEditModel(tree), tree_(tree)
{
  objectChildren_ = true;
}

QModelIndex
CQMetaWidgetModel::
parent(const QModelIndex &index) const
{
  if (! index.isValid())
    return QModelIndex();

  auto *child = (objectChildren_ ? indexObject(index) : indexWidget(index));

  if (! child)
    return QModelIndex();

  auto *parent = (objectChildren_ ?
    child->parent() : qobject_cast<QWidget *>(child)->parentWidget());

  if (! parent)
    return QModelIndex();

  auto *parentParent = (objectChildren_ ?
    parent->parent() : qobject_cast<QWidget *>(parent)->parentWidget());

  if (parentParent) {
    const auto &children = objectChildren(parentParent);

    int i = 0;

    for (auto *child : children) {
      if (child == parent)
        return createIndex(i, 0, static_cast<void *>(parent));

      ++i;
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
  QObject *parentObject = nullptr;

  if (parent.isValid())
    parentObject = indexObject(parent);
  else {
    if (objectChildren_)
      parentObject = tree_->object();
    else
      parentObject = qobject_cast<QWidget *>(tree_->object());
  }

  if (! parentObject)
    return 0;

  const auto &children = objectChildren(parentObject);

  return children.size();
}

QModelIndex
CQMetaWidgetModel::
index(int row, int column, const QModelIndex &parent) const
{
  QObject *parentObject = nullptr;

  if (parent.isValid())
    parentObject = indexObject(parent);
  else {
    if (objectChildren_)
      parentObject = tree_->object();
    else
      parentObject = qobject_cast<QWidget *>(tree_->object());
  }

  if (! parentObject)
    return createIndex(row, column, nullptr);

  const auto &children = objectChildren(parentObject);

  int num = 0;

  for (auto *child : children) {
    if (row == num)
      return createIndex(row, column, static_cast<void *>(child));

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
      auto *object = indexObject(index);

      QString name = (object ? object->objectName() : QString());

      if (name == "")
        name = "<no name>";

      return name;
    }
    else if (index.column() == 1) {
      auto *object = indexObject(index);

      auto name = (object ? CQUtil::className(object) : QString());

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
  return qobject_cast<QWidget *>(indexObject(index));
}

QObject *
CQMetaWidgetModel::
indexObject(const QModelIndex &index) const
{
  if (! index.isValid())
    return nullptr;

  return static_cast<QObject *>(index.internalPointer());
}

std::vector<QObject *>
CQMetaWidgetModel::
objectChildren(QObject *obj) const
{
  std::vector<QObject *> objs;

  const auto &children = obj->children();

  for (int i = 0; i < children.size(); ++i) {
    if (! objectChildren_) {
      auto *w = qobject_cast<QWidget *>(children[i]);
      if (! w) continue;

      objs.push_back(w);
    }
    else
      objs.push_back(children[i]);
  }

  auto *view = qobject_cast<QAbstractItemView *>(obj);

  if (view) {
    auto *model = view->model();

    auto *proxyModel = qobject_cast<QAbstractProxyModel *>(model);

    while (proxyModel) {
      objs.push_back(proxyModel);

      model = proxyModel->sourceModel();

      proxyModel = qobject_cast<QAbstractProxyModel *>(model);
    }

    objs.push_back(model);
  }

  return objs;
}
