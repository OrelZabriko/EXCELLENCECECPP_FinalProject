#include "UserWithRolesController.h"

// הכלת השירות
#include "./../services/UserService.h" 

void UserWithRolesController::getUsersWithRoles(
    const drogon::HttpRequestPtr& req,
    std::function<void(const drogon::HttpResponsePtr&)>&& callback
) {
    UserService userService;

    // 🔥 התיקון: הלמדא כעת מקבלת וקטור של UserWithRoleDTO במקום המודל הישן
    userService.getUsersWithRolesList([callback](bool success, const std::vector<UserWithRoleDTO>& users, const std::string& errorMsg) {
        
        auto resp = drogon::HttpResponse::newHttpResponse();

        if (!success) {
            resp->setStatusCode(drogon::k500InternalServerError);
            resp->setBody("Database Error via Service: " + errorMsg);
            callback(resp);
            return;
        }

        std::string html = "<!DOCTYPE html><html lang='en'><head><meta charset='UTF-8'><title>Clean Architecture</title>";
        html += "<style>body { font-family: Arial, sans-serif; margin: 40px; background-color: #f4f7f6; }";
        html += "table { width: 100%; border-collapse: collapse; margin-top: 20px; background: white; }";
        html += "th, td { border: 1px solid #ddd; padding: 12px; text-align: left; }";
        html += "th { background-color: #2a5298; color: white; }</style></head><body>";

        html += "<h1>Users & Roles (Fetched via UserService Layer)</h1>";
        html += "<table><thead><tr><th>ID</th><th>Username</th><th>Email</th><th>Role Name</th></tr></thead><tbody>";
        
        // 🔥 הלולאה כעת רצה על ה-DTOs בצורה מהירה וללא פניות נוספות ל-DB
        for (const auto& user : users) {
            html += "<tr>";
            html += "<td>" + std::to_string(user.id) + "</td>";
            html += "<td>" + user.username + "</td>";
            html += "<td>" + user.email + "</td>";
            html += "<td>" + user.roleName + "</td>"; // שם התפקיד מגיע מוכן ומעובד!
            html += "</tr>";
        }
        
        html += "</tbody></table></body></html>";

        resp->setStatusCode(drogon::k200OK);
        resp->setContentTypeCode(drogon::CT_TEXT_HTML);
        resp->setBody(html);
        callback(resp);
    });
}

void UserWithRolesController::addUserWithORM(
    const drogon::HttpRequestPtr& req,
    std::function<void(const drogon::HttpResponsePtr&)>&& callback
) {
    auto resp = drogon::HttpResponse::newHttpResponse();
    resp->setStatusCode(drogon::k303SeeOther);
    resp->addHeader("Location", "/users_roles");
    callback(resp);
}
