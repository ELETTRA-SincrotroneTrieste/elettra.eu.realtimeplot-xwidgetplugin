#include "qurtplot.h"
#include <QHBoxLayout>
#include <quwatcher.h>
#include <quwriter.h>
#include <QPainter>
#include <QPaintEvent>
#include <QTimer>
#include <elettracolors.h>
#include <cucontrolsreader_abs.h>
#include <qustring.h>
#include <qustringlist.h>
#include <cucontextmenu.h>
#include <culinkstats.h>
#include <QPropertyAnimation>
#include <quplotcontextmenucomponent.h>

#include "rtconfwidget.h"

class QuRTPlotPrivate {
public:
    QuSpectrumPlot *plot;
};

QuRTPlot::QuRTPlot(QWidget *parent, Cumbia *cumbia, const CuControlsReaderFactoryI &r_fac ) : QWidget (parent)

{
    d = new QuRTPlotPrivate();
    d->plot = new QuSpectrumPlot(this, cumbia, r_fac);
    m_init();
}

QuRTPlot::QuRTPlot(QWidget *parent, CumbiaPool *cumbia_pool, const CuControlsFactoryPool &fpool)  : QWidget (parent)
{
    d = new QuRTPlotPrivate();
    d->plot = new QuSpectrumPlot(this, cumbia_pool, fpool);
    m_init();
}

QuRTPlot::~QuRTPlot()
{
    delete d->plot;
    delete findChild<RTConfWidget *>();
    delete d;
}

void QuRTPlot::m_init()
{
    QVBoxLayout *vlo = new QVBoxLayout(this);
    vlo->addWidget(d->plot);
    d->plot->setPeriod(100);
    d->plot->setXAxisAutoscaleEnabled(true);
    d->plot->setYAxisAutoscaleEnabled(true);
    d->plot->installEventFilter(this);
    RTConfWidget* cw = new RTConfWidget(this);
    cw->setMaximumHeight(0);
    vlo->addWidget(cw);
}

CuContext *QuRTPlot::getContext() const
{
    return d->plot->QuSpectrumPlot::getContext();
}

QString QuRTPlot::link() const
{
    return d->plot->QuSpectrumPlot::source();
}

void QuRTPlot::setLink(const QString &s)
{
    d->plot->QuSpectrumPlot::setSource(s);
}

void QuRTPlot::unsetLink()
{
    d->plot->QuSpectrumPlot::unsetSource(QString());
}

QuXtraWidgetI::Type QuRTPlot::getType() const
{
    return QuXtraWidgetI::Reader;
}

QSize QuRTPlot::minimumSizeHint() const
{
    QSize pmsh = d->plot->minimumSizeHint();
    QSize cmsh = findChild<RTConfWidget *>()->minimumSizeHint();
    return QSize(qMax(pmsh.width(), cmsh.width()), pmsh.height() + cmsh.height());
}

QStringList QuRTPlot::sources() const
{
    return d->plot->sources();
}

void QuRTPlot::setSources(const QStringList &srcs)
{
     d->plot->setSources(srcs);
}

void QuRTPlot::showRTConf()
{
    RTConfWidget *cw = findChild<RTConfWidget *>();
    connect(cw, SIGNAL(apply(int, int)), this, SLOT(applyRTConf(int, int)));
    connect(cw, SIGNAL(hide()), this, SLOT(hideRTConf()));
    QPropertyAnimation *a = cw->findChild<QPropertyAnimation *>();
    if(!a) {
        a = new QPropertyAnimation(cw, "maximumHeight");
        a->setDuration(200);
        a->setStartValue(0);
        a->setEndValue(cw->minimumSizeHint().height());
    }
    a->start();
}

void QuRTPlot::hideRTConf()
{
    RTConfWidget *cw = findChild<RTConfWidget *>();
    QPropertyAnimation *a = cw->findChild<QPropertyAnimation *>();
    if(!a) {
        a = new QPropertyAnimation(cw, "maximumHeight");
        a->setDuration(200);
        a->setStartValue(cw->height());
        a->setEndValue(0);
    }
    a->start();
}

void QuRTPlot::setRTConfVisible(bool vis)
{
    vis ? showRTConf() : hideRTConf();
}

void QuRTPlot::applyRTConf(int period, int nsam)
{
    QStringList srcs;
    if(period != d->plot->period())
        d->plot->setPeriod(period);
    foreach(QString s, d->plot->sources()) {
        QRegExp cmdRe("(.*)\\((\\d+),(\\d+)\\)");
        if(cmdRe.indexIn(s) > -1 && cmdRe.capturedTexts().size() > 3) {
            QStringList caps = cmdRe.capturedTexts();
            QString newSrc = QString("%1(%2,%3)").arg(caps[1]).arg(caps[2]).arg(nsam);
            srcs << newSrc;
        }
    }
    if(!srcs.isEmpty() && srcs != d->plot->sources())
        d->plot->setSources(srcs);
}

void QuRTPlot::setCloseButtonVisible(bool vis) {
    findChild<RTConfWidget *>()->findChild<QWidget *>("pbClose")->setVisible(vis);
}

void QuRTPlot::setApplyButtonVisible(bool vis) {
    findChild<RTConfWidget *>()->findChild<QWidget *>("pbApply")->setVisible(vis);
}

void QuRTPlot::applyConf() {
    findChild<RTConfWidget *>()->applyClicked();
}

bool QuRTPlot::closeButtonVisible() const {
    return findChild<RTConfWidget *>()->findChild<QWidget *>("pbClose")->isVisible();
}

bool QuRTPlot::applyButtonVisible() const {
    return findChild<RTConfWidget *>()->findChild<QWidget *>("pbApply")->isVisible();
}

bool QuRTPlot::eventFilter(QObject *watched, QEvent *event)
{
    if(event->type() == QEvent::ContextMenu) {
        QMenu *m = d->plot->contextMenuStrategy()->createMenu(d->plot);
        if(m) {
            m->addSeparator();
            m->addAction("Realtime plot...", this, SLOT(showRTConf()));
        }
        m->popup(static_cast<QContextMenuEvent *>(event)->globalPos());
        return true;
    }
    return QObject::eventFilter(watched, event);
}
