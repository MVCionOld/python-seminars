#!/bin/bash

docker run --pull missing --name mipt-diht-python-2021-seminars -it -p 8888:8888 -v `pwd`:/home/jovyan/work jupyter/datascience-notebook jupyter notebook
