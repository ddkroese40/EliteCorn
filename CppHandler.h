#ifndef CPPHANDLER_H
#define CPPHANDLER_H

#include <QObject>
#include <QString>
#include <QUrl>
#include <QDebug>
#include <FileReader.h>
#include <Field.h>

class CppHandler : public QObject {
    Q_OBJECT
    Q_PROPERTY(int visiblePlantsCount READ visiblePlantsCount NOTIFY visiblePlantsCountChanged)
    Q_PROPERTY(QString highestScore READ highestScore NOTIFY highestScoreChanged)
    Q_PROPERTY(int highestScoreX READ highestScoreX NOTIFY highestScoreChanged)
    Q_PROPERTY(int highestScoreY READ highestScoreY NOTIFY highestScoreChanged)

public:
    CppHandler(QObject *parent = nullptr) : QObject(parent) {}
    int visiblePlantsCount() const { return m_visiblePlantsCount; }
    QString highestScore() const { return m_highestScore; }
    Q_INVOKABLE void processFile(const QString &fileUrl);
    int highestScoreX() const { return m_highestScoreX; }
    int highestScoreY() const { return m_highestScoreY; }
    Q_INVOKABLE QList<QList<int>> getGrid() const {
        return m_field.getGrid();  // Assuming 'field' is an instance of Field
    }



signals:
    void visiblePlantsCountChanged();
    void highestScoreChanged();

private:
    int m_visiblePlantsCount = 0;
    QString m_highestScore;
    int m_highestScoreX = -1;
    int m_highestScoreY = -1;
    Field m_field = Field({});
};

#endif // CPPHANDLER_H
