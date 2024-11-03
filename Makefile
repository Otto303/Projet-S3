CFLAGS = -Wall -Wextra

TARGETS = solver network

all: $(TARGETS)

solver : .cache/Solver/*.c .cache/Solver/*.h .cache/MyLib/*.c .cache/MyLib/*.h
	gcc $(CFLAGS) -o solver .cache/Solver/*.c .cache/Solver/*.h .cache/MyLib/*.c .cache/MyLib/*.h

network : .cache/NeuronNetwork/*.c .cache/NeuronNetwork/*.h
	gcc $(CFLAGS) -o network .cache/NeuronNetwork/*.c .cache/NeuronNetwork/*.h -lm

sauvegarde_image : .cache/sauvegarde_image/*.c .cache/sauvegarde_image/*.h
	gcc $(CFLAGS) -o sauvegarde_image .cache/sauvegarde_image/*.c .cache/sauvegarde_image/*.h
