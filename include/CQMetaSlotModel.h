#ifndef CQMetaSlotModel_H
#define CQMetaSlotModel_H

#include <CQMetaEditModel.h>

class CQMetaSlotTree;

class CQMetaSlotModel : public CQMetaEditModel {
 public:
  CQMetaSlotModel(CQMetaSlotTree *tree);

  QModelIndex parent(const QModelIndex &index) const override;

  int columnCount(const QModelIndex &) const override;

  int rowCount(const QModelIndex &parent) const override;

  QModelIndex index(int row, int column, const QModelIndex &parent) const override;

  QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

  QVariant data(const QModelIndex &index, int role) const override;

 private:
  CQMetaSlotTree *tree_ { nullptr };
};

#endif
