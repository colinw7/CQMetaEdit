#include <CQMetaEdit.h>
#include <CQMetaPropertyTree.h>
#include <CQMetaLayoutTree.h>
#include <CQMetaSignalTree.h>
#include <CQMetaSlotTree.h>
#include <CQMetaWidgetTree.h>
#include <CQMetaEditOptions.h>
#include <CQMetaEditPalette.h>
#include <CQUtil.h>
#include <CQPicker.h>
#include <CQLinkLabel.h>

#include <QApplication>
#include <QTabWidget>
#include <QLineEdit>
#include <QToolButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QPainter>

#include <svg/icon_svg.h>
#include <svg/image_svg.h>

CQMetaEdit::
CQMetaEdit(QWidget *parent) :
 QFrame(parent)
{
  setWindowTitle("Meta Edit");
  setWindowIcon (CQPixmapCacheInst->getIcon("ICON"));

  setObjectName("edit");

  QVBoxLayout *layout = new QVBoxLayout(this);
  layout->setMargin(0); layout->setSpacing(2);

  //---

  QFrame *objectFrame = new QFrame;

  objectFrame->setObjectName("objectFrame");

  layout->addWidget(objectFrame);

  QVBoxLayout *objectLayout = new QVBoxLayout(objectFrame);
  objectLayout->setMargin(2); objectLayout->setSpacing(2);

  //---

  QFrame *objectDetailsFrame = new QFrame;

  objectDetailsFrame->setObjectName("objectDetailsFrame");

  objectLayout->addWidget(objectDetailsFrame);

  QGridLayout *objectDetailsLayout = new QGridLayout(objectDetailsFrame);
  objectDetailsLayout->setMargin(0); objectDetailsLayout->setSpacing(2);

  //---

  QFontMetrics fm(font());

  picker_ = new CQPicker;

  picker_->setSize(3*fm.height());

  connect(picker_, SIGNAL(objectPicked(QObject *)), this, SLOT(pickObject(QObject *)));

  objectDetailsLayout->addWidget(picker_, 0, 0, 3, 1);

  //---

  objectNameEdit_ = new QLineEdit;

  objectNameEdit_->setObjectName("objectNameEdit");

  objectDetailsLayout->addWidget(new QLabel("Name"), 0, 1);
  objectDetailsLayout->addWidget(objectNameEdit_   , 0, 2);

  connect(objectNameEdit_, SIGNAL(returnPressed()), this, SLOT(loadObjectName()));

  //---

  typeLabel_ = new QLabel;

  typeLabel_->setObjectName("typeLabel");

  objectDetailsLayout->addWidget(new QLabel("Type"), 1, 1);
  objectDetailsLayout->addWidget(typeLabel_        , 1, 2);

  //---

  parentLink_ = new CQLinkLabel;

  parentLink_->setObjectName("parentLink");
  parentLink_->setText("<no name>");

  connect(parentLink_, SIGNAL(clicked()), this, SLOT(loadParent()));

  objectDetailsLayout->addWidget(new QLabel("Parent"), 2, 1);
  objectDetailsLayout->addWidget(parentLink_         , 2, 2);

  //---

  layoutLabel_ = new QLabel;

  layoutLabel_->setObjectName("layoutLabel");

  objectDetailsLayout->addWidget(new QLabel("Layout"), 3, 1);
  objectDetailsLayout->addWidget(layoutLabel_        , 3, 2);

  //------

  QTabWidget *tab = new QTabWidget;

  tab->setObjectName("tab");

  layout->addWidget(tab);

  propertyTree_ = new CQMetaPropertyTree(this);

  tab->addTab(propertyTree_, "Properties");

  layoutTree_ = new CQMetaLayoutTree(this);

  tab->addTab(layoutTree_, "Layout");

  signalTree_ = new CQMetaSignalTree(this);

  tab->addTab(signalTree_, "Signals");

  slotTree_ = new CQMetaSlotTree(this);

  tab->addTab(slotTree_, "Slots");

  widgetTree_ = new CQMetaWidgetTree(this);

  tab->addTab(widgetTree_, "Children");

  options_ = new CQMetaEditOptions(this);

  tab->addTab(options_, "Options");

  palette_ = new CQMetaEditPalette(this);

  tab->addTab(palette_, "Palette");

  //----

  QToolButton *snapButton = new QToolButton;

  snapButton->setIcon(CQPixmapCacheInst->getIcon("IMAGE"));

  connect(snapButton, SIGNAL(clicked()), this, SLOT(snapshotSlot()));

  tab->setCornerWidget(snapButton);

  //----

  QFrame *statusBar = new QFrame;

  QHBoxLayout *statusLayout = new QHBoxLayout(statusBar);

  focusLabel_ = new QLabel;

  statusLayout->addWidget(focusLabel_);
  statusLayout->addStretch();

  layout->addWidget(statusBar);

  //----

  connect(qApp, SIGNAL(focusChanged(QWidget *, QWidget *)),
          this, SLOT(focusChangedSlot(QWidget *, QWidget *)));
}

