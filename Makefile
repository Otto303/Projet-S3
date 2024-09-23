solver : .cache/Solver/*.c .cache/Solver/*.h .cache/MyLib/*.c .cache/MyLib/*.h
	gcc -o solver -Wall -Wextra .cache/Solver/*.c .cache/Solver/*.h .cache/MyLib/*.c .cache/MyLib/*.h
