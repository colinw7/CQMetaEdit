#ifndef CQMetaPropertyModel_H
#define CQMetaPropertyModel_H

#include <CQMetaEditModel.h>

class CQMetaPropertyTree;

class CQMetaPropertyModel : public CQMetaEditModel {
 public:
  CQMetaPropertyModel(CQMetaPropertyTree *tree);

  QModelIndex parent(const QModelIndex &index) const;

  int columnCount(const QModelIndex &) const;

  int rowCount(const QModelIndex &parent) const;

  QModelIndex index(int row, int column, const QModelIndex &parent) const;

  QVariant headerData(int section, Qt::Orientation orientation, int role) const;

  QVariant data(const QModelIndex &index, int role) const;

  bool setData(const QModelIndex &index, const QVariant &value, int role) override;

  Qt::ItemFlags flags(const QModelIndex &index) const override;

 private:
  CQMetaPropertyTree *tree_ { nullptr };
};

#endif
