#include "CppHandler.h"

void CppHandler::processFile(const QString &fileUrl) {
    std::string filePath = fileUrl.toStdString();
    qDebug() << filePath;
    FileReader fileReader;
    std::vector<std::vector<int>> grid = fileReader.readFile(filePath);

    if (grid.empty() || (grid.size() == 1 && grid[0][0] == -1)) {
        qWarning("Invalid file. Please ensure it's formatted correctly.");
        m_visiblePlantsCount = -1;
        emit visiblePlantsCountChanged();
        if (grid.empty()) {
            m_highestScore = QString("Error reading file");
        } else {
            m_highestScore = QString("File contains invalid characters\nPlease ensure the file has only digits (0-9)");
        }
        emit highestScoreChanged();
        return;
    }

    m_field = Field(grid);
    m_visiblePlantsCount = m_field.countVisiblePlantsFromOutside();
    emit visiblePlantsCountChanged();
    qDebug() << "Number of visible plants: " << m_visiblePlantsCount;

    // Calculate elite scores
    m_field.CalculateScores();
    auto [maxScore, location] = m_field.getHighestScoreAndLocation();
    m_highestScoreX = location.first;
    m_highestScoreY = location.second;
    qDebug() << m_highestScoreX;
    m_highestScore = QString("Top score: %1\nat (%2, %3)").arg(maxScore).arg(location.first).arg(location.second);
    emit highestScoreChanged();
}
