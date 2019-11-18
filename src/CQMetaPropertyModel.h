#ifndef CQMetaPropertyModel_H
#define CQMetaPropertyModel_H

#include <CQMetaEditModel.h>

class CQMetaPropertyTree;

class CQMetaPropertyModel : public CQMetaEditModel {
 public:
  CQMetaPropertyModel(CQMetaPropertyTree *tree);

  QModelIndex parent(const QModelIndex &index) const override;

  int columnCount(const QModelIndex &) const override;

  int rowCount(const QModelIndex &parent) const override;

  QModelIndex index(int row, int column, const QModelIndex &parent) const override;

  QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

  QVariant data(const QModelIndex &index, int role) const override;

  bool setData(const QModelIndex &index, const QVariant &value, int role) override;

  Qt::ItemFlags flags(const QModelIndex &index) const override;

 private:
  CQMetaPropertyTree *tree_ { nullptr };
};

#endif
