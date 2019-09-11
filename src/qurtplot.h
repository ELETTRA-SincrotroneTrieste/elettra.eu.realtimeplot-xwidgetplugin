#ifndef TINTERVALSLIDER_H
#define TINTERVALSLIDER_H

#include <quspectrumplot.h>
#include <cudata.h>
#include <cudatalistener.h>
#include <quxtrawidgetplugininterface.h>
#include <QGroupBox>

class Cumbia;
class CuControlsReaderFactoryI;
class QuRTPlotPrivate;

//class CtxMenuObjFilter : public QObject {
//    Q_OBJECT
//public:
//    virtual bool eventFilter(QObject *watched, QEvent *event);
//};

class RTConfWidget : public QGroupBox {
    Q_OBJECT
public:
    RTConfWidget(QWidget *parent);

private slots:
    void applyClicked();
signals:
    void apply(int period, int nSamples);
    void hide();
};

class QuRTPlot : public QWidget, public QuXtraWidgetI
{
    Q_OBJECT
    Q_PROPERTY(QString source READ link WRITE setLink)
    Q_PROPERTY(QStringList sources READ sources WRITE setSources)

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

public slots:
    void setSources(const QStringList& srcs);

protected:
    void contextMenuEvent(QContextMenuEvent* e);

    bool eventFilter(QObject *watched, QEvent *event);
protected slots:
    void showRTConf();
    void hideRTConf();
    void applyRTConf(int period, int nsam);

private:
    QuRTPlotPrivate *d;

    void m_init();
};















#endif // TINTERVALSLIDER_H
