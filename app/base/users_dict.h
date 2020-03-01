#pragma once

#include "types.h"
#include "user.h"

#include <map>
#include <memory>
#include <vector>

struct UsersDict
{
    std::vector<std::shared_ptr<User>> toVector() const;

    std::map<user_id, std::shared_ptr<User>> dict;
};

