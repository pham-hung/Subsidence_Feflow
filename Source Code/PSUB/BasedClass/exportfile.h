#ifndef EXPORTFILE_H
#define EXPORTFILE_H

#include <QObject>

class exportFile : public QObject
{
    Q_OBJECT
public:
    explicit exportFile(QObject *parent = nullptr);

signals:

public slots:
};

#endif // EXPORTFILE_H