#ifndef CQLinkLabel_H
#define CQLinkLabel_H

#include <QWidget>

class QPaintEvent;
class CQLinkLabel;

/*!
 * Simple label like widget which displays a hypertext like link text
 * which can be clicked on to generate a clicked() signal
 */
class CQLinkLabel : public QWidget {
  Q_OBJECT

  Q_PROPERTY(QString text      READ text      WRITE setText)
  Q_PROPERTY(QColor  linkColor READ linkColor WRITE setLinkColor)
  Q_PROPERTY(bool    linked    READ linked    WRITE setLinked)
  Q_PROPERTY(bool    enabled   READ enabled   WRITE setEnabled)

 public:
  CQLinkLabel(QWidget *parent, const QString &text="");
  CQLinkLabel(const QString &text="");

  const QString &text() const { return text_; }

  void setText(const QString &sizeText);

  const QColor &linkColor() const { return linkColor_; }
  void setLinkColor(const QColor &c);

  bool linked() const { return linked_; }
  void setLinked(bool linked);

  bool enabled() const { return enabled_; }
  void setEnabled(bool enabled);

 public slots:
  void click();

 signals:
  void clicked();

 private:
  void init();

  bool isActive() const { return active_; }

  void enterEvent(QEvent *e);
  void leaveEvent(QEvent *e);

  void paintEvent(QPaintEvent *);

  void mousePressEvent(QMouseEvent *);
  void mouseReleaseEvent(QMouseEvent *);
  void mouseDoubleClickEvent(QMouseEvent *);

  QSize sizeHint() const;
  QSize minimumSizeHint() const;

  QString encodeText(const QString &text) const;

 private:
  QString text_;
  QColor  linkColor_ { 0, 0, 255 };
  bool    enabled_   { true };
  bool    linked_    { true };
  bool    active_    { false };
  bool    pressed_   { false };
};

#endif
