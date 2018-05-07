#ifndef CQMetaLayoutModel_H
#define CQMetaLayoutModel_H

#include <CQMetaEditModel.h>

class CQMetaLayoutTree;
class QLayout;

class CQMetaLayoutModel : public CQMetaEditModel {
 public:
  CQMetaLayoutModel(CQMetaLayoutTree *tree);

  QModelIndex parent(const QModelIndex &index) const;

  int columnCount(const QModelIndex &) const;

  int rowCount(const QModelIndex &parent) const;

  QModelIndex index(int row, int column, const QModelIndex &parent) const;

  QVariant headerData(int section, Qt::Orientation orientation, int role) const;

  QVariant data(const QModelIndex &index, int role) const;

 private:
  QLayout *layoutObject() const;

 private:
  CQMetaLayoutTree *tree_ { nullptr };
};

#endif
