#!/bin/bash

docker run --pull missing --name mipt-atp-python-seminars -it -p 8888:8888 -v `pwd`:/home/jovyan/work jupyter/datascience-notebook jupyter notebook
