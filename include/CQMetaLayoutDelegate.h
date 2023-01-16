#ifndef CQMetaLayoutDelegate_H
#define CQMetaLayoutDelegate_H

#include <QItemDelegate>

class CQMetaLayoutTree;

class CQMetaLayoutDelegate : public QItemDelegate {
  Q_OBJECT

 public:
  CQMetaLayoutDelegate(CQMetaLayoutTree *tree);

  void paint(QPainter *painter, const QStyleOptionViewItem &option,
             const QModelIndex &index) const override;

 private:
  CQMetaLayoutTree *tree_ { nullptr };
};

#endif
