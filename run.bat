@echo off
title Run

make WindowsAll
java -cp .\target\QuimbertQuarrel-1.0-SNAPSHOT.jar;.\lib\jaylib-5.0.0-0.jar com.quimbertco.QuimbertQuarrel.QuimbertQuarrel
pause