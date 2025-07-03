#ifndef DRAWINGWIDGET_H
#define DRAWINGWIDGET_H
#include <QWidget>
#include <QPointF>

class DrawingWidget : public QWidget {
    Q_OBJECT
public:
    explicit DrawingWidget(QWidget *parent = nullptr);
public slots:
    void actualizarPosicion(const QPointF& nuevaPos);
protected:
    void paintEvent(QPaintEvent *event) override;
private:
    QPointF posicionActual;
};
#endif