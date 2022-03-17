#include <stdlib.h>
#include <iostream>
// #include <vector>
#include </usr/include/mysql/mysql.h>

using namespace std;

int main(void)
{
    // std::vector<std::string> tables;
    MYSQL_RES *result;
    MYSQL_ROW row;
    MYSQL *connection, mysql;

    int state;

    mysql_init(&mysql);

    connection = mysql_real_connect(&mysql,"127.0.0.1","root","root","world",0,0,0);

    // cout << connection;
    if (connection == NULL)
    {
        std::cout << mysql_error(&mysql) << std::endl;
        return -1;
        // return tables;
    }

    state = mysql_query(connection, "SHOW DATABASES\n");
    if (state !=0)
    {
        std::cout << mysql_error(connection) << std::endl;
    }

    result = mysql_store_result(connection);

    std::cout << "tables: " << mysql_num_rows(result) << std::endl;
    while ( ( row=mysql_fetch_row(result)) != NULL )
    {
        cout << row[0] << std::endl;
    }

    mysql_free_result(result);
    mysql_close(connection);
}


// void response(const char *query)
// {
//     MYSQL mysql; // Дескриптор соединения
//     MYSQL_ROW row; // Массив полей текущей строки
//     MYSQL_RES *res; // Дескриптор результирующей таблицы

//     char host[] = "localhost"; // хост
//     char user[] = "admin"; // пользователь
//     char passwd[] = "admin"; // пароль
//     char db[] = "library"; // название базы данных
//     int port = 0; //  порт. Если порт у сервера MySQL не по умолчанию (3306), то нужно указывать конкретный номер порта

//     mysql_init(&mysql);  // Инициализация
//     mysql_real_connect(&mysql, host, user, passwd, db, port, NULL, 0); // соединение

//     if (mysql_query(&mysql, query) > 0) // запорс. Если ошибок нет, то продолжаем работу
//     {

//         // Если была ошибка, ...
//         printf("%s", mysql_error(&mysql));  // ... вывдем ее
//         return; // и завершим работу
//     }

//     res = mysql_store_result(&mysql); // Берем результат,
//     int num_fields = mysql_num_fields(res); // количество полей
//     int num_rows = mysql_num_rows(res); // и количество строк.

//     for (int i = 0; i < num_fields; i++) // Выводим названия полей
//     {
//         field = mysql_fetch_field_direct(res, i); // Получение названия текущего поля
//         printf("| %s |", field->name);
//     }

//     printf("\n");

//     for (int i = 0; i < num_rows; i++) // Вывод таблицы
//     {
//         row = mysql_fetch_row(res); // получаем строку

//         for (int l = 0; l < num_fields; l++)
//             printf("| %s |", row[l]); // Выводим поля

//         printf("\n");
//     }

//     printf("Count records = %d", num_rows); // Вывод информации о количестве записей
//     mysql_free_result(res); // Очищаем результаты
//     mysql_close(&mysql); // Закрываем соединение
// }