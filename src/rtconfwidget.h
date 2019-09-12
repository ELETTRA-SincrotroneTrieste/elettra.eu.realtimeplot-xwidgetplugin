#ifndef RTCONFWIDGET_H
#define RTCONFWIDGET_H

#include <QGroupBox>

class RTConfWidget : public QGroupBox {
    Q_OBJECT
public:
    RTConfWidget(QWidget *parent);

public slots:
    void applyClicked();
signals:
    void apply(int period, int nSamples);
    void hide();
};
#endif // RTCONFWIDGET_H
