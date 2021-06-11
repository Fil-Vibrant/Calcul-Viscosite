#ifndef LOGS_H
#define LOGS_H

#include <QObject>
#include <QFile>
#include <QDir>
#include <QTextStream>
#include <QDateTime>

class Logs : public QObject
{
    Q_OBJECT
public:
    explicit Logs(QObject *parent);
    ~Logs();

private:
    QFile *file;

signals:
    public slots:
        void write(const QString &value, bool date);

};

#endif // LOGS_H
