#include <drogon/drogon.h>
#include <string>

class UsersController : public drogon::HttpController<UsersController> {
public:
    METHOD_LIST_BEGIN
    ADD_METHOD_TO(UsersController::getUsersPage, "/users", drogon::Get);
    METHOD_LIST_END

    void getUsersPage(const drogon::HttpRequestPtr& req, std::function<void (const drogon::HttpResponsePtr&)>&& callback) {
        auto dbClient = drogon::app().getDbClient();

        dbClient->execSqlAsync(
            "SELECT id, username, email FROM users ORDER BY id ASC;",
            [callback = std::move(callback)](const drogon::orm::Result& result) {
                
                std::string html = R"(
                    <!DOCTYPE html>
                    <html>
                    <head>
                        <meta charset="UTF-8">
                        <title>Users List</title>
                        <style>
                            body { font-family: Arial, sans-serif; background-color: #f4f7f6; margin: 40px; color: #333; display: flex; flex-direction: column; align-items: center; }
                            .wrapper { width: 100%; max-width: 800px; background: white; padding: 30px; border-radius: 12px; box-shadow: 0 4px 20px rgba(0, 0, 0, 0.08); }
                            h1 { color: #1e3c72; border-bottom: 2px solid #eef2f5; padding-bottom: 15px; }
                            table { width: 100%; border-collapse: collapse; margin-bottom: 30px; }
                            th, td { padding: 14px 18px; text-align: left; border-bottom: 1px solid #eef2f5; }
                            th { background-color: #2a5298; color: white; }
                            tr:hover { background-color: #f8fafc; }
                            .badge { background: #e0f2fe; color: #0369a1; padding: 4px 8px; border-radius: 6px; font-weight: bold; }
                            .back-btn { display: inline-block; color: #2a5298; text-decoration: none; font-weight: bold; }
                        </style>
                    </head>
                    <body>
                        <div class="wrapper">
                            <h1>👥 Ayal's Database Content</h1>
                            <p>Pulled live from PostgreSQL using a dedicated Controller file!</p>
                            <table>
                                <tr>
                                    <th>ID</th>
                                    <th>Username</th>
                                    <th>Email</th>
                                </tr>
                )";

                for (const auto& row : result) {
                    html += "<tr>";
                    html += "<td><span class='badge'>" + std::to_string(row["id"].as<int>()) + "</span></td>";
                    html += "<td><strong>" + row["username"].as<std::string>() + "</strong></td>";
                    html += "<td>" + row["email"].as<std::string>() + "</td>";
                    html += "</tr>";
                }

                html += R"(
                            </table>
                            <a class="back-btn" href="/">⬅️ Back to Main Page</a>
                        </div>
                    </body>
                    </html>
                )";

                // תיקון 1: יצירת תגובה עם קוד סטטוס 200 (OK) וסוג תוכן HTML
                auto resp = drogon::HttpResponse::newHttpResponse(drogon::k200OK, drogon::CT_TEXT_HTML);
                resp->setBody(html);
                callback(resp);
            },
            [callback](const drogon::orm::DrogonDbException& e) {
                // תיקון 2: פה הייתה השגיאה השנייה שקפצה לך! יצירת תגובת שגיאה 500 בצורה תקינה
                auto resp = drogon::HttpResponse::newHttpResponse(drogon::k500InternalServerError, drogon::CT_TEXT_HTML);
                resp->setBody("<h2>Database Error: " + std::string(e.base().what()) + "</h2>");
                callback(resp);
            }
        );
    }
};

//REGISTER_COMPONENT(UsersController);
