#include <CQMetaEditTest.h>
#include <CQMetaEdit.h>
#include <CQApp.h>

#include <QPainter>
#include <QPushButton>
#include <QHBoxLayout>

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

  auto *layout = new QVBoxLayout(this);

  auto makeFrame = [&](const QString &name) {
    auto *frame = new QFrame;
    frame->setObjectName(name);
    layout->addWidget(frame);
    return frame;
  };

  auto *hframe = makeFrame("hframe");
  auto *vframe = makeFrame("vframe");
  auto *gframe = makeFrame("gframe");

  auto *hlayout = new QHBoxLayout(hframe); hlayout->setObjectName("hlayout");
  auto *vlayout = new QVBoxLayout(vframe); vlayout->setObjectName("vlayout");
  auto *glayout = new QGridLayout(gframe); glayout->setObjectName("glayout");

  auto makeButton = [&](const QString &name) {
    auto *button = new QPushButton(name);
    button->setObjectName(name);
    return button;
  };

  hlayout->addWidget(makeButton("One"));
  hlayout->addWidget(makeButton("Two"));
  hlayout->addSpacerItem(new QSpacerItem(4, 4));
  hlayout->addWidget(makeButton("Three"));

  auto *vlayout1 = new QVBoxLayout; vlayout->setObjectName("vlayout1");
  vlayout1->addWidget(makeButton("Four"));
  vlayout1->addWidget(makeButton("Five"));
  hlayout->addLayout(vlayout1);

  vlayout->addWidget(makeButton("One"));
  vlayout->addWidget(makeButton("Two"));
  vlayout->addSpacerItem(new QSpacerItem(4, 4));
  vlayout->addWidget(makeButton("Three"));

  auto *hlayout1 = new QHBoxLayout; vlayout->setObjectName("hlayout1");
  hlayout1->addWidget(makeButton("Four"));
  hlayout1->addWidget(makeButton("Five"));
  vlayout->addLayout(hlayout1);

  auto *gbutton1 = makeButton("One");
  auto *gbutton2 = makeButton("Two");
  auto *gbutton3 = makeButton("Three");

  glayout->addWidget(gbutton1, 0, 0);
  glayout->addWidget(gbutton2, 0, 1);
  glayout->addWidget(gbutton3, 1, 0);
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
