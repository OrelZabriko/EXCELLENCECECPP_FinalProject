#include "UserQueries.h"
#include <string>

void UserRepository::getAllUsers(DbSelectCallback&& success, DbErrorCallback&& error) {
    // Constructing the columns string using the pre-defined constants
    std::string columns = std::string(COL_USERS_ID) + ", " + 
                          std::string(COL_USERS_USERNAME) + ", " + 
                          std::string(COL_USERS_EMAIL) + ", " + 
                          std::string(COL_USERS_CREATED_AT);

    // Running the query using the constants
    DB_Repository::getInstance().runSelectQuery(
        std::string(TABLE_USERS), 
        std::move(success), 
        std::move(error), 
        columns, 
        ""
    );
}

// Version 2: Utilizing the Wildcard (*) operator
void UserRepository::getAllUsersWildcard(DbSelectCallback&& success, DbErrorCallback&& error) {
    // Running the query passing the wildcard constant as the columns parameter
    DB_Repository::getInstance().runSelectQuery(
        std::string(TABLE_USERS), 
        std::move(success), 
        std::move(error), 
        std::string(WILDCARD_ALL), 
        ""
    );
}

void UserRepository::insertUser(
    const std::string& username,
    const std::string& email,
    DbUpdateCallback&& success,
    DbErrorCallback&& error
) {
    // Building the INSERT statement purely from schemas and type-safe constants
    std::string sqlQuery = "INSERT INTO " + std::string(TABLE_USERS) + " (" +
                           std::string(COL_USERS_USERNAME) + ", " +
                           std::string(COL_USERS_EMAIL) + ", " +
                           std::string(COL_USERS_ROLE_ID) + ") VALUES (" +
                           "'" + username + "', " +
                           "'" + email + "', " + 
                           std::to_string(DEFAULT_ROLE_ID) + ")";

    // Executing via the singleton repository instance
    DB_Repository::getInstance().run_update_query(
        sqlQuery,
        std::move(success),
        std::move(error)
    );
}
