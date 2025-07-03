# Tarea 3: Simulador Gráfico Publicador-Suscriptor en C++/Qt

Este proyecto es la implementación de la Tarea 3 para el curso de Diseño y Programación Orientados a Objetos. El objetivo es desarrollar un simulador gráfico del patrón de diseño Publicador-Suscriptor utilizando C++ y el framework Qt, traduciendo y ampliando los conceptos de una tarea previa desarrollada en Java.

## Información del Curso
* *Asignatura:* ELO329 - Diseño y Programación Orientados a Objetos
* *Semestre:* 1er Semestre 2025
* *Universidad:* Universidad Técnica Federico Santa María

## Integrantes
* Tomás Chacana
* Victoria Fernández
* Josefa Zamora

## Descripción del Proyecto

La aplicación simula un sistema desacoplado donde diferentes "Publicadores" emiten información a "Tópicos" específicos, y los "Suscriptores" que están interesados en esos tópicos reaccionan a los mensajes. La comunicación es gestionada por un *Broker* central implementado como un Singleton.

El simulador cuenta con dos sistemas principales:

1.  *Sistema de Video:*
    * Un *Publicador* permite ingresar URLs de video.
    * Un *Suscriptor* muestra el último URL recibido en un botón y, al hacerle clic, abre una nueva ventana para reproducir el video.

2.  *Sistema de GPS:*
    * Un *Publicador* carga una ruta desde un archivo de texto (.txt) con formato tiempo x y.
    * El publicador interpola las posiciones y emite una nueva coordenada cada segundo.
    * Un *Suscriptor* muestra la última coordenada recibida y, en una ventana separada, dibuja un punto rojo que sigue la trayectoria del vehículo en un lienzo gráfico.

## Requisitos de Entorno (Linux Mint / Ubuntu)
* Compilador C++17 (g++)
* Paquete build-essential
* Qt 5 (versión de desarrollo): qt5-default
* Módulos de Qt Multimedia: qtmultimedia5-dev
* Plugins de GStreamer para la reproducción de video:
    bash
    sudo apt-get install gstreamer1.0-plugins-base gstreamer1.0-plugins-good gstreamer1.0-plugins-bad gstreamer1.0-plugins-ugly gstreamer1.0-libav libqt5multimedia5-plugins
    

## Instrucciones de Compilación y Ejecución

1.  *Clonar el repositorio* o descargar los archivos fuente en una carpeta.
2.  *Abrir una terminal* en la carpeta del proyecto (ej. ETAPA4/).
3.  *Generar el Makefile* usando qmake:
    bash
    qmake ETAPA4.pro
    
4.  *Compilar el proyecto* usando make:
    bash
    make
    
5.  *Ejecutar la aplicación*:
    bash
    ./SimuladorGrafico
    

## Guía de Uso de la Aplicación

### Prueba del Sistema de Video
1.  En el campo de texto del *Publicador de Video*, ingrese una URL válida de un video (ej. un .mp4).
2.  Presione la tecla Enter.
3.  Observe cómo el botón del *Suscriptor de Video* actualiza su texto con la URL ingresada.
4.  Haga clic en el botón del suscriptor para abrir una nueva ventana y reproducir el video.

### Prueba del Sistema de GPS
1.  Asegúrese de tener un archivo de texto (ej. posiciones.txt) en la misma carpeta del ejecutable con coordenadas en formato tiempo x y.
2.  En la aplicación, haga clic en el botón *"Cargar Archivo GPS"*.
3.  Seleccione el archivo posiciones.txt.
4.  La publicación comenzará automáticamente. Observe cómo la etiqueta del *Suscriptor de GPS* se actualiza cada segundo y cómo una nueva ventana ("Car Tracker") muestra un punto rojo moviéndose.
