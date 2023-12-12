#include "qurtplot2.h"
#include <QMenu>
#include <QDialog>
#include <QGridLayout>
#include <QLabel>
#include <QSpinBox>
#include <QPushButton>

QuRTPlot2::QuRTPlot2(QWidget *parent, Cumbia *cumbia, const CuControlsReaderFactoryI &r_fac)
 : QuSpectrumPlot (parent, cumbia, r_fac) {
    setYAxisAutoscaleEnabled(true);
}

QuRTPlot2::QuRTPlot2(QWidget *parent, CumbiaPool *cumbia_pool, const CuControlsFactoryPool &fpool)
 : QuSpectrumPlot (parent, cumbia_pool, fpool) {
    setYAxisAutoscaleEnabled(true);
}

QuRTPlot2::~QuRTPlot2() {

}

QStringList QuRTPlot2::sources() const {
    return QuSpectrumPlot::sources();
}

void QuRTPlot2::contextMenuEvent(QContextMenuEvent *e) {
    QMenu *menu = contextMenuStrategy()->createMenu(this);
    menu->addAction("Configure real time plot...", this, SLOT(configureRT()));
    menu->exec(QCursor::pos());
}

void QuRTPlot2::setSources(const QStringList &srcs) {
    QuSpectrumPlot::setSources(srcs);
}

void QuRTPlot2::configureRT() {
    QDialog d(this);
    QGridLayout *lo = new QGridLayout(&d);
    lo->setContentsMargins(3,3,3,3);
    lo->setSpacing(lo->spacing() / 3);
    QLabel *lperiod = new QLabel("Period", &d);
    lperiod->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *lnsam = new QLabel("Number of samples", &d);
    lnsam->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QSpinBox *sbperiod = new QSpinBox(&d);
    sbperiod->setMinimum(10);
    sbperiod->setMaximum(10000);
    sbperiod->setValue(100);
    sbperiod->setSuffix("ms");
    sbperiod->setObjectName("sbperiod");
    QSpinBox *sbSamples = new QSpinBox (&d);
    sbSamples->setMinimum(10);
    sbSamples->setMaximum(1000000);
    sbSamples->setValue(1000);
    sbSamples->setObjectName("sbnsam");

    lo->addWidget(lperiod, 0, 0, 1, 2);
    lo->addWidget(sbperiod, 0, 2, 1, 2);
    lo->addWidget(lnsam, 0, 4, 1, 2);
    lo->addWidget(sbSamples, 0, 6, 1, 2);

    QPushButton *pbClose = new QPushButton("Close", &d);
    pbClose->setObjectName("pbClose");
    connect(pbClose, SIGNAL(clicked()), &d, SLOT(reject()));
    lo->addWidget(pbClose, 1, 0, 1, 1);
    QPushButton *pbApply = new QPushButton("Apply", &d);
    pbApply->setObjectName("pbApply");
    lo->addWidget(pbApply, 1, 7, 1, 1);
    connect(pbApply, SIGNAL(clicked()), &d, SLOT(accept()));

    if(d.exec() == QDialog::Accepted) {
        int timeout = sbperiod->value();
        int nsam = sbSamples->value();
        QStringList srcs;
        if(timeout != period())
            setPeriod(timeout);
        foreach(QString s, sources()) {
            QRegularExpression cmdRe("(.*)\\((\\d+),(\\d+)\\)");
            QRegularExpressionMatch ma = cmdRe.match(s);
            if(ma.hasMatch() && ma.capturedTexts().size() > 3) {
                QStringList caps = ma.capturedTexts();
                QString newSrc = QString("%1(%2,%3)").arg(caps[1]).arg(caps[2]).arg(nsam);
                srcs << newSrc;
            }
        }
        if(!srcs.isEmpty() && srcs != sources())
            setSources(srcs);
    }
}

CuContext *QuRTPlot2::getContext() const {
    return QuSpectrumPlot::getContext();
}

QString QuRTPlot2::link() const {
    return QuSpectrumPlot::source();
}

void QuRTPlot2::setLink(const QString &s) {
    QuSpectrumPlot::setSource(s);
}

void QuRTPlot2::unsetLink() {
    QuSpectrumPlot::unsetSource(QString());
}

QuXtraWidgetI::Type QuRTPlot2::getType() const {
    return  QuXtraWidgetI::Reader;
}
