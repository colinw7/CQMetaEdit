#include <QFrame>

class CQMetaEditTest : public QFrame {
  Q_OBJECT

 public:
  Q_PROPERTY(QColor color READ color WRITE setColor)
  Q_PROPERTY(QFont  font  READ font  WRITE setFont )

 public:
  CQMetaEditTest(QWidget *parent=nullptr);

  const QColor &color() const { return color_; }
  void setColor(const QColor &v) { color_ = v; updateState(); }

  const QFont &font() const { return font_; }
  void setFont(const QFont &v) { font_ = v; updateState(); }

  void updateState();

  void paintEvent(QPaintEvent *) override;

 private:
  QColor color_;
  QFont  font_;
};