void
CQMetaEdit::
setInherited(bool inherited)
{
  inherited_ = inherited;

  propertyTree_->updateObject();
  layoutTree_  ->updateObject();
  signalTree_  ->updateObject();
  slotTree_    ->updateObject();
  widgetTree_  ->updateObject();
}

void
CQMetaEdit::
loadObjectName()
{
  QObject *object = CQUtil::nameToObject(objectNameEdit_->text());

  if (object)
    setObject(object);
}

void
CQMetaEdit::
loadParent()
{
  QWidget *parent = (widget() ? widget()->parentWidget() : nullptr);

  setObject(parent);
}

void
CQMetaEdit::
pickObject(QObject *object)
{
  setObject(object);
}

QObject *
CQMetaEdit::
object() const
{
  return object_;
}

void
CQMetaEdit::
setObject(QObject *obj)
{
  object_ = obj;

  if (object()) {
    objectNameEdit_->setText(CQUtil::fullName(object()));

    typeLabel_->setText(CQUtil::hierClassNames(object()).join(" "));
  }
  else {
    objectNameEdit_->setText("<no object>");

    typeLabel_->setText("<no type>");
  }

  parentLink_->setText  ("<no name>");
  parentLink_->setLinked(false);

  if      (widget()) {
    if (widget()->parentWidget()) {
      QString name = widget()->parentWidget()->objectName();

      if (name != "") {
        parentLink_->setText  (name);
        parentLink_->setLinked(true);
      }
    }
  }
  else if (object()) {
    if (object()->parent()) {
      QString name = object()->parent()->objectName();

      if (name != "") {
        parentLink_->setText  (name);
        parentLink_->setLinked(true);
      }
    }
  }

  layoutLabel_->setText("<no layout>");

  if (widget()) {
    if (widget()->layout()) {
      QString objName   = widget()->layout()->objectName();
      QString className = CQUtil::className(widget()->layout());

      if (objName == "")
        objName = "<no name>";

      layoutLabel_->setText(QString("%1 : %2").arg(className).arg(objName));
    }
  }

  //---

  propertyTree_->updateObject();
  layoutTree_  ->updateObject();
  signalTree_  ->updateObject();
  slotTree_    ->updateObject();
  widgetTree_  ->updateObject();
}

QWidget *
CQMetaEdit::
widget() const
{
  return qobject_cast<QWidget *>(object_);
}

void
CQMetaEdit::
snapshotSlot()
{
  QWidget *widget = this->widget();

  if (! widget)
    return;

  int w = widget->width ();
  int h = widget->height();

  QImage image = QImage(QSize(w, h), QImage::Format_ARGB32);

  QPainter painter;

  painter.begin(&image);

  widget->render(&painter);

  painter.end();

  image.save("snapshot.png");
}

void
CQMetaEdit::
focusChangedSlot(QWidget *, QWidget *newW)
{
  focusLabel_->setText(CQUtil::fullName(newW));
}
