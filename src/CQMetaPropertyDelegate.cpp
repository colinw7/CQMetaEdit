#include <CQMetaPropertyDelegate.h>
#include <CQMetaPropertyTree.h>
#include <CQMetaEdit.h>

#include <CQColorChooser.h>
#include <CQFontChooser.h>
#include <CQIntegerEdit.h>
#include <CQUtil.h>

#include <QCheckBox>
#include <QLineEdit>
#include <QComboBox>
#include <QPainter>

CQMetaPropertyDelegate::
CQMetaPropertyDelegate(CQMetaPropertyTree *tree) :
 QItemDelegate(tree), tree_(tree)
{
}

void
CQMetaPropertyDelegate::
paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
  CQMetaEdit *edit = tree_->edit();

  if      (index.column() == 0) {
    CQUtil::PropInfo propInfo;

    if (CQUtil::getPropertyInfo(tree_->object(), index.row(), &propInfo, edit->inherited())) {
      QStyleOptionViewItem option1 = option;

      if (! propInfo.isWritable())
        option1.font.setItalic(true);

      QItemDelegate::paint(painter, option1, index);
    }
    else
      QItemDelegate::paint(painter, option, index);
  }
  else if (index.column() == 1) {
    QItemDelegate::paint(painter, option, index);
  }
  else if (index.column() == 2) {
    QVariant value = CQUtil::getPropertyValue(tree_->object(), index.row(), edit->inherited());

    if      (value.type() == QVariant::Rect  || value.type() == QVariant::RectF ||
             value.type() == QVariant::Size  || value.type() == QVariant::SizeF ||
             value.type() == QVariant::Point || value.type() == QVariant::PointF ||
             value.type() == QVariant::Region || value.type() == QVariant::Locale ||
             value.type() == QVariant::Palette || value.type() == QVariant::SizePolicy) {
      QString text;

      if (CQUtil::variantToString(value, text)) {
        drawBackground(painter, option, index);

        drawDisplay(painter, option, option.rect, text);
      }
    }
    else if (value.type() == QVariant::Cursor) {
      QCursor cursor = value.value<QCursor>();

      const QBitmap* bm   = cursor.bitmap();
      const QBitmap* mask = cursor.mask();
      QPixmap        pm   = cursor.pixmap();

      if (bm) {
        QString text = "bitmap";

        if (mask)
          text += ":mask";

        drawDisplay(painter, option, option.rect, text);
      }
      else if (! pm.isNull()) {
        painter->drawPixmap(option.rect.topLeft(), pm);
      }
      else {
        Qt::CursorShape shape = cursor.shape();

        QString text = QString("%1").arg(shape);

        drawDisplay(painter, option, option.rect, text);
      }
    }
    else if (value.type() == QVariant::Icon) {
      QIcon icon = value.value<QIcon>();

      if (! icon.isNull()) {
        QPixmap pm = icon.pixmap(option.rect.size());

        if (! pm.isNull())
          painter->drawPixmap(option.rect.topLeft(), pm);
      }
    }
    else if (CQUtil::getPropertyValueIsEnum(tree_->object(), index.row(), edit->inherited())) {
      drawBackground(painter, option, index);

      QString text =
        CQUtil::getPropertyEnumValue(tree_->object(), index.row(), edit->inherited());

      drawDisplay(painter, option, option.rect, text);
    }
    else if (value.type() == QVariant::UserType) {
      QString text;

      if (CQUtil::userVariantToString(value, text)) {
        drawBackground(painter, option, index);

        drawDisplay(painter, option, option.rect, text);
      }
    }
    else {
      QItemDelegate::paint(painter, option, index);
    }
  }
  else {
    QItemDelegate::paint(painter, option, index);
  }
}

QWidget *
CQMetaPropertyDelegate::
createEditor(QWidget *parent, const QStyleOptionViewItem &, const QModelIndex &index) const
{
  CQMetaEdit *edit = tree_->edit();

  CQUtil::PropInfo propInfo;

  if (CQUtil::getPropertyInfo(tree_->object(), index.row(), &propInfo, edit->inherited())) {
    if (! propInfo.isWritable())
      return nullptr;
  }

  if (index.column() == 2) {
    QVariant value = CQUtil::getPropertyValue(tree_->object(), index.row(), edit->inherited());

    // bool - create toggle
    if      (value.type() == QVariant::Bool) {
      QCheckBox *edit = new QCheckBox(parent);

      edit->setAutoFillBackground(true);

      return edit;
    }
    else if (value.type() == QVariant::Int) {
      // enum - create combobox
      if (CQUtil::getPropertyValueIsEnum(tree_->object(), index.row(), edit->inherited())) {
        QStringList names  =
          CQUtil::getMetaPropertyEnumNames (tree_->object(), index.row(), edit->inherited());
        QList<int>  values =
          CQUtil::getMetaPropertyEnumValues(tree_->object(), index.row(), edit->inherited());

        QComboBox *edit = new QComboBox(parent);

        for (int i = 0; i < names.size(); ++i)
          edit->addItem(names[i], values[i]);

        return edit;
      }
      // int line edit
      else {
        CQIntegerEdit *edit = new CQIntegerEdit(parent);

        edit->setAutoFillBackground(true);

        return edit;
      }
    }
    else if (value.type() == QVariant::String) {
      QLineEdit *edit = new QLineEdit(parent);

      edit->setAutoFillBackground(true);

      return edit;
    }
    else if (value.type() == QVariant::Color) {
      CQColorChooser *edit = new CQColorChooser(parent);

      edit->setAutoFillBackground(true);

      return edit;
    }
    else if (value.type() == QVariant::Font) {
      CQFontChooser *edit = new CQFontChooser(parent);

      edit->setAutoFillBackground(true);

      return edit;
    }
    else if (value.type() == QVariant::UserType) {
      QLineEdit *edit = new QLineEdit(parent);

      edit->setAutoFillBackground(true);

      return edit;
    }
    else {
      return nullptr;
    }
  }
  else {
    return nullptr;
  }
}

