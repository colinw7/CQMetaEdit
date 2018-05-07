#ifndef CQMetaSlotTree_H
#define CQMetaSlotTree_H

#include <CQMetaEditTree.h>

class CQMetaSlotModel;
class CQMetaSlotDelegate;

class CQMetaSlotTree : public CQMetaEditTree {
  Q_OBJECT

 public:
  CQMetaSlotTree(CQMetaEdit *edit);

 private:
  CQMetaSlotModel    *model_    { nullptr };
  CQMetaSlotDelegate *delegate_ { nullptr };
};

#endif
