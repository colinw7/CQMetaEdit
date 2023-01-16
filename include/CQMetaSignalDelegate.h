#ifndef CQMetaSignalDelegate_H
#define CQMetaSignalDelegate_H

#include <QItemDelegate>

class CQMetaSignalTree;

class CQMetaSignalDelegate : public QItemDelegate {
  Q_OBJECT

 public:
  CQMetaSignalDelegate(CQMetaSignalTree *tree);

  void paint(QPainter *painter, const QStyleOptionViewItem &option,
              const QModelIndex &index) const  override;

 private:
  CQMetaSignalTree *tree_ { nullptr };
};

#endif
