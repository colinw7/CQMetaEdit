#ifndef CQMetaPropertyDelegate_H
#define CQMetaPropertyDelegate_H

#include <QItemDelegate>

class CQMetaPropertyTree;

class CQMetaPropertyDelegate : public QItemDelegate {
  Q_OBJECT

 public:
  CQMetaPropertyDelegate(CQMetaPropertyTree *tree);

  void paint(QPainter *painter, const QStyleOptionViewItem &option,
             const QModelIndex &index) const override;

  QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &item,
                        const QModelIndex &index) const override;

  void setEditorData(QWidget *w, const QModelIndex &index) const override;

  void setModelData(QWidget *w, QAbstractItemModel *model,
                    const QModelIndex &index) const override;

 private:
  CQMetaPropertyTree *tree_ { nullptr };
};

#endif
