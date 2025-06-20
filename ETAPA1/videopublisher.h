#ifndef VIDEOPUBLISHER_H
#define VIDEOPUBLISHER_H

#include "publisher.h"
#include <QWidget>
#include <string>
#include <QLineEdit>
#include <QPushButton>

class VideoPublisher : public QWidget, public Publisher
{

    Q_OBJECT
public:
    explicit VideoPublisher(string name, Broker* broker, string topicName, QWidget* parent = nullptr);

signals:
    void urlPublicada (const QString& url); // Cambiado a QString para compatibilidad con Qt

public slots:
    void publicarUrl();

private:
    QLineEdit* campoUrl;
    QPushButton* botonPublicar;

};
#endif // VIDEOPUBLISHER_H
