CFLAGS = -Wall -Wextra

TARGETS = solver network rotation interface image_save grid_build

all: $(TARGETS)
LIBS = -lSDL2 -lSDL2_image -lSDL2_ttf

solver : .cache/Solver/*.c .cache/Solver/*.h .cache/MyLib/*.c .cache/MyLib/*.h
	gcc $(CFLAGS) -o solver .cache/Solver/*.c .cache/Solver/*.h .cache/MyLib/*.c .cache/MyLib/*.h

network : .cache/NeuronNetwork/*.c .cache/NeuronNetwork/*.h .cache/NeuronNetwork/Network/*.c .cache/NeuronNetwork/Network/*.h .cache/NeuronNetwork/Dataset/*.c .cache/NeuronNetwork/Dataset/*.h
	gcc $(CFLAGS) -o network_training .cache/NeuronNetwork/training.c .cache/NeuronNetwork/Network/*.c .cache/NeuronNetwork/Network/*.h .cache/NeuronNetwork/Dataset/*.c .cache/NeuronNetwork/Dataset/*.h -lm
	gcc $(CFLAGS) -o network_resolve .cache/NeuronNetwork/resolve.c .cache/NeuronNetwork/predict.h .cache/NeuronNetwork/predict.c .cache/NeuronNetwork/bmp_to_array.h .cache/NeuronNetwork/bmp_to_array.c .cache/NeuronNetwork/Network/*.c .cache/NeuronNetwork/Network/*.h .cache/NeuronNetwork/Dataset/*.c .cache/NeuronNetwork/Dataset/*.h -lm -lSDL2

rotation : .cache/Rotation/*.c
	gcc $(CFLAGS) -o rotation .cache/Rotation/*.c -lSDL2

image_save : .cache/image_save/*.c
	gcc $(CFLAGS) -o image_save1 .cache/image_save/programme.c $(LIBS)
	gcc $(CFLAGS) -o image_save1 .cache/image_save/programme2.c $(LIBS)

grid_build: .cache/grid_build/*.c
	gcc $(CFLAGS) -o final_grid .cache/grid_build/final_grid.c $(LIBS)
	gcc $(CFLAGS) -o grid_from_coordonates .cache/grid_build/grid_from_coordinates.c $(LIBS)

interface : .cache/Interface/*.c .cache/Interface/*.h
	gcc $(CFLAGS) -o interface .cache/Interface/*.c .cache/Interface/*.h  $(LIBS)
