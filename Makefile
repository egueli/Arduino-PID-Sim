test: arduinopidsim.txt
	

arduinopidsim.txt: pidsim
	./pidsim > arduinopidsim.txt

pidsim: *.h *.cpp
	g++ -g -std=c++11 -Wall -o pidsim -DARDUINO=170 -I. -I../Arduino-PID-Library ../Arduino-PID-Library/PID_v1.cpp pid-tester.cpp Arduino.cpp
	