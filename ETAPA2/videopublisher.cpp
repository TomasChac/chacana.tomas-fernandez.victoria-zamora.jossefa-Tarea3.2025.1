#include "videopublisher.h"
#include <QVBoxLayout>
#include <QString>
#include <string>

using namespace std;

// Constructor de VideoPublisher
VideoPublisher::VideoPublisher(std::string name, Broker* broker, std::string topicName, QWidget* parent)
    : QWidget(parent), Publisher(name, broker, topicName)
{
    // Crea el campo de texto donde el usuario ingresa la URL
    campoUrl = new QLineEdit(this);

    // Crea el botón para publicar la URL
    botonPublicar = new QPushButton("Publicar URL", this);

    // Crea un layout vertical y agrega los widgets
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(campoUrl); // Campo de texto para ingresar la URL
    layout->addWidget(botonPublicar); // Botón para publicar la URL
    setLayout(layout); // Establece el layout en la ventana

    // Conecta el clic del botón a la función publicarUrl()
    connect(botonPublicar, &QPushButton::clicked, this, &VideoPublisher::publicarUrl);
    //Conecta el evento de presionar Enter en el campo de texto a publicarUrl()
    connect(campoUrl, &QLineEdit::returnPressed, this, &VideoPublisher::publicarUrl);
}

void VideoPublisher::publicarUrl()
{
    // Obtiene el texto del campo de texto
    QString url = campoUrl->text().trimmed(); // Elimina espacios en blanco al inicio y al final

    if(url.isEmpty()) {
        // Si el campo de texto está vacío, no hace nada
        return;
    }
    // Llama al método publicar (de Publisher) con la URL como string estándar
    this->publicar(url.toStdString());

    // Emite la señal para notificar que se publicó una URL (útil para conectar con otros widgets)
    emit urlPublicada(url);

    // Limpia el campo de texto después de publicar
    campoUrl->clear();
}
