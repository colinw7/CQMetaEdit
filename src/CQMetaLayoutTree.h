#ifndef CQMetaLayoutTree_H
#define CQMetaLayoutTree_H

#include <CQMetaEditTree.h>

class CQMetaLayoutModel;
class CQMetaLayoutDelegate;

class CQMetaLayoutTree : public CQMetaEditTree {
  Q_OBJECT

 public:
  CQMetaLayoutTree(CQMetaEdit *edit);

 private:
  CQMetaLayoutModel    *model_    { nullptr };
  CQMetaLayoutDelegate *delegate_ { nullptr };
};

#endif
