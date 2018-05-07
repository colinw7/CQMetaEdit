#ifndef CQMetaEditOptions_H
#define CQMetaEditOptions_H

#include <QFrame>

class CQMetaEdit;
class QCheckBox;

class CQMetaEditOptions : public QFrame {
  Q_OBJECT

 public:
  CQMetaEditOptions(CQMetaEdit *edit);

 private:
  CQMetaEdit* edit_           { nullptr };
  QCheckBox*  inheritedCheck_ { nullptr };
};

#endif
