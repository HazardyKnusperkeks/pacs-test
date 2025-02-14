/**
 * @file
 * @brief Enthält die Deklaration des List-Views.
 * @author Björn Schäpers
 */

#ifndef LIST_VIEW_HPP
#define LIST_VIEW_HPP

#include <QWidget>

class ListView : public QWidget {
    Q_OBJECT
    public:
    explicit ListView(QWidget* parent = nullptr) noexcept;
};

#endif //LIST_VIEW_HPP
