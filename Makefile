# KOSTA
# IF YOU SEE THIS, IGNORE THIS FILE PLEASE
# PLEASE DON'T EVER TOUCH THIS, THIS IS MY VERSION OF run.bat AND c.bat

LinuxAll:
	mvn clean dependency:copy-dependencies package


LinuxRun:
	make LinuxAll
	java -cp ./target/QuimbertQuarrel-1.0-SNAPSHOT.jar:./lib/jaylib-5.0.0-0.jar com.quimbertco.QuimbertQuarrel.QuimbertQuarrel


WindowsAll:
	mvn clean dependency:copy-dependencies package

WindowsRun:
	make WindowsAll
	java -cp .\target\QuimbertQuarrel-1.0-SNAPSHOT.jar;.\lib\jaylib-5.0.0-0.jar com.quimbertco.QuimbertQuarrel.QuimbertQuarrel

