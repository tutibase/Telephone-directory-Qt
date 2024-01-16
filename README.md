# Telephone-directory-Qt
С полным описанием программы можно ознакомиться в [отчете о выполненной работе](https://github.com/tutibase/Telephone-directory-Qt/blob/main/report.pdf).

## Краткое описание программы
Приложение телефонный справочник:
- Все вводимые данные проверяются на корректность при помощи регулярных выражений
- Добавление, удаление записей
- Редактирование всех полей
- Сортировка записей по столбцам
- Поиск по всем записям в справочнике
- Хранение данных в файле

## Примеры работы программы:
При считывании данных из файла приложение откроет последнюю сохраненную версию справочника:
| ![image](https://github.com/tutibase/Telephone-directory-Qt/assets/44751053/15683b81-fd10-470d-8c0a-8cc5fa3e3b84) | 
|:--:| 
| *Внешний вид справочника* |

По нажатию на название столбца происходит сортировка по нему. При нажатии на кнопку ```Search``` будет выполнен поиск всех подходящих записей: 
| ![image](https://github.com/tutibase/Telephone-directory-Qt/assets/44751053/c2994d89-6640-4b68-b5a1-30d75e31623c) | 
|:--:| 
| *Сортировка по убыванию даты рождения и поиск слова "address"* |

По нажатию кнопки ```Delete Rows``` все выделенные колонки будут удалены:
| ![image](https://github.com/tutibase/Telephone-directory-Qt/assets/44751053/8b675510-13e8-4426-bf95-ebfe55c7614a) | 
|:--:| 
| *Справочник после удаления строк* |
