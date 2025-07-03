#include "drawingwidget.h"
#include <QPainter>

DrawingWidget::DrawingWidget(QWidget *parent) : QWidget(parent) {
    posicionActual = QPointF(-20, -20); // Posición inicial fuera de la pantalla
    setPalette(QPalette(Qt::white));
    setAutoFillBackground(true);
    setMinimumSize(400, 400);
}

void DrawingWidget::actualizarPosicion(const QPointF& nuevaPos) {
    posicionActual = nuevaPos;
    update(); // Pide al widget que se repinte
}

void DrawingWidget::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setBrush(Qt::red);
    painter.drawEllipse(posicionActual, 10, 10);
}