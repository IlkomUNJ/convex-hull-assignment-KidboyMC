#ifndef DRAWINGWIDGET_H
#define DRAWINGWIDGET_H

#include <QWidget>
#include <QVector>
#include <QPoint>

class DrawingWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DrawingWidget(QWidget *parent = nullptr);

public slots:
    void runAllConvexHull();
    void clearCanvas();

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

private:
    // Helper function for orientation check (left/right turn)
    int orientation(const QPoint &p, const QPoint &q, const QPoint &r);

    // Algorithm implementations
    void calculateSlowConvexHull();
    void calculateFastConvexHull();

    QVector<QPoint> m_points;
    QVector<QPoint> m_hullPoints;

    long long m_slowIterations;
    long long m_fastIterations;
    bool m_hullCalculated;
};

#endif // DRAWINGWIDGET_H
