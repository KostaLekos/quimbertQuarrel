@echo off
title Run

"H:\Registries\java\bin\javac.exe" -cp .\jaylib-5.0.0-0.jar .\QuimbertQuarrel.java .\Quimbert.java .\QuimbertTextBox.java
"H:\Registries\java\bin\java.exe" -cp jaylib-5.0.0-0.jar;. QuimbertQuarrel
pause