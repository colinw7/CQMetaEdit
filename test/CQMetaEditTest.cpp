#include <CQMetaEditTest.h>
#include <CQMetaEdit.h>
#include <CQApp.h>
#include <QPainter>

int
main(int argc, char **argv)
{
  CQApp app(argc, argv);

  CQMetaEdit *edit = new CQMetaEdit;

  edit->setObject(edit);

  edit->show();

  CQMetaEditTest *test = new CQMetaEditTest;

  test->show();

  return app.exec();
}

CQMetaEditTest::
CQMetaEditTest(QWidget *parent) :
 QFrame(parent)
{
  setObjectName("test");
}

void
CQMetaEditTest::
updateState()
{
  update();
}

void
CQMetaEditTest::
paintEvent(QPaintEvent *)
{
  QPainter p(this);

  p.fillRect(rect(), color_);

  p.setFont(font_);

  p.drawText(rect(), "ABC abc");
}
