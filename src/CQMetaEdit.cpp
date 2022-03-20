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
#include <CQIconButton.h>

#include <QApplication>
#include <QTabWidget>
#include <QLineEdit>
#include <QToolButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QPainter>
#include <QRubberBand>

#include <svg/icon_svg.h>

#include <svg/image_bw_light_svg.h>
#include <svg/image_bw_dark_svg.h>

CQMetaEdit::
CQMetaEdit(QWidget *parent) :
 QFrame(parent)
{
  setWindowTitle("Meta Edit");
  setWindowIcon (CQPixmapCacheInst->getIcon("ICON"));

  setObjectName("edit");

  auto *layout = CQUtil::makeLayout<QVBoxLayout>(this, 0, 2);

  //---

  auto *objectFrame = CQUtil::makeWidget<QFrame>("objectFrame");

  layout->addWidget(objectFrame);

  auto *objectLayout = CQUtil::makeLayout<QVBoxLayout>(objectFrame, 2, 2);

  //---

  auto *objectDetailsFrame = CQUtil::makeWidget<QFrame>("objectDetailsFrame");

  objectLayout->addWidget(objectDetailsFrame);

  auto *objectDetailsLayout = CQUtil::makeLayout<QGridLayout>(objectDetailsFrame, 0, 2);

  //---

  QFontMetrics fm(font());

  picker_ = CQUtil::makeWidget<CQPicker>();

  picker_->setSize(3*fm.height());
  picker_->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

  connect(picker_, SIGNAL(objectPicked(QObject *)), this, SLOT(pickObject(QObject *)));

  objectDetailsLayout->addWidget(picker_, 0, 0, 4, 1);

  //---

  nameLink_ = CQUtil::makeWidget<CQLinkLabel>("nameLink");
  nameLink_->setText("Name");

  connect(nameLink_, SIGNAL(clicked()), this, SLOT(showObject()));

  objectNameEdit_ = CQUtil::makeWidget<QLineEdit>("objectNameEdit");

  objectDetailsLayout->addWidget(nameLink_      , 0, 1);
  objectDetailsLayout->addWidget(objectNameEdit_, 0, 2, 1, 2);

  connect(objectNameEdit_, SIGNAL(returnPressed()), this, SLOT(loadObjectName()));

  //---

  typeLabel_ = CQUtil::makeWidget<QLabel>("typeLabel");

  objectDetailsLayout->addWidget(CQUtil::makeLabelWidget<QLabel>("Type", "label"), 1, 1);
  objectDetailsLayout->addWidget(typeLabel_                                      , 1, 2, 1, 2);

  //---

  parentLink_ = CQUtil::makeWidget<CQLinkLabel>("parentLink");
  parentLink_->setText("<no name>");

  parentLabel_ = CQUtil::makeWidget<QLabel>("parentLabel");

  connect(parentLink_, SIGNAL(clicked()), this, SLOT(loadParent()));

  objectDetailsLayout->addWidget(CQUtil::makeLabelWidget<QLabel>("Parent", "label"), 2, 1);
  objectDetailsLayout->addWidget(parentLink_                                       , 2, 2);
  objectDetailsLayout->addWidget(parentLabel_                                      , 2, 3);

  //---

  layoutLabel_ = CQUtil::makeWidget<QLabel>("layoutLabel");

  objectDetailsLayout->addWidget(CQUtil::makeLabelWidget<QLabel>("Layout", "label"), 3, 1);
  objectDetailsLayout->addWidget(layoutLabel_                                      , 3, 2, 1, 2);

  //---

  objectDetailsLayout->setColumnStretch(2, 1);

  //------

  auto *tab = CQUtil::makeWidget<QTabWidget>("tab");

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

  auto *snapButton = CQUtil::makeWidget<CQIconButton>();

  snapButton->setIcon("IMAGE_BW");

  connect(snapButton, SIGNAL(clicked()), this, SLOT(snapshotSlot()));

  tab->setCornerWidget(snapButton);

  //----

  auto *statusBar = CQUtil::makeWidget<QFrame>("statusBar");

  auto *statusLayout = CQUtil::makeLayout<QHBoxLayout>(statusBar, 2, 2);

  focusLabel_ = CQUtil::makeWidget<QLabel>("label");

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
  auto *object = CQUtil::nameToObject(objectNameEdit_->text());

  if (object)
    setObject(object);
}

void
CQMetaEdit::
showObject()
{
  if (! widget())
    return;

  auto rect  = widget()->rect();
  auto rtl   = widget()->mapToGlobal(rect.topLeft());
  auto rbr   = widget()->mapToGlobal(rect.bottomRight());
  auto rrect = QRect(rtl, rbr);

  if (! rubberBand_)
    rubberBand_ = new QRubberBand(QRubberBand::Rectangle);

  rubberBand_->setGeometry(rrect);

  rubberBand_->show();
}

void
CQMetaEdit::
loadParent()
{
  auto *parent = (widget() ? widget()->parentWidget() : nullptr);

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
  if (obj == object_)
    return;

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

  parentLabel_->setText("");

  if      (widget()) {
    if (widget()->parentWidget()) {
      auto name = widget()->parentWidget()->objectName();

      if (name != "") {
        parentLink_->setText  (name);
        parentLink_->setLinked(true);
      }

      parentLabel_->setText(QString("(%1)").arg(CQUtil::className(widget()->parentWidget())));
    }
  }
  else if (object()) {
    if (object()->parent()) {
      auto name = object()->parent()->objectName();

      if (name != "") {
        parentLink_->setText  (name);
        parentLink_->setLinked(true);
      }

      parentLabel_->setText(QString("(%1)").arg(CQUtil::className(object()->parent())));
    }
  }

  layoutLabel_->setText("<no layout>");

  if (widget()) {
    if (widget()->layout()) {
      auto objName   = widget()->layout()->objectName();
      auto className = CQUtil::className(widget()->layout());

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

  //---

  if (rubberBand_)
    rubberBand_->hide();

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
  auto *widget = this->widget();

  if (! widget)
    return;

  int w = widget->width ();
  int h = widget->height();

  auto image = QImage(QSize(w, h), QImage::Format_ARGB32);

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
