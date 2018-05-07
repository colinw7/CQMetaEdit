#ifndef CQMetaPropertyTree_H
#define CQMetaPropertyTree_H

#include <CQMetaEditTree.h>

class CQMetaPropertyModel;
class CQMetaPropertyDelegate;

class CQMetaPropertyTree : public CQMetaEditTree {
  Q_OBJECT

 public:
  CQMetaPropertyTree(CQMetaEdit *edit);

 private:
  CQMetaPropertyModel    *model_    { nullptr };
  CQMetaPropertyDelegate *delegate_ { nullptr };
};

#endif
