run:
	g++ main.cpp -std=c++17 -Wall -Wextra -o main.exe & main.exe

input:
	g++ main.cpp -std=c++17 -Wall -Wextra -o main.exe & main.exe < input.in

generate:
	copy template.cpp main.cpp

clean:
	del main.exe main.cpp