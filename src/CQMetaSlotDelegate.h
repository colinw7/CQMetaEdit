#ifndef CQMetaSlotDelegate_H
#define CQMetaSlotDelegate_H

#include <QItemDelegate>

class CQMetaSlotTree;

class CQMetaSlotDelegate : public QItemDelegate {
  Q_OBJECT

 public:
  CQMetaSlotDelegate(CQMetaSlotTree *tree);

  void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;

 private:
  CQMetaSlotTree *tree_ { nullptr };
};

#endif
