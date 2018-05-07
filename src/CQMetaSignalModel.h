#ifndef CQMetaSignalModel_H
#define CQMetaSignalModel_H

#include <CQMetaEditModel.h>

class CQMetaSignalTree;

class CQMetaSignalModel : public CQMetaEditModel {
 public:
  CQMetaSignalModel(CQMetaSignalTree *tree);

  QModelIndex parent(const QModelIndex &index) const;

  int columnCount(const QModelIndex &) const;

  int rowCount(const QModelIndex &parent) const;

  QModelIndex index(int row, int column, const QModelIndex &parent) const;

  QVariant headerData(int section, Qt::Orientation orientation, int role) const;

  QVariant data(const QModelIndex &index, int role) const;

 private:
  CQMetaSignalTree *tree_ { nullptr };
};

#endif
