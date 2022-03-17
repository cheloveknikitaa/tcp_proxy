#pragma once

#include <mysql.h> // Заголовочный файл с описание функций
#include <stdio.h>
#include <conio.h>

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

Class Client {
private:
    Client();
    int const _UserFd;
    int _DbFd;
public:
    Client(int const UserFd);
    ~Client();
    void response(const char *query);
};

Client::Client(int const UserFd): _UserFd(UserFd) {

}

void response(const char *query)
{
    MYSQL mysql; // Дескриптор соединения
    MYSQL_ROW row; // Массив полей текущей строки
    MYSQL_RES *res; // Дескриптор результирующей таблицы

    char host[] = "localhost"; // хост
    char user[] = "admin"; // пользователь
    char passwd[] = "admin"; // пароль
    char db[] = "library"; // название базы данных
    int port = 0; //  порт. Если порт у сервера MySQL не по умолчанию (3306), то нужно указывать конкретный номер порта

    mysql_init(&mysql);  // Инициализация
    mysql_real_connect(&mysql, host, user, passwd, db, port, NULL, 0); // соединение

    if (mysql_query(&mysql, query) > 0) // запорс. Если ошибок нет, то продолжаем работу
    {

        // Если была ошибка, ...
        printf("%s", mysql_error(&mysql));  // ... вывдем ее
        return; // и завершим работу
    }

    res = mysql_store_result(&mysql); // Берем результат,
    int num_fields = mysql_num_fields(res); // количество полей
    int num_rows = mysql_num_rows(res); // и количество строк.

    for (int i = 0; i < num_fields; i++) // Выводим названия полей
    {
        field = mysql_fetch_field_direct(res, i); // Получение названия текущего поля
        printf("| %s |", field->name);
    }

    printf("\n");

    for (int i = 0; i < num_rows; i++) // Вывод таблицы
    {
        row = mysql_fetch_row(res); // получаем строку

        for (int l = 0; l < num_fields; l++)
            printf("| %s |", row[l]); // Выводим поля

        printf("\n");
    }

    printf("Count records = %d", num_rows); // Вывод информации о количестве записей
    mysql_free_result(res); // Очищаем результаты
    mysql_close(&mysql); // Закрываем соединение
}
