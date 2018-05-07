#ifndef CQMetaWidgetDelegate_H
#define CQMetaWidgetDelegate_H

#include <QItemDelegate>

class CQMetaWidgetTree;

class CQMetaWidgetDelegate : public QItemDelegate {
  Q_OBJECT

 public:
  CQMetaWidgetDelegate(CQMetaWidgetTree *tree);

  void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;

 private:
  CQMetaWidgetTree *tree_ { nullptr };
};

#endif
