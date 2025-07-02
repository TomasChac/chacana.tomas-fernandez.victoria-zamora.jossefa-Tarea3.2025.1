#ifndef VIDEOPUBLISHER_H
#define VIDEOPUBLISHER_H
#include <QWidget>
class QLineEdit;

class VideoPublisher : public QWidget {
    Q_OBJECT
public:
    explicit VideoPublisher(QWidget *parent = nullptr);
signals:
    void wantsToPublish(const QString& topic, const QString& message);
private slots:
    void onPublish();
private:
    QLineEdit *urlLineEdit;
};
#endif