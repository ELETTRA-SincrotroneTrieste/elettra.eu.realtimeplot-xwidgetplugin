#include "rtconfwidget.h"
#include <QGridLayout>
#include <QLabel>
#include <QSpinBox>
#include <QPushButton>

RTConfWidget::RTConfWidget(QWidget *parent) : QGroupBox (parent)
{
    QGridLayout *lo = new QGridLayout(this);
    lo->setMargin(3);
    lo->setSpacing(lo->spacing() / 3);
    QLabel *lperiod = new QLabel("Period", this);
    lperiod->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *lnsam = new QLabel("Number of samples", this);
    lnsam->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QSpinBox *sbperiod = new QSpinBox(this);
    sbperiod->setMinimum(10);
    sbperiod->setMaximum(10000);
    sbperiod->setValue(100);
    sbperiod->setSuffix("ms");
    sbperiod->setObjectName("sbperiod");
    QSpinBox *sbSamples = new QSpinBox (this);
    sbSamples->setMinimum(10);
    sbSamples->setMaximum(1000000);
    sbSamples->setValue(1000);
    sbSamples->setObjectName("sbnsam");

    lo->addWidget(lperiod, 0, 0, 1, 2);
    lo->addWidget(sbperiod, 0, 2, 1, 2);
    lo->addWidget(lnsam, 0, 4, 1, 2);
    lo->addWidget(sbSamples, 0, 6, 1, 2);

    QPushButton *pbClose = new QPushButton("Close", this);
    pbClose->setObjectName("pbClose");
    connect(pbClose, SIGNAL(clicked()), this, SIGNAL(hide()));
    lo->addWidget(pbClose, 1, 0, 1, 1);
    QPushButton *pbApply = new QPushButton("Apply", this);
    pbApply->setObjectName("pbApply");
    lo->addWidget(pbApply, 1, 7, 1, 1);
    connect(pbApply, SIGNAL(clicked()), this, SLOT(applyClicked()));

    setTitle("Configure real time plot");
}


void RTConfWidget::applyClicked()
{
    emit apply(findChild<QSpinBox *>("sbperiod")->value(), findChild<QSpinBox *>("sbnsam")->value());
}
