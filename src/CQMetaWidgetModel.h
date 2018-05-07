#ifndef CQMetaWidgetModel_H
#define CQMetaWidgetModel_H

#include <CQMetaEditModel.h>

class CQMetaWidgetTree;

class CQMetaWidgetModel : public CQMetaEditModel {
 public:
  CQMetaWidgetModel(CQMetaWidgetTree *tree);

  QModelIndex parent(const QModelIndex &index) const;

  int columnCount(const QModelIndex &) const;

  int rowCount(const QModelIndex &parent) const;

  QModelIndex index(int row, int column, const QModelIndex &parent) const;

  QVariant headerData(int section, Qt::Orientation orientation, int role) const;

  QVariant data(const QModelIndex &index, int role) const;

  QWidget *indexWidget(const QModelIndex &index) const;

 private:
  CQMetaWidgetTree *tree_ { nullptr };
};

#endif
