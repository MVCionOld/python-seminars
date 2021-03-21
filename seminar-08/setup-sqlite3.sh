#!/bin/bash

docker run \
    --pull missing \
    --name mipt-diht-python-2021-sqlite3 \
    -it -v `pwd`:/home/jovyan/work/seminar-08/sqlite3 \
    keinos/sqlite3 \
    sqlite3
