#ifndef CQMetaSignalModel_H
#define CQMetaSignalModel_H

#include <CQMetaEditModel.h>

class CQMetaSignalTree;

class CQMetaSignalModel : public CQMetaEditModel {
 public:
  CQMetaSignalModel(CQMetaSignalTree *tree);

  QModelIndex parent(const QModelIndex &index) const override;

  int columnCount(const QModelIndex &) const override;

  int rowCount(const QModelIndex &parent) const override;

  QModelIndex index(int row, int column, const QModelIndex &parent) const override;

  QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

  QVariant data(const QModelIndex &index, int role) const override;

 private:
  CQMetaSignalTree *tree_ { nullptr };
};

#endif
