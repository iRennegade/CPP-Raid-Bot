@ECHO OFF
g++ ../src/main.cpp -o ../dist/bot.exe -ldpp -lssl3 -lpthread
echo Compiled, now run run.bat