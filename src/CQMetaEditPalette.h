#ifndef CQMetaEditPalette_H
#define CQMetaEditPalette_H

#include <QFrame>

class CQMetaEdit;

class CQMetaEditPalette : public QFrame {
  Q_OBJECT

 public:
  CQMetaEditPalette(CQMetaEdit *edit);

 private:
  void paintEvent(QPaintEvent *);

 private:
  CQMetaEdit *edit_ { nullptr };
};

#endif
