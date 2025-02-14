/**
 * @file
 * @brief Enthält die Definition des Personen-Modells.
 * @author Björn Schäpers
 */

#include "person_model.hpp"

#include <QDate>
#include <QPixmap>

using namespace Qt::StringLiterals;

enum class Column {
    Image,
    FirstName,
    LastName,
    DateOfBirth,
    Mail,
    Vip,
    Count,
};

/**
 * @class PersonModel
 * @brief Ein einfaches Modell für Personen-Daten.
 * @author Björn Schäpers
 * @since V0.1 - 14.02.2025
 *
 * @property PersonModel::Data
 * @brief Die Daten im Modell.
 */

/**
 * @brief Die Daten zu einer Person.
 * @author Björn Schäpers
 */
struct PersonModel::PersonData {
    /** @brief Das Bild zur Person. */
    QPixmap Image;
    /** @brief Der Vorname. */
    QString FirstName;
    /** @brief Der Nachname. */
    QString LastName;
    /** @brief Der Geburtstag. */
    QDate   DateOfBirth;
    /** @brief Die Mail-Adresse. */
    QString Mail;
    /** @brief Ob die Person eine VIP ist. */
    bool    IsVip;
};

/**
 * @brief Konstruktor.
 * @author Björn Schäpers
 * @param[in] parent Qt-Parent.
 */
PersonModel::PersonModel(QObject* parent) noexcept : QAbstractItemModel{parent} {
    return;
}

/**
 * @brief Destruktor.
 * @author Björn Schäpers
 */
PersonModel::~PersonModel(void) noexcept = default;

/**
 * @brief Fügt Testdaten in das Modell ein.
 * @author Björn Schäpers
 */
void PersonModel::populateWithTestData(void) noexcept {
    beginResetModel();
    QPixmap image{32, 32};
    image.fill(Qt::GlobalColor::red);
    Data.emplace_back(image, "Hugo"_L1, "B."_L1, QDate{1967, 4, 2}, "xyz.xyz@android.com"_L1, false);

    image.fill(Qt::GlobalColor::cyan);
    Data.emplace_back(image, "James"_L1, "Friendship"_L1, QDate{1969, 2, 3}, "abc.abc@android.com"_L1, false);

    image.fill(Qt::GlobalColor::black);
    Data.emplace_back(image, "Anand"_L1, "A."_L1, QDate{1999, 12, 12}, "def.def@android.com"_L1, true);

    image.fill(Qt::GlobalColor::darkYellow);
    Data.emplace_back(image, "John"_L1, "Smith"_L1, QDate{2007, 2, 1}, "ghi.ghi@android.com"_L1, false);

    image.fill(Qt::GlobalColor::darkGray);
    Data.emplace_back(image, "Larry"_L1, "Page"_L1, QDate{1973, 3, 26}, "jkl.jkl@android.com"_L1, false);

    image.fill(Qt::GlobalColor::yellow);
    Data.emplace_back(image, QString::fromUtf8("Matías"), "Duarte"_L1, QDate{1973, 1, 30}, "mno.mno@android.com"_L1,
                      false);

    image.fill(Qt::GlobalColor::green);
    Data.emplace_back(image, "Jane"_L1, "Smith"_L1, QDate{1967, 4, 2}, "pqr.pqr@android.com"_L1, true);

    image.fill(Qt::GlobalColor::gray);
    Data.emplace_back(image, "Android"_L1, "User"_L1, QDate{1925, 5, 5}, "stu.stu@android.com"_L1, false);

    image.fill(Qt::GlobalColor::blue);
    Data.emplace_back(image, QString::fromUtf8("Björn"), QString::fromUtf8("Schäpers"), QDate{1985, 8, 3},
                      "github@hazardy.de"_L1, true);

    image.fill(Qt::GlobalColor::darkMagenta);
    Data.emplace_back(image, "John"_L1, "Doe"_L1, QDate{1966, 6, 28}, "john.doe@example.com"_L1, false);

    endResetModel();
    return;
}

/**
 * @brief Generiert den Index für einen Modell-Eintrag.
 * @author Björn Schäpers
 * @param[in] row Die gefragte Zeile.
 * @param[in] column Die gefragte Spalte.
 * @param[in] parent Der Eltern-Index, dessen Kinder gesucht werden.
 * @return Der Index.
 */
QModelIndex PersonModel::index(int row, int column, const QModelIndex& parent) const noexcept {
    if ( parent.isValid() ) {
        return {};
    } //if ( parent.isValid() )

    if ( row >= std::ssize(Data) || column >= static_cast<int>(Column::Count) ) {
        return {};
    } //if ( row >= std::ssize(Data) || column >= static_cast<int>(Column::Count) )

    return createIndex(row, column);
}

/**
 * @brief Liefert den Eltern-Index zu einem Index.
 * @author Björn Schäpers
 * @param[in] child Der Index zu dem gefragt wird.
 * @return Der Eltern-Indx.
 */
QModelIndex PersonModel::parent(const QModelIndex& /*child*/) const noexcept {
    //Wir sind nur eine Liste, d.h. alle gültigen Indices haben den Default-Index als Elter.
    return {};
}

/**
 * @brief Liefert die Anzahl der Zeilen unter einem Index.
 * @author Björn Schäpers
 * @param[in] parent Der Index nach dessen Unterzeilen gefragt wird.
 * @return Die Anzahl der Zeilen.
 */
int PersonModel::rowCount(const QModelIndex& parent) const noexcept {
    return parent.isValid() ? 0 : static_cast<int>(Data.size());
}

/**
 * @brief Liefert die Anzahl der Spalten unter einem Index.
 * @author Björn Schäpers
 * @param[in] parent Der Index nach dessen Unterspalten gefragt wird.
 * @return Die Anzahl der Spalten.
 */
int PersonModel::columnCount(const QModelIndex& /*parent*/) const noexcept {
    return static_cast<int>(Column::Count);
}

/**
 * @brief Setzt die Daten.
 * @author Björn Schäpers
 * @param[in] index Der Index des zu ändernden Eintrags.
 * @param[in] value Der neue Wert.
 * @param[in] role Die Rolle die bearbeitet wird.
 * @return Ob das Editieren erfolgt ist.
 */
bool PersonModel::setData(const QModelIndex& index, const QVariant& value, int role) noexcept {
    return false;
}

/**
 * @brief Liefert die Daten.
 * @author Björn Schäpers
 * @param[in] index Der Index des gefragten Eintrags.
 * @param[in] role Die gefragte Rolle.
 * @return Der Wert.
 */
QVariant PersonModel::data(const QModelIndex& index, int role) const noexcept {
    return {};
}

/**
 * @brief Liefert die Flags zu einem Index.
 * @author Björn Schäpers
 * @param[in] index Der Index.
 * @return Die Flags dazu.
 */
Qt::ItemFlags PersonModel::flags(const QModelIndex& index) const noexcept {
    const auto baseFlags = QAbstractItemModel::flags(index);

    if ( !index.isValid() ) {
        return baseFlags;
    } //if ( !index.isValid() )

    auto flags = baseFlags | Qt::ItemFlag::ItemNeverHasChildren;

    if ( index.column() == static_cast<int>(Column::Vip) ) {
        flags |= Qt::ItemFlag::ItemIsEditable;
    } //if ( index.column() == static_cast<int>(Column::Vip) )

    return flags;
}

#include "moc_person_model.cpp"
