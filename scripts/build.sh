#!/bin/bash
echo LINUX BOT BUILDER
g++ ../src/main.cpp -o ../dist/bot -ldpp -lssl3 -lpthread
echo Done, now run ./bot