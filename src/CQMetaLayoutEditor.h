#ifndef CQMetaLayoutEditor_H
#define CQMetaLayoutEditor_H

#include <QFrame>
#include <QPointer>

class CQMetaLayoutEditorCanvas;
class CQMetaLayoutEditorControl;
class CQMetaEdit;

class QLineEdit;
class QComboBox;
class QHBoxLayout;
class QVBoxLayout;
class QGridLayout;
class QLayoutItem;

class CQMetaLayoutEditor : public QFrame {
  Q_OBJECT

 public:
  CQMetaLayoutEditor(CQMetaEdit *edit);

  CQMetaEdit *edit() const { return edit_; }

  CQMetaLayoutEditorControl *control() const { return control_; }
  CQMetaLayoutEditorCanvas  *canvas () const { return canvas_; }

  void updateObject();

 private:
  CQMetaEdit* edit_ { nullptr };

  CQMetaLayoutEditorCanvas*  canvas_  { nullptr };
  CQMetaLayoutEditorControl* control_ { nullptr };
};

//---

class CQMetaLayoutEditorCanvas : public QFrame {
  Q_OBJECT

 public:
  CQMetaLayoutEditorCanvas(CQMetaLayoutEditor *editor);

  void mousePressEvent(QMouseEvent *e) override;

  void mouseDoubleClickEvent(QMouseEvent *e) override;

  int positionInd(const QPoint &p) const;

  void paintEvent(QPaintEvent *) override;

  QSize sizeHint() const override;

  bool event(QEvent *e) override;

  void showTip(const QPoint &);

 private:
  using WidgetP = QPointer<QWidget>;

  struct ItemData {
    int     ind { -1 };
    QRect   rect;
    QString name;
    WidgetP widget;
  };

  using ItemDatas = std::vector<ItemData>;

  CQMetaLayoutEditor* editor_ { nullptr };

  ItemDatas itemDatas_;
  ItemData  data_;
  WidgetP   widget_;
};

//---

class CQMetaLayoutEditorControl : public QFrame {
  Q_OBJECT

 public:
  struct ItemData {
    QLayout*     layout  { nullptr };
    QHBoxLayout* hlayout { nullptr };
    QVBoxLayout* vlayout { nullptr };
    QGridLayout* glayout { nullptr };
    int          ind     { -1 };
    QLayoutItem* item    { nullptr };
  };

 public:
  CQMetaLayoutEditorControl(CQMetaLayoutEditor *editor);

  void setInd(int ind);

 private Q_SLOTS:
  void editSlot();

 private:
  bool getItemData(ItemData &data);

  bool getItemPosition(const ItemData &data, int &row, int &col, int &rowSpan, int &colSpan);

 private:
  CQMetaLayoutEditor* editor_ { nullptr };

  QLineEdit* marginEdit_  { nullptr };
  QLineEdit* spacingEdit_ { nullptr };
  QLineEdit* rowEdit_     { nullptr };
  QLineEdit* colEdit_     { nullptr };
  QLineEdit* rowSpanEdit_ { nullptr };
  QLineEdit* colSpanEdit_ { nullptr };

  QComboBox* hsizePolicyCombo_ { nullptr };
  QComboBox* vsizePolicyCombo_ { nullptr };

  int ind_ { -1 };
};

#endif