// set editor from model
void
CQMetaPropertyDelegate::
setEditorData(QWidget *w, const QModelIndex &index) const
{
  CQMetaEdit *edit = tree_->edit();

  if (index.column() == 2) {
    QVariant value = CQUtil::getPropertyValue(tree_->object(), index.row(), edit->inherited());

    if      (value.type() == QVariant::Bool) {
      QCheckBox *edit = qobject_cast<QCheckBox *>(w);
      assert(edit);

      bool b = index.model()->data(index, Qt::EditRole).toBool();

      edit->setChecked(b);

      edit->setText(edit->isChecked() ? "true" : "false");
    }
    else if (value.type() == QVariant::Int) {
      if (CQUtil::getPropertyValueIsEnum(tree_->object(), index.row(), edit->inherited())) {
        QComboBox *edit = qobject_cast<QComboBox *>(w);
        assert(edit);

        int value = index.model()->data(index, Qt::EditRole).toInt();

        int ind = edit->findData(value);

        if (ind >= 0)
          edit->setCurrentIndex(ind);
      }
      else {
        CQIntegerEdit *edit = qobject_cast<CQIntegerEdit *>(w);
        assert(edit);

        int value = index.model()->data(index, Qt::EditRole).toInt();

        edit->setValue(value);
      }
    }
    else if (value.type() == QVariant::String) {
      QLineEdit *edit = qobject_cast<QLineEdit *>(w);
      assert(edit);

      QString text = index.model()->data(index, Qt::EditRole).toString();

      edit->setText(text);
    }
    else if (value.type() == QVariant::String) {
      QLineEdit *edit = qobject_cast<QLineEdit *>(w);
      assert(edit);

      QString text = index.model()->data(index, Qt::EditRole).toString();

      edit->setText(text);
    }
    else if (value.type() == QVariant::Color) {
      CQColorChooser *edit = qobject_cast<CQColorChooser *>(w);
      assert(edit);

      QColor color = index.model()->data(index, Qt::EditRole).value<QColor>();

      edit->setColor(color);
    }
    else if (value.type() == QVariant::Font) {
      CQFontChooser *edit = qobject_cast<CQFontChooser *>(w);
      assert(edit);

      QFont font = index.model()->data(index, Qt::EditRole).value<QFont>();

      edit->setFont(font);
    }
    else if (value.type() == QVariant::UserType) {
      QLineEdit *edit = qobject_cast<QLineEdit *>(w);
      assert(edit);

      QVariant var = index.model()->data(index, Qt::EditRole);

      QString text;

      if (CQUtil::userVariantToString(var, text))
        edit->setText(text);
    }
    else {
      return;
    }
  }
  else {
    return;
  }
}

// set model from editor
void
CQMetaPropertyDelegate::
setModelData(QWidget *w, QAbstractItemModel *model, const QModelIndex &index) const
{
  CQMetaEdit *edit = tree_->edit();

  if (index.column() == 2) {
    QVariant value = CQUtil::getPropertyValue(tree_->object(), index.row(), edit->inherited());

    if      (value.type() == QVariant::Bool) {
      QCheckBox *edit = qobject_cast<QCheckBox *>(w);
      assert(edit);

      model->setData(index, edit->isChecked(), Qt::EditRole);
    }
    else if (value.type() == QVariant::Int) {
      if (CQUtil::getPropertyValueIsEnum(tree_->object(), index.row(), edit->inherited())) {
        QComboBox *edit = qobject_cast<QComboBox *>(w);
        assert(edit);

        int ind = edit->currentIndex();

        int value = edit->itemData(ind).toInt();

        model->setData(index, value, Qt::EditRole);
      }
      else {
        CQIntegerEdit *edit = qobject_cast<CQIntegerEdit *>(w);
        assert(edit);

        int value = edit->getValue();

        model->setData(index, value, Qt::EditRole);
      }
    }
    else if (value.type() == QVariant::String) {
      QLineEdit *edit = qobject_cast<QLineEdit *>(w);
      assert(edit);

      model->setData(index, edit->text(), Qt::EditRole);
    }
    else if (value.type() == QVariant::Color) {
      CQColorChooser *edit = qobject_cast<CQColorChooser *>(w);
      assert(edit);

      model->setData(index, edit->color(), Qt::EditRole);
    }
    else if (value.type() == QVariant::Font) {
      CQFontChooser *edit = qobject_cast<CQFontChooser *>(w);
      assert(edit);

      model->setData(index, edit->font(), Qt::EditRole);
    }
    else if (value.type() == QVariant::UserType) {
      QLineEdit *edit = qobject_cast<QLineEdit *>(w);
      assert(edit);

      QVariant var = index.model()->data(index, Qt::EditRole);

      if (CQUtil::userVariantFromString(var, edit->text()))
        model->setData(index, var, Qt::EditRole);
    }
    else {
      return;
    }
  }
  else {
    return;
  }
}
