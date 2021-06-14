#include "logs.h"

Logs::Logs(QObject *parent) : QObject(parent) {

    if (!QDir(QDir::currentPath() + "/logs").exists()) {
        QDir(QDir::currentPath()).mkdir("logs");
    }

    QString fileName = QDir::currentPath() + "/logs/" + QDateTime::currentDateTime().toString("yyyy-MM-dd hh-mm-ss") +".log";

    file = new QFile;
    file->setFileName(fileName);
    file->open(QIODevice::Append | QIODevice::Text);
    write("=== Démarage ===", false);
}

/**
 * Ecrire un message dans les logs
 *
 * @brief Logs::write
 * @param value Texte a écrire
 * @param date Afficher la date ou pas
 */

void Logs::write(const QString &value, bool date) {

    QString text = value;// + "";
    if (date) {
        text = QDateTime::currentDateTime().toString("[dd/MM/yyyy hh:mm:ss] ") + text;
    }
    
    text += "\n";
    
    QTextStream out(file);
    out.setCodec("UTF-8");
    if (file != 0) {
         out << text;
    }
}

Logs::~Logs() {
    write("=== Fin ===", false);
    if (file != 0) {
        file->close();
    }
}
