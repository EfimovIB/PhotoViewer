#include "users_dict.h"


std::vector<std::shared_ptr<User> > UsersDict::toVector() const
{
    std::vector<std::shared_ptr<User>> users;
    users.reserve(dict.size());

    std::transform (dict.begin(), dict.end(), back_inserter(users),
        [] (const std::pair<user_id, std::shared_ptr<User>>& pair)
        {
            return pair.second;
        });

    return users;
}
