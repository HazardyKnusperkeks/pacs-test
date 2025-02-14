/**
 * @file
 * @brief Enthält die Definition des List-Views.
 * @author Björn Schäpers
 */

#include "list_view.hpp"

/**
 * @class ListView
 * @brief Ein List-View für Personendaten.
 * @author Björn Schäpers
 * @since V0.1 - 14.02.2025
 */

/**
 * @brief Konstruktor.
 * @author Björn Schäpers
 * @param[in] parent Qt-Parent.
 */
ListView::ListView(QWidget* parent) noexcept : QWidget{parent} {
    return;
}

#include "moc_list_view.cpp"
