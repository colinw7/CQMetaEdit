#ifndef CQMetaWidgetTree_H
#define CQMetaWidgetTree_H

#include <CQMetaEditTree.h>

class CQMetaWidgetModel;
class CQMetaWidgetDelegate;

class CQMetaWidgetTree : public CQMetaEditTree {
  Q_OBJECT

 public:
  CQMetaWidgetTree(CQMetaEdit *edit);

  void mouseDoubleClickEvent(QMouseEvent *) override;

 private:
  CQMetaWidgetModel*    model_    { nullptr };
  CQMetaWidgetDelegate* delegate_ { nullptr };
};

#endif
