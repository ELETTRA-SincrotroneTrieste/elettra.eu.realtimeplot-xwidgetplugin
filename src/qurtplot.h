#ifndef TINTERVALSLIDER_H
#define TINTERVALSLIDER_H

#include <quspectrumplot.h>
#include <cudata.h>
#include <cudatalistener.h>
#include <quxtrawidgetplugininterface.h>

class Cumbia;
class CuControlsReaderFactoryI;
class QuRTPlotPrivate;

class QuRTPlot : public QWidget, public QuXtraWidgetI
{
    Q_OBJECT
    Q_PROPERTY(QString source READ link WRITE setLink)
    Q_PROPERTY(QStringList sources READ sources WRITE setSources)
    Q_PROPERTY(bool closeButtonVisible READ closeButtonVisible WRITE setCloseButtonVisible)
    Q_PROPERTY(bool applyButtonVisible READ applyButtonVisible WRITE setApplyButtonVisible)

public:
    QuRTPlot(QWidget *parent, Cumbia *cumbia, const CuControlsReaderFactoryI &r_fac);
    QuRTPlot(QWidget *parent, CumbiaPool *cumbia_pool, const CuControlsFactoryPool &fpool);

    ~QuRTPlot();

    // QuXtraWidgetI interface
    CuContext *getContext() const;
    QString link() const;
    void setLink(const QString &s);
    void unsetLink();
    QuXtraWidgetI::Type getType() const;

    QSize minimumSizeHint() const;

    QStringList sources() const;

    bool closeButtonVisible() const;
    bool applyButtonVisible() const;

public slots:
    void setSources(const QStringList& srcs);
    void showRTConf();
    void hideRTConf();
    void setRTConfVisible(bool vis);
    void applyRTConf(int period, int nsam);
    void setCloseButtonVisible(bool vis);
    void setApplyButtonVisible(bool vis);
    void applyConf();

protected:
    bool eventFilter(QObject *watched, QEvent *event);

private:
    QuRTPlotPrivate *d;

    void m_init();
};















#endif // TINTERVALSLIDER_H
