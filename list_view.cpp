/**
 * @file
 * @brief Enthält die Definition des List-Views.
 * @author Björn Schäpers
 */

#include "list_view.hpp"

#include <QHBoxLayout>
#include <QTreeView>

/**
 * @class ListView
 * @brief Ein List-View für Personendaten.
 * @author Björn Schäpers
 * @since V0.1 - 14.02.2025
 *
 * @property ListView::TheView
 * @brief Das eigentliche View.
 */

/**
 * @brief Konstruktor.
 * @author Björn Schäpers
 * @param[in] parent Qt-Parent.
 */
ListView::ListView(QWidget* parent) noexcept : QWidget{parent} {
    TheView = new QTreeView{this};
    TheView->setAllColumnsShowFocus(true);
    TheView->setHeaderHidden(true);
    TheView->setIndentation(0);
    TheView->setItemsExpandable(false);
    TheView->setRootIsDecorated(false);
    TheView->setUniformRowHeights(true);

    auto layout = new QHBoxLayout{this};
    layout->addWidget(TheView);
    return;
}

/**
 * @brief Setzt das Modell für das View.
 * @author Björn Schäpers
 * @param[in] model Das Modell.
 */
void ListView::setModel(QAbstractItemModel* model) noexcept {
    TheView->setModel(model);
    return;
}

#include "moc_list_view.cpp"
