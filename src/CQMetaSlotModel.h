#ifndef CQMetaSlotModel_H
#define CQMetaSlotModel_H

#include <CQMetaEditModel.h>

class CQMetaSlotTree;

class CQMetaSlotModel : public CQMetaEditModel {
 public:
  CQMetaSlotModel(CQMetaSlotTree *tree);

  QModelIndex parent(const QModelIndex &index) const;

  int columnCount(const QModelIndex &) const;

  int rowCount(const QModelIndex &parent) const;

  QModelIndex index(int row, int column, const QModelIndex &parent) const;

  QVariant headerData(int section, Qt::Orientation orientation, int role) const;

  QVariant data(const QModelIndex &index, int role) const;

 private:
  CQMetaSlotTree *tree_ { nullptr };
};

#endif
