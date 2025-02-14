/**
 * @file
 * @brief Enthält die Definition des List-Views.
 * @author Björn Schäpers
 */

#include "list_view.hpp"

#include "columns.hpp"
#include "vip_delegate.hpp"

#include <QHBoxLayout>
#include <QHeaderView>
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

    TheView->setItemDelegateForColumn(static_cast<int>(Column::Vip), new VipDelegate{this});

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
    TheView->header()->resizeSections(QHeaderView::ResizeMode::ResizeToContents);
    return;
}

/**
 * @brief Setzt die empfohlene Größe des Widgets.
 * @author Björn Schäpers
 * @return Die Größe.
 *
 * Das ist für das Beispiel in diesem Programm angepasst.
 */
QSize ListView::sizeHint(void) const noexcept {
    return {600, 400};
}

#include "moc_list_view.cpp"
