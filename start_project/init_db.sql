-- 1. מחיקת הטבלה אם היא כבר קיימת (מונע שגיאות של "טבלה כבר קיימת")
DROP TABLE IF EXISTS users CASCADE;

-- 2. יצירת הטבלה מחדש עם שדות בסיסיים
CREATE TABLE users (
    id SERIAL PRIMARY KEY,            -- מספר סידורי רץ אוטומטי
    username VARCHAR(50) UNIQUE NOT NULL, -- שם משתמש ייחודי
    email VARCHAR(100) NOT NULL,       -- אימייל
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP -- תאריך יצירה אוטומטי
);

-- 3. אופציונלי: הכנסת קצת נתונים ראשוניים (Data Seeding) בשביל הבדיקות
INSERT INTO users (username, email) VALUES 
('ayal_admin', 'ayal@example.com'),
('test_user', 'user@example.com');
