#ifndef FIELD_H
#define FIELD_H

#include <vector>
#include <QObject>
#include <QDebug>

class Field {
public:
    Field(const std::vector<std::vector<int>>& gridData) : grid(gridData) {}
    int countVisiblePlantsFromOutside() const;
    void CalculateScores();
    void displayGrid() const;
    std::pair<int, std::pair<int, int>> getHighestScoreAndLocation() const;

    Q_INVOKABLE QList<QList<int>> getGrid() const {
        QList<QList<int>> gridList;
        for (const auto& row : grid) {
            QList<int> rowList;
            for (const auto& value : row) {
                rowList.append(value);
            }
            gridList.append(rowList);
        }
        qDebug() << "rows: " << gridList.count();
        return gridList;
    }

private:
    std::vector<std::vector<int>> score_map;
    std::vector<std::vector<int>> grid;
};

#endif
