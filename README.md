# Database-D

This project is an implementation of simple database from scratch. It uses [B-tree](https://en.wikipedia.org/wiki/B-tree) to store tables and [Deques](https://en.wikipedia.org/wiki/Double-ended_queue) to store the data in each table. Database-D has been created as an educational project (database for processing the data about students of some school or university) and not intended for production, at least in current state.

## Requirements
* C++ compiler (e.g. gcc or clang)
* Python 3 (for tests)

## Install

```sh
git clone https://github.com/DavidOSX/Database-D
chmod +x install.sh
./install.sh
```

## Using
After you install this database to run it just type:
```sh
./database-d
```

Nowadays you can use these commands:

* 'add' -   add student's name and group number
* 'search' - search for a student by the name and the group number
* 'search_by_num' -  search for a students by the group number
* 'del' -  removal of information about the certain student
* 'del_by_num' - removal of information about the certain group
* 'q' -   quit 
* 'test' - test the database with the data about 10000 students (you can change size of test dataset if run following command ```python3 test.py```)

Note: group-students tables can be easily correct for arbitrary use