# ex3
Interpreter for flight gear simulator:
  this program interpret a text to a code that run the flight gear simulator
  the commands to fly the airplane is in the "fly.txt" and "fly_with_func.txt" file
  this program do support functions, so you can run it with fly_with_func file.
  you can compile this program with the command -
  "g++ -std=c++11 *.cpp -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic -o a.out -pthread"
  and run it with the command "./a.out file_name" when file_name is the name of the text file you
  want to interpret, for example fly_with_func.txt.
  you should reside the text files along side the main.cpp file (and all the others)
  you should also reside the "generic_small.xml" file in the protocol folder under data of 
  the simulator code (wherever you downloaded it to).
  please make sure that you open the program before enter the simulator to enable right connection flow.
  enjoy!
