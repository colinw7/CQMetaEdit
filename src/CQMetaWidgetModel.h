#ifndef CQMetaWidgetModel_H
#define CQMetaWidgetModel_H

#include <CQMetaEditModel.h>

class CQMetaWidgetTree;

class CQMetaWidgetModel : public CQMetaEditModel {
  Q_OBJECT

 public:
  CQMetaWidgetModel(CQMetaWidgetTree *tree);

  QModelIndex parent(const QModelIndex &index) const override;

  int columnCount(const QModelIndex &) const override;

  int rowCount(const QModelIndex &parent) const override;

  QModelIndex index(int row, int column, const QModelIndex &parent) const override;

  QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

  QVariant data(const QModelIndex &index, int role) const override;

  QWidget *indexWidget(const QModelIndex &index) const;
  QObject *indexObject(const QModelIndex &index) const;

 private:
  std::vector<QObject *> objectChildren(QObject *obj) const;

 private:
  CQMetaWidgetTree *tree_ { nullptr };
  bool              objectChildren_ { false };
};

#endif
