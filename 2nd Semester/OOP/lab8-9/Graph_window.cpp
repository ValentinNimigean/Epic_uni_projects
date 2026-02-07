//
// Created by valen on 5/22/2024.
//

#include "Graph_window.h"
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include<QPainter>

Size_Chart::Size_Chart(QWidget *parent): QWidget(parent) {
    setFixedSize(500, 500);
}

void Size_Chart::populate(const std::vector<TrencchCoat> &coats) {
    sizes.clear();
    for (const auto &coat: coats) {
        sizes[QString::fromStdString(coat.getSize())]+=coat.getQuantity();
    }
    update();
}

void Size_Chart::paintEvent(QPaintEvent *event) {
    QWidget::paintEvent(event);

    if (sizes.isEmpty()) {
        return;
    }

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.fillRect(rect(), Qt::white);
    // Define dimensions and spacing
    int margin = 40;
    int barWidth = 50;
    int spacing = 30;
    int maxBarHeight = height() - 2 * margin;
    int maxBarValue = *std::max_element(sizes.begin(), sizes.end());

    // Calculate total width required
    int totalWidth = sizes.size() * (barWidth + spacing) - spacing;

    // Determine the start x position
    int startX = (width() - totalWidth) / 2;

    // Define colors for the bars
    QVector<QColor> colors = {Qt::cyan, Qt::magenta, Qt::red, Qt::darkRed, Qt::darkGreen, Qt::blue, Qt::yellow, Qt::darkCyan, Qt::darkMagenta};

    int i = 0;
    for (auto it = sizes.begin(); it != sizes.end(); ++it, ++i) {
        // Calculate bar height
        int barHeight = (it.value() * maxBarHeight) / maxBarValue;

        // Draw the bar
        QRect barRect(startX + i * (barWidth + spacing), height() - margin - barHeight, barWidth, barHeight);
        painter.setBrush(colors[i % colors.size()]);
        painter.setPen(Qt::NoPen);
        painter.drawRect(barRect);

        // Draw the size name with a border
        painter.setPen(Qt::black);
        QRect textRect(barRect.bottomLeft() + QPoint(-10, 5), QSize(barWidth + 20, margin / 2));
        painter.drawText(textRect, Qt::AlignCenter, it.key());

        // Draw the value above the bar with a different color
        painter.setPen(colors[(i + 1) % colors.size()]);
        painter.drawText(barRect.topLeft() + QPoint(-10, -10), QString::number(it.value()));
    }

    // Draw the axes
    painter.setPen(Qt::black);
    painter.drawLine(margin, height() - margin, width() - margin, height() - margin); // X axis
    painter.drawLine(margin, height() - margin, margin, margin); // Y axis

    // Draw the axis labels
    painter.drawText(margin - 30, margin - 20, "Number of Coats");
    painter.drawText(width() - margin, height() - margin + 30, "Size");
}





