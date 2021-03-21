#!/bin/bash

POSTGRES_DB=testdb
POSTGRES_PASSWORD=testuser
POSTGRES_USER=testuser

docker run \
    --pull missing \
    --name mipt-diht-python-2021-postgres \
    -it -p 5432:5432 \
    -v `pwd`:/home/jovyan/work/seminar-08/postgres \
    -e POSTGRES_DB=$POSTGRES_DB \
    -e POSTGRES_PASSWORD=$POSTGRES_PASSWORD \
    -e POSTGRES_USER=$POSTGRES_USER \
    -d postgres:latest
