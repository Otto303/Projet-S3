CFLAGS = -Wall -Wextra -O3 #-fsanitize=address

TARGETS = solver network

all: $(TARGETS)
LIBS = -lSDL2 -lSDL2_image -lSDL2_ttf

solver : .cache/Solver/*.c .cache/Solver/*.h .cache/MyLib/*.c .cache/MyLib/*.h
	gcc $(CFLAGS) -o solver .cache/Solver/*.c .cache/Solver/*.h .cache/MyLib/*.c .cache/MyLib/*.h

network : .cache/NeuronNetwork/*.c .cache/NeuronNetwork/*.h .cache/NeuronNetwork/Network/*.c .cache/NeuronNetwork/Network/*.h .cache/NeuronNetwork/Dataset/*.c .cache/NeuronNetwork/Dataset/*.h
	gcc $(CFLAGS) -o network_training .cache/NeuronNetwork/training.c .cache/NeuronNetwork/Network/*.c .cache/NeuronNetwork/Network/*.h .cache/NeuronNetwork/Dataset/*.c .cache/NeuronNetwork/Dataset/*.h -lm
	gcc $(CFLAGS) -o network_resolve .cache/NeuronNetwork/resolve.c .cache/NeuronNetwork/bmp_to_array.h .cache/NeuronNetwork/bmp_to_array.c .cache/NeuronNetwork/Network/*.c .cache/NeuronNetwork/Network/*.h .cache/NeuronNetwork/Dataset/*.c .cache/NeuronNetwork/Dataset/*.h -lm -lSDL2

