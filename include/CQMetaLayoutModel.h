#ifndef CQMetaLayoutModel_H
#define CQMetaLayoutModel_H

#include <CQMetaEditModel.h>

class CQMetaLayoutTree;
class QLayout;

class CQMetaLayoutModel : public CQMetaEditModel {
 public:
  CQMetaLayoutModel(CQMetaLayoutTree *tree);

  QModelIndex parent(const QModelIndex &index) const override;

  int columnCount(const QModelIndex &) const override;

  int rowCount(const QModelIndex &parent) const override;

  QModelIndex index(int row, int column, const QModelIndex &parent) const override;

  QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

  QVariant data(const QModelIndex &index, int role) const override;

 private:
  QLayout *layoutObject() const;

 private:
  CQMetaLayoutTree *tree_ { nullptr };
};

#endif
