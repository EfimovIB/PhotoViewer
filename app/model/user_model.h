#pragma once

#include <QAbstractListModel>

class DataSource;
struct User;

class UserModel
  : public QAbstractListModel
{
    Q_OBJECT

public:

    UserModel(DataSource* dataSource, QObject* parent = nullptr);

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

    Q_INVOKABLE int userIdRole() const { return U_Id; }

    QHash<int, QByteArray> roleNames() const override
    {
        return {
            {U_Id, "id"}
          , {U_UserName, "userName"}
        };
    }

private:

    enum UserModelRoles
    {
        U_Id = Qt::UserRole + 1
      , U_UserName
    };

    void resetModel();

    DataSource* m_dataSource;
    std::vector<std::shared_ptr<User>> m_users;
};
