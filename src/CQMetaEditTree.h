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

  CQMetaEdit *metaEdit() const;

  QObject *object() const;

  void updateObject();

  void beginResetModel();
  void endResetModel();

 protected:
  using CQMetaEditP = QPointer<CQMetaEdit>;

  CQMetaEditP edit_;
};

#endif
