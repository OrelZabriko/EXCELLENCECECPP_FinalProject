#include "UserQueries.h"

void UserRepository::getAllUsers(DbSelectCallback&& success, DbErrorCallback&& error) {
    DB_Repository::getInstance().runSelectQuery("users", std::move(success), std::move(error), "id, username, email, created_at", "");
}

void UserRepository::insertUser(
    const std::string& username,
    const std::string& email,
    DbUpdateCallback&& success,
    DbErrorCallback&& error
) {
    // בניית שאילתת INSERT
    std::string sqlQuery = "INSERT INTO users (username, email, role_id ) VALUES ("
                           "'" + username + "', "
                           "'" + email + "',1)";

    // הרצה מול הסינגלטון
    DB_Repository::getInstance().run_update_query(
        sqlQuery,
        std::move(success),
        std::move(error)
    );
}

