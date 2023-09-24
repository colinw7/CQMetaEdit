#include <CQMetaLayoutEditor.h>
#include <CQMetaEdit.h>

#include <QLineEdit>
#include <QComboBox>
#include <QLabel>
#include <QPainter>
#include <QLayout>
#include <QHelpEvent>
#include <QToolTip>

CQMetaLayoutEditor::
CQMetaLayoutEditor(CQMetaEdit *edit) :
 edit_(edit)
{
  setObjectName("layoutEditor");

  auto *layout = new QVBoxLayout(this);

  canvas_  = new CQMetaLayoutEditorCanvas(this);
  control_ = new CQMetaLayoutEditorControl(this);

  layout->addWidget(canvas_);
  layout->addWidget(control_);
}

void
CQMetaLayoutEditor::
updateObject()
{
  control_->setInd(-1);

  canvas_->update();
  update();
}

//---

CQMetaLayoutEditorCanvas::
CQMetaLayoutEditorCanvas(CQMetaLayoutEditor *editor) :
 editor_(editor)
{
  setObjectName("canvas");

  setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

void
CQMetaLayoutEditorCanvas::
mousePressEvent(QMouseEvent *e)
{
  auto p = e->pos();

  auto ind = positionInd(p);

  if (ind >= 0)
    data_ = itemDatas_[ind];
  else
    data_ = ItemData();

  editor_->control()->setInd(data_.ind);

  update();
}

void
CQMetaLayoutEditorCanvas::
mouseDoubleClickEvent(QMouseEvent *e)
{
  auto p = e->pos();

  auto ind = positionInd(p);
  if (ind < 0) return;

  auto *w = editor_->edit()->widget();
  if (! w) return;

  auto *layout = w->layout();
  if (! layout) return;

  auto *item = layout->itemAt(ind);

  auto *iwidget = item->widget();
  auto *ilayout = item->layout();

  if      (iwidget)
    editor_->edit()->setObject(iwidget);
  else if (ilayout)
    editor_->edit()->setObject(ilayout);
}

int
CQMetaLayoutEditorCanvas::
positionInd(const QPoint &p) const
{
  int ind = 0;

  for (const auto &itemData : itemDatas_) {
    if (itemData.rect.contains(p))
      return ind;

    ++ind;
  }

  return -1;
}

void
CQMetaLayoutEditorCanvas::
paintEvent(QPaintEvent *)
{
  QPainter painter(this);

  auto prect = this->rect();

  painter.fillRect(prect, Qt::white);

  //---

  itemDatas_.clear();

  //---

  auto *w = editor_->edit()->widget();
  if (! w) return;

  auto *layout = w->layout();
  if (! layout) return;

  auto wrect = w->rect();

  auto xf = double(prect.width ())/double(wrect.width ());
  auto yf = double(prect.height())/double(wrect.height());

  auto remapRect = [&](const QRect &r) {
    auto x1 = (r.left() - wrect.left())*xf;
    auto y1 = (r.top () - wrect.top ())*yf;

    auto xf1 = double(r.width ())/double(wrect.width ());
    auto yf1 = double(r.height())/double(wrect.height());

    auto w1 = prect.width ()*xf1;
    auto h1 = prect.height()*yf1;

    return QRect(x1, y1, w1, h1);
  };

  int n = layout->count();

  for (int i = 0; i < n; ++i) {
    auto *item = layout->itemAt(i);

    auto *lw = item->widget();

    auto rect  = item->geometry();
    auto rect1 = remapRect(rect);

    painter.setPen(Qt::black);
    painter.setBrush(data_.ind == i ? Qt::green : Qt::gray);

    painter.drawRect(rect1);

    auto *ll = item->layout();
    auto *ls = item->spacerItem();

    QString name;

    if (lw) {
      name = lw->objectName();

      if (name == "")
        name = lw->metaObject()->className();
    }
    else if (ll) {
      name = ll->objectName();

      if (name == "")
        name = ll->metaObject()->className();
    }
    else if (ls) {
      name = "<spacer>";
    }

    painter.drawText(rect1, name);

    //---

    ItemData data;

    data.ind    = i;
    data.rect   = rect1;
    data.name   = name;
    data.widget = lw;

    itemDatas_.push_back(data);
  }
}

QSize
CQMetaLayoutEditorCanvas::
sizeHint() const
{
  return QSize(256, 256);
}

bool
CQMetaLayoutEditorCanvas::
event(QEvent *e)
{
  switch (e->type()) {
    case QEvent::ToolTip: {
      auto *he = static_cast<QHelpEvent *>(e);
      showTip(he->globalPos());
      break;
    }
    default:
      break;
  }

  return QWidget::event(e);
}

void
CQMetaLayoutEditorCanvas::
showTip(const QPoint &gp)
{
  ItemData data;

  auto p = mapFromGlobal(gp);

  for (const auto &itemData : itemDatas_) {
    if (itemData.rect.contains(p)) {
      data = itemData;
      break;
    }
  }

  //---

  if (data.ind >= 0) {
    auto *w = editor_->edit()->widget();

    auto *layout  = (w ? w->layout() : nullptr);
    auto *hlayout = qobject_cast<QHBoxLayout *>(layout);
    auto *vlayout = qobject_cast<QVBoxLayout *>(layout);
    auto *glayout = qobject_cast<QGridLayout *>(layout);

    auto *item = (layout ? layout->itemAt(data.ind) : nullptr);

//  auto *lw = (item ? item->widget() : nullptr);
//  auto *ll = (item ? item->layout() : nullptr);
//  auto *ls = (item ? item->spacerItem() : nullptr);

    auto tip = "Name: " + data.name;

    if (hlayout || vlayout) {
      auto *blayout = (hlayout ? qobject_cast<QBoxLayout *>(hlayout) :
                                 qobject_cast<QBoxLayout *>(vlayout));

      auto margin  = blayout->margin();
      auto spacing = blayout->spacing();

      tip += "\nMargin: "  + QString::number(margin);
      tip += "\nSpacing: " + QString::number(spacing);
    }

    auto getItemPosition = [&](int &row, int &col, int &rowSpan, int &colSpan) {
      row     = 0;
      col     = 0;
      rowSpan = 1;
      colSpan = 1;

      if      (glayout)
        glayout->getItemPosition(data.ind, &row, &col, &rowSpan, &colSpan);
      else if (hlayout)
        row = data.ind;
      else if (vlayout)
        col = data.ind;

      return true;
    };

    int row, col, rowSpan, colSpan;
    getItemPosition(row, col, rowSpan, colSpan);

    tip += "\nRow: " + QString::number(row);
    tip += "\nCol: " + QString::number(col);
    tip += "\nRowSpan: " + QString::number(rowSpan);
    tip += "\nColSpan: " + QString::number(colSpan);

    if (item) {
      QString alignStr;

      auto addAlignStr = [&](const QString &str) {
        if (alignStr != "") alignStr += "|";
        alignStr += str;
      };

      auto align = item->alignment();

      if (align & Qt::AlignLeft    ) addAlignStr("left");
      if (align & Qt::AlignRight   ) addAlignStr("right");
      if (align & Qt::AlignHCenter ) addAlignStr("hcenter");
      if (align & Qt::AlignJustify ) addAlignStr("justify");
      if (align & Qt::AlignTop     ) addAlignStr("top");
      if (align & Qt::AlignBottom  ) addAlignStr("bottom");
      if (align & Qt::AlignVCenter ) addAlignStr("vcenter");
      if (align & Qt::AlignBaseline) addAlignStr("baseline");

      if (alignStr == "")
        addAlignStr("None");

      tip += "\nAlignment: " + alignStr;

      //---

      QString expandStr;

      auto addExpandStr = [&](const QString &str) {
        if (expandStr != "") expandStr += "|";
        expandStr += str;
      };

      auto orients = item->expandingDirections();

      if (orients & Qt::Horizontal) addExpandStr("Horizontal");
      if (orients & Qt::Vertical  ) addExpandStr("Vertical");
      if (expandStr == ""         ) addExpandStr("None");

      tip += "\nExpand: " + expandStr;

      //---

      auto sizeToString = [&](const QString &label, const QSize &s) {
        return label + ": " + QString::number(s.width()) + " " + QString::number(s.height());
      };

      tip += "\n" + sizeToString("Minimum Size", item->minimumSize());
      tip += "\n" + sizeToString("Maximum Size", item->maximumSize());
    }

    QToolTip::showText(gp, tip);
  }
  else
    QToolTip::hideText();
}

//-----

CQMetaLayoutEditorControl::
CQMetaLayoutEditorControl(CQMetaLayoutEditor *editor) :
 editor_(editor)
{
  setObjectName("control");

  setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

  //---

  auto *layout = new QVBoxLayout(this);
  layout->setMargin(2); layout->setSpacing(2);

  auto addFrameWidget= [&](const QString &name, QWidget *edit) {
    auto *frame = new QFrame;

    auto *flayout = new QHBoxLayout(frame);
    flayout->setMargin(2); flayout->setSpacing(2);

    flayout->addWidget(new QLabel(name));
    flayout->addWidget(edit);

    layout->addWidget(frame);

    return frame;
  };

  auto addFrameEdit = [&](const QString &id, const QString &name, QLineEdit* &edit) {
    edit = new QLineEdit;
    edit->setProperty("id", id);

    connect(edit, SIGNAL(editingFinished()), this, SLOT(editSlot()));

    return addFrameWidget(name, edit);
  };

  auto addFrameCombo = [&](const QString &id, const QString &name, QComboBox* &combo) {
    combo = new QComboBox;
    combo->setProperty("id", id);

    connect(combo, SIGNAL(currentIndexChanged(int)), this, SLOT(editSlot()));

    return addFrameWidget(name, combo);
  };

  addFrameEdit("margin" , "Margin"  , marginEdit_);
  addFrameEdit("spacing", "Spacing" , spacingEdit_);
  addFrameEdit("row"    , "Row"     , rowEdit_);
  addFrameEdit("col"    , "Col"     , colEdit_);
  addFrameEdit("rowSpan", "Row Span", rowSpanEdit_);
  addFrameEdit("colSpan", "Col Span", colSpanEdit_);

  auto sizePolicyStrs = (QStringList() <<
    "Fixed" << "Minimum" << "Maximum" << "Preferred" <<
    "Expanding" << "MinimumExpanding" << "Ignored");

  addFrameCombo("hsizePolicy", "HSize Policy", hsizePolicyCombo_);
  addFrameCombo("vsizePolicy", "VSize Policy", vsizePolicyCombo_);

  hsizePolicyCombo_->addItems(sizePolicyStrs);
  vsizePolicyCombo_->addItems(sizePolicyStrs);
}

void
CQMetaLayoutEditorControl::
setInd(int ind)
{
  ind_ = ind;

  ItemData data;
  if (! getItemData(data))
    return;

  int margin { 0 }, spacing { 0 };

  if (data.layout) {
    margin  = data.layout->margin();
    spacing = data.layout->spacing();
  }

  int row { 0 }, col { 0 }, rowSpan { 1 }, colSpan { 1 };
  getItemPosition(data, row, col, rowSpan, colSpan);

  marginEdit_ ->setText(QString::number(margin));
  spacingEdit_->setText(QString::number(spacing));
  rowEdit_    ->setText(QString::number(row));
  colEdit_    ->setText(QString::number(col));
  rowSpanEdit_->setText(QString::number(rowSpan));
  colSpanEdit_->setText(QString::number(colSpan));

  auto *w = (data.item ? data.item->widget() : nullptr);

  if (w) {
    auto sp = w->sizePolicy();

    auto policyInd = [](const QSizePolicy::Policy p) {
      switch (p) {
        default:
        case QSizePolicy::Fixed           : return 0;
        case QSizePolicy::Minimum         : return 1;
        case QSizePolicy::Maximum         : return 2;
        case QSizePolicy::Preferred       : return 3;
        case QSizePolicy::Expanding       : return 4;
        case QSizePolicy::MinimumExpanding: return 5;
        case QSizePolicy::Ignored         : return 6;
      }
    };

    hsizePolicyCombo_->setCurrentIndex(policyInd(sp.horizontalPolicy()));
    vsizePolicyCombo_->setCurrentIndex(policyInd(sp.verticalPolicy  ()));
  }
}

void
CQMetaLayoutEditorControl::
editSlot()
{
  auto *w = qobject_cast<QWidget *>(sender());
  assert(w);

  auto id = w->property("id").toString();

  auto *edit  = qobject_cast<QLineEdit *>(sender());
  auto *combo = qobject_cast<QComboBox *>(sender());

  ItemData data;
  if (! getItemData(data))
    return;

  if (edit) {
    bool ok;
    int i = edit->text().toInt(&ok);

    bool changed { false };
    int  margin1 { 0 }, spacing1 { 0 };

    if (data.layout) {
      margin1  = data.layout->margin();
      spacing1 = data.layout->spacing();
    }
    int margin  = margin1;
    int spacing = spacing1;

    int row1 { 0 }, col1 { 0 }, rowSpan1 { 1 }, colSpan1 { 1 };
    getItemPosition(data, row1, col1, rowSpan1, colSpan1);
    int row = row1, col = col1, rowSpan = rowSpan1, colSpan = colSpan1;

    if      (id == "margin" ) { margin  = i; changed = (margin  != margin1 ); }
    else if (id == "spacing") { spacing = i; changed = (spacing != spacing1); }
    else if (id == "row"    ) { row     = i; changed = (row     != row1    ); }
    else if (id == "col"    ) { col     = i; changed = (col     != col1    ); }
    else if (id == "rowSpan") { rowSpan = i; changed = (rowSpan != rowSpan1); }
    else if (id == "colSpan") { colSpan = i; changed = (colSpan != colSpan1); }

    if (! changed) return;

    if (data.layout) {
      data.layout->setMargin (margin);
      data.layout->setSpacing(spacing);
    }

    int n = data.layout->count();

  //auto *widget = (data.item ? data.item->widget() : nullptr);
  //auto *layout = (data.item ? data.item->layout() : nullptr);
  //auto *spacer = (data.item ? data.item->spacer() : nullptr);

    if (data.glayout) {
      data.item = data.layout->takeAt(ind_);

      data.glayout->addItem(data.item, row, col, rowSpan, colSpan);
    }
    else if (data.hlayout) {
      if (col != col1) {
        std::vector<QLayoutItem *> items;

        for (int i = 0; i < n; ++i) {
          auto *item = data.layout->takeAt(0);
          items.push_back(item);
        }

        auto *item1 = items[col1];
        for (int i = col1 + 1; i < n; ++i)
          items[i - 1] = items[i];
        for (int i = n - 1; i >= col; --i)
          items[i + 1] = items[i];
        items[col] = item1;

        for (auto *item : items)
          data.layout->addItem(item);
      }
    }
    else if (data.vlayout) {
      if (row != row1) {
        std::vector<QLayoutItem *> items;

        for (int i = 0; i < n; ++i) {
          auto *item = data.layout->takeAt(0);
          items.push_back(item);
        }

        auto *item1 = items[row1];
        for (int i = row1 + 1; i < n; ++i)
          items[i - 1] = items[i];
        for (int i = n - 1; i >= row; --i)
          items[i] = items[i - 1];
        items[row] = item1;

        for (auto *item : items)
          data.layout->addItem(item);
      }
    }

    //---

    for (int i = 0; i < n; ++i) {
      auto *item = data.layout->itemAt(i);

      if (item == data.item) {
        ind_ = i;
        break;
      }
    }

    editor_->canvas()->update();
  }

  if (combo) {
    auto indPolicy = [](int ind) {
      switch (ind) {
        default:
        case 0: return QSizePolicy::Fixed;
        case 1: return QSizePolicy::Minimum;
        case 2: return QSizePolicy::Maximum;
        case 3: return QSizePolicy::Preferred;
        case 4: return QSizePolicy::Expanding;
        case 5: return QSizePolicy::MinimumExpanding;
        case 6: return QSizePolicy::Ignored;
      }
    };

    int ind = combo->currentIndex();

    auto *widget = (data.item ? data.item->widget() : nullptr);

    if (widget) {
      auto sp = widget->sizePolicy();

      if      (id == "hsizePolicy") {
        sp.setHorizontalPolicy(indPolicy(ind));
      }
      else if (id == "vsizePolicy") {
        sp.setVerticalPolicy(indPolicy(ind));
      }

      widget->setSizePolicy(sp);

      editor_->canvas()->update();
    }
  }
}

bool
CQMetaLayoutEditorControl::
getItemData(ItemData &data)
{
  auto *w = editor_->edit()->widget();
  if (! w) return false;

  data.layout = w->layout();
  if (! data.layout) return false;

  data.hlayout = qobject_cast<QHBoxLayout *>(data.layout);
  data.vlayout = qobject_cast<QVBoxLayout *>(data.layout);
  data.glayout = qobject_cast<QGridLayout *>(data.layout);

  int n = data.layout->count();

  if (ind_ >= 0 && ind_ < n) {
    data.ind  = ind_;
    data.item = data.layout->itemAt(ind_);
  }
  else {
    data.ind  = -1;
    data.item = nullptr;
  }

  return true;
}

bool
CQMetaLayoutEditorControl::
getItemPosition(const ItemData &data, int &row, int &col, int &rowSpan, int &colSpan)
{
  row     = 0;
  col     = 0;
  rowSpan = 1;
  colSpan = 1;

  if (! data.item)
    return false;

  if      (data.glayout)
    data.glayout->getItemPosition(data.ind, &row, &col, &rowSpan, &colSpan);
  else if (data.hlayout)
    col = data.ind;
  else if (data.vlayout)
    row = data.ind;

  return true;
}
