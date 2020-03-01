#include "user_model.h"

#include <QDebug>

#include "data_source/data_source.h"
#include "base/user.h"

UserModel::UserModel(DataSource* dataSource, QObject* parent)
  : QAbstractListModel(parent)
  , m_dataSource(dataSource)
  , m_users(m_dataSource->users())
{
    connect(m_dataSource, &DataSource::dataUpdated, this, &UserModel::resetModel);
}

int UserModel::rowCount(const QModelIndex&) const
{
    return static_cast<int>(m_users.size());
}

QVariant UserModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid())
        return {};

    const std::shared_ptr<User>& user = m_users[static_cast<size_t>(index.row())];

    switch (role)
    {
    case U_Id: return static_cast<int>(user->id);
    case U_UserName: return user->userName;
    }

    return {};
}

void UserModel::resetModel()
{
    beginResetModel();
    m_users = m_dataSource->users();
    endResetModel();
}
