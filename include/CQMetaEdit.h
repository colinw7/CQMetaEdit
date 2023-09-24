#ifndef CQMetaEdit_H
#define CQMetaEdit_H

#include <QFrame>
#include <QPointer>

class CQMetaPropertyTree;
class CQMetaLayoutTree;
class CQMetaLayoutEditor;
class CQMetaSignalTree;
class CQMetaSlotTree;
class CQMetaWidgetTree;
class CQMetaEditOptions;
class CQMetaEditPalette;
class CQPicker;
class CQLinkLabel;

class QLineEdit;
class QLabel;
class QRubberBand;

class CQMetaEdit : public QFrame {
  Q_OBJECT

  Q_PROPERTY(bool inherited READ inherited WRITE setInherited)

 public:
  CQMetaEdit(QWidget *parent=nullptr);

  bool inherited() const { return inherited_; }

  QObject *object() const;
  void setObject(QObject *object);

  QWidget *widget() const;

  void showWidget(QWidget *w);

  QSize sizeHint() const override { return QSize(800, 800); }

 public Q_SLOTS:
  void setInherited(bool);

 private Q_SLOTS:
  void loadObjectName();

  void showObject();

  void loadParent();

  void pickObject(QObject *object);

  void snapshotSlot();

  void focusChangedSlot(QWidget *oldW, QWidget *newW);

 private:
  typedef QPointer<QObject> ObjectP;

  bool                inherited_      { true };
  ObjectP             object_;
  CQPicker*           picker_         { nullptr };
  QLineEdit*          objectNameEdit_ { nullptr };
  QLabel*             typeLabel_      { nullptr };
  CQLinkLabel*        nameLink_       { nullptr };
  CQLinkLabel*        parentLink_     { nullptr };
  QLabel*             parentLabel_    { nullptr };
  QLabel*             layoutLabel_    { nullptr };
  CQMetaPropertyTree* propertyTree_   { nullptr };
  CQMetaLayoutTree*   layoutTree_     { nullptr };
  CQMetaLayoutEditor* layoutEditor_   { nullptr };
  CQMetaSignalTree*   signalTree_     { nullptr };
  CQMetaSlotTree*     slotTree_       { nullptr };
  CQMetaWidgetTree*   widgetTree_     { nullptr };
  CQMetaEditOptions*  options_        { nullptr };
  CQMetaEditPalette*  palette_        { nullptr };
  QLabel*             focusLabel_     { nullptr };
  QRubberBand*        rubberBand_     { nullptr };
};

#endif
