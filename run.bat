@echo off
title Run

"E:\Actually Useful\NonZips\java\jdk-21.0.4+7\bin\javac.exe" -cp .\jaylib-5.0.0-0.jar .\QuimbertQuarrel.java .\Quimbert.java
"E:\Actually Useful\NonZips\java\jdk-21.0.4+7\bin\java.exe" -cp jaylib-5.0.0-0.jar;. QuimbertQuarrel
pause