#include "videopublisher.h"
#include <QLineEdit>
#include <QVBoxLayout>
#include <QLabel>

VideoPublisher::VideoPublisher(QWidget *parent) : QWidget(parent) {
    urlLineEdit = new QLineEdit();
    urlLineEdit->setPlaceholderText("Ingresar URL de video y presionar Enter");
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(new QLabel("<b>Publicador (Tópico: Video)</b>"));
    layout->addWidget(urlLineEdit);
    connect(urlLineEdit, &QLineEdit::returnPressed, this, &VideoPublisher::onPublish);
}

void VideoPublisher::onPublish() {
    emit wantsToPublish("Video", urlLineEdit->text());
    urlLineEdit->clear();
}