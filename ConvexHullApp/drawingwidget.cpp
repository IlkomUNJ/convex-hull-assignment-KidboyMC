#include "drawingwidget.h"
#include <QPainter>
#include <QMouseEvent>
#include <QSet>
#include <QMap>
#include <algorithm>

// Custom QPoint less-than operator for sorting and maps
bool operator<(const QPoint& a, const QPoint& b) {
    return a.x() < b.x() || (a.x() == b.x() && a.y() < b.y());
}

DrawingWidget::DrawingWidget(QWidget *parent)
    : QWidget(parent), m_slowIterations(0), m_fastIterations(0), m_hullCalculated(false)
{
    // Set a white background
    QPalette pal = palette();
    pal.setColor(QPalette::Window, Qt::white);
    setAutoFillBackground(true);
    setPalette(pal);
}

void DrawingWidget::runAllConvexHull()
{
    if (m_points.size() < 3) return;

    // Run both algorithms to get iteration counts
    calculateSlowConvexHull();
    calculateFastConvexHull(); // This will set the final m_hullPoints for drawing

    m_hullCalculated = true;
    update(); // Trigger a repaint
}

void DrawingWidget::clearCanvas()
{
    m_points.clear();
    m_hullPoints.clear();
    m_slowIterations = 0;
    m_fastIterations = 0;
    m_hullCalculated = false;
    update(); // Trigger a repaint
}

void DrawingWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // 1. Draw all the points
    painter.setBrush(Qt::red);
    painter.setPen(Qt::NoPen);
    for (const QPoint &p : m_points) {
        painter.drawEllipse(p, 3, 3);
    }

    // 2. If the hull is calculated, draw it
    if (m_hullCalculated && m_hullPoints.size() > 1) {
        painter.setPen(QPen(Qt::blue, 2));
        painter.setBrush(Qt::NoBrush);
        QPolygon hullPolygon(m_hullPoints);
        painter.drawPolygon(hullPolygon);
    }

    // 3. Write the iteration counts on the canvas
    if (m_hullCalculated) {
        painter.setPen(Qt::black);
        painter.setFont(QFont("Arial", 12));
        painter.drawText(10, 25, QString("SlowCONVEXHULL Iterations: %1").arg(m_slowIterations));
        painter.drawText(10, 50, QString("CONVEXHULL Iterations: %1").arg(m_fastIterations));
    }
}

void DrawingWidget::mousePressEvent(QMouseEvent *event)
{
    // Add point on left-click
    if (event->button() == Qt::LeftButton) {
        m_points.append(event->pos());
        m_hullCalculated = false; // New point invalidates old hull
        update(); // Trigger repaint to show the new point
    }
}

// Determines the orientation of the ordered triplet (p, q, r)
// Returns:
// 0 --> p, q and r are collinear
// 1 --> Clockwise (right turn)
// 2 --> Counterclockwise (left turn)
int DrawingWidget::orientation(const QPoint &p, const QPoint &q, const QPoint &r) {
    // Using long long to avoid overflow
    long long val = (long long)(q.y() - p.y()) * (r.x() - q.x()) -
                    (long long)(q.x() - p.x()) * (r.y() - q.y());

    if (val == 0) return 0;  // Collinear
    return (val > 0) ? 2 : 1; // Left turn (CCW) or Right turn (CW)
}

// Algorithm SLOWCONVEXHULL(P)
void DrawingWidget::calculateSlowConvexHull()
{
    m_slowIterations = 0;
    if (m_points.size() < 3) return;

    QSet<QPair<QPoint, QPoint>> edgeSet;

    for (int i = 0; i < m_points.size(); ++i) {
        for (int j = 0; j < m_points.size(); ++j) {
            if (i == j) continue;

            const QPoint &p = m_points[i];
            const QPoint &q = m_points[j];
            bool valid = true;

            for (int k = 0; k < m_points.size(); ++k) {
                if (k == i || k == j) continue;
                m_slowIterations++; // Counting the core check
                // For a clockwise hull edge (p,q), all other points 'r' must be to its right or collinear.
                // If any point 'r' is to the left, this edge is not on the hull.
                if (orientation(p, q, m_points[k]) == 2) { // 2 is Counterclockwise (left turn)
                    valid = false;
                    break;
                }
            }

            if (valid) {
                edgeSet.insert({p, q});
            }
        }
    }

    // The iteration count is now set. We don't need to assemble the hull from this
    // algorithm because the fast one is more reliable for drawing. The goal was to track iterations.
}


// Algorithm CONVEXHULL(P) - Andrew's Monotone Chain variant
void DrawingWidget::calculateFastConvexHull() {
    m_fastIterations = 0;
    int n = m_points.size();
    if (n <= 2) {
        m_hullPoints = m_points;
        return;
    }

    QVector<QPoint> sortedPoints = m_points;
    std::sort(sortedPoints.begin(), sortedPoints.end());

    // Build upper hull
    QVector<QPoint> upperHull;
    for (const QPoint &p : sortedPoints) {
        while (upperHull.size() >= 2) {
            m_fastIterations++; // Counting the core check
            // If the last 3 points make a right turn, pop the middle one
            // We want to maintain a "left turn" chain
            if (orientation(upperHull[upperHull.size()-2], upperHull.back(), p) != 2) { // Not a left turn
                upperHull.pop_back();
            } else {
                break;
            }
        }
        upperHull.push_back(p);
    }

    // Build lower hull
    QVector<QPoint> lowerHull;
    for (int i = n - 1; i >= 0; --i) {
        const QPoint &p = sortedPoints[i];
        while (lowerHull.size() >= 2) {
            m_fastIterations++; // Counting the core check
            if (orientation(lowerHull[lowerHull.size()-2], lowerHull.back(), p) != 2) { // Not a left turn
                lowerHull.pop_back();
            } else {
                break;
            }
        }
        lowerHull.push_back(p);
    }

    // Remove the first and last points from the lower hull to avoid duplicates
    lowerHull.removeFirst();
    lowerHull.removeLast();

    // Combine hulls
    m_hullPoints = upperHull + lowerHull;
}
