CFLAGS = -Wall -Wextra

TARGETS = solver network sauvegarde_image interface

all: $(TARGETS)

solver : .cache/Solver/*.c .cache/Solver/*.h .cache/MyLib/*.c .cache/MyLib/*.h
	gcc $(CFLAGS) -o solver .cache/Solver/*.c .cache/Solver/*.h .cache/MyLib/*.c .cache/MyLib/*.h

network : .cache/NeuronNetwork/*.c .cache/NeuronNetwork/*.h
	gcc $(CFLAGS) -o network .cache/NeuronNetwork/*.c .cache/NeuronNetwork/*.h -lm

sauvegarde_image : .cache/sauvegarde_image/*.c
	gcc $(CFLAGS) -o sauvegarde_image .cache/sauvegarde_image/*.c

interface : .cache/Interface/*.c .cache/Interface/*.h
	gcc $(CFLAGS) -o interface .cache/Interface/*.c .cache/Interface/*.h -lSDL2_image -lSDL2_ttf
