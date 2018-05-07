#ifndef CQMetaEditTree_H
#define CQMetaEditTree_H

#include <CQTreeView.h>
#include <QPointer>

class CQMetaEdit;

class CQMetaEditTree : public CQTreeView {
  Q_OBJECT

 public:
  CQMetaEditTree(CQMetaEdit *edit);

  virtual ~CQMetaEditTree() { }

  CQMetaEdit *edit() const { return edit_; }

  QObject *object() const;

  void updateObject();

  void beginResetModel();
  void endResetModel();

 protected:
  CQMetaEdit* edit_ { nullptr };
};

#endif
