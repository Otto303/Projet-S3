CFLAGS = -Wall -Wextra

TARGETS = solver network

all: $(TARGETS)

solver : .cache/Solver/*.c .cache/Solver/*.h .cache/MyLib/*.c .cache/MyLib/*.h
	gcc $(CFLAGS) -o solver .cache/Solver/*.c .cache/Solver/*.h .cache/MyLib/*.c .cache/MyLib/*.h

network : .cache/NeuronNetwork/*.c .cache/NeuronNetwork/*.h .cache/MyLib/*.c .cache/MyLib/*.h
	gcc $(CFLAGS) -o network .cache/NeuronNetwork/*.c .cache/NeuronNetwork/*.h -lm
