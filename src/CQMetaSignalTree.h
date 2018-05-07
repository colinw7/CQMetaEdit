#ifndef CQMetaSignalTree_H
#define CQMetaSignalTree_H

#include <CQMetaEditTree.h>

class CQMetaSignalModel;
class CQMetaSignalDelegate;

class CQMetaSignalTree : public CQMetaEditTree {
  Q_OBJECT

 public:
  CQMetaSignalTree(CQMetaEdit *edit);

 private:
  CQMetaSignalModel    *model_    { nullptr };
  CQMetaSignalDelegate *delegate_ { nullptr };
};

#endif
