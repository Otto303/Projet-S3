CFLAGS = -Wall -Wextra

TARGETS = solver network interface sauvegarde_image1 sauvegarde_image2

all: $(TARGETS)
LIBS = -lSDL2 -lSDL2_image -lSDL2_ttf

solver : .cache/Solver/*.c .cache/Solver/*.h .cache/MyLib/*.c .cache/MyLib/*.h
	gcc $(CFLAGS) -o solver .cache/Solver/*.c .cache/Solver/*.h .cache/MyLib/*.c .cache/MyLib/*.h

network : .cache/NeuronNetwork/*.c .cache/NeuronNetwork/*.h
	gcc $(CFLAGS) -o network .cache/NeuronNetwork/*.c .cache/NeuronNetwork/*.h -lm

interface : .cache/Interface/*.c .cache/Interface/*.h
	gcc $(CFLAGS) -o interface .cache/Interface/*.c .cache/Interface/*.h  $(LIBS)

sauvegarde_image1 : .cache/sauvegarde_image/*.c
	gcc $(CFLAGS) -o sauvegarde_image1 .cache/sauvegarde_image/*.c

sauvegarde_image2 : .cache/sauvegarde_image2/*.c
	gcc $(CFLAGS) -o sauvegarde_image2 .cache/sauvegarde_image2/*.c $(LIBS)
