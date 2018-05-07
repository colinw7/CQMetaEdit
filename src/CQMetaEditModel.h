#ifndef CQMetaEditModel_H
#define CQMetaEditModel_H

#include <QAbstractItemModel>

class CQMetaEditTree;

class CQMetaEditModel : public QAbstractItemModel {
  Q_OBJECT

 public:
  CQMetaEditModel(CQMetaEditTree *tree);

  void beginResetModel();
  void endResetModel();

  QVariant data(const QModelIndex &index, int role) const override;

 private:
  CQMetaEditTree *tree_ { nullptr };
};

#endif
