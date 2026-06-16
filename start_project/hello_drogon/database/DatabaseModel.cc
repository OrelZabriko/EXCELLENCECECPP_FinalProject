#include <functional>
#include <string>
#include "DatabaseModel.h"

// מימוש ה-SELECT הגנרי
void DatabaseModel::executeSelect(
    const std::string& sqlQuery,
    std::function<void(const drogon::orm::Result&)>&& successCallback,
    std::function<void(const std::string&)>&& errorCallback
) {
    auto dbClient = drogon::app().getDbClient();
    
    dbClient->execSqlAsync(
        sqlQuery,
        [successCallback = std::move(successCallback)](const drogon::orm::Result& result) {
            successCallback(result); 
        },
        [errorCallback = std::move(errorCallback)](const drogon::orm::DrogonDbException& e) {
            errorCallback(e.base().what()); 
        }
    );
}

// מימוש ה-UPDATE / INSERT / DELETE הגנרי
void DatabaseModel::executeUpdate(
    const std::string& sqlQuery,
    std::function<void(size_t)>&& successCallback,
    std::function<void(const std::string&)>&& errorCallback
) {
    auto dbClient = drogon::app().getDbClient();

    dbClient->execSqlAsync(
        sqlQuery,
        [successCallback = std::move(successCallback)](const drogon::orm::Result& result) {
            successCallback(result.affectedRows()); 
        },
        [errorCallback = std::move(errorCallback)](const drogon::orm::DrogonDbException& e) {
            errorCallback(e.base().what());
        }
    );
}
