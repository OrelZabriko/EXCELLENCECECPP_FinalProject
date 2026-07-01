#pragma once
#include "./../Repository/DB_Repository.h"
#include <string_view>

// Database schema constants to avoid hardcoded strings
constexpr std::string_view TABLE_USERS = "users";

constexpr std::string_view COL_USERS_ID = "id";
constexpr std::string_view COL_USERS_USERNAME = "username";
constexpr std::string_view COL_USERS_EMAIL = "email";
constexpr std::string_view COL_USERS_ROLE_ID = "role_id";
constexpr std::string_view COL_USERS_CREATED_AT = "created_at";

// Wildcard constant for selecting all columns
constexpr std::string_view WILDCARD_ALL = "*";

constexpr int DEFAULT_ROLE_ID = 1;
class UserRepository {
public:
    UserRepository() = default;

    void getAllUsers(DbSelectCallback&& success, DbErrorCallback&& error);
    
    // Version 2: Fetches all columns using the wildcard (*) operator
    void getAllUsersWildcard(DbSelectCallback&& success, DbErrorCallback&& error);

    void insertUser(
        const std::string& username,
        const std::string& email,
        DbUpdateCallback&& success,
        DbErrorCallback&& error
    );
};
