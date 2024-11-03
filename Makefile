CFLAGS = -Wall -Wextra

TARGETS = solver network interface image_save1 image_save2

all: $(TARGETS)
LIBS = -lSDL2 -lSDL2_image -lSDL2_ttf

solver : .cache/Solver/*.c .cache/Solver/*.h .cache/MyLib/*.c .cache/MyLib/*.h
	gcc $(CFLAGS) -o solver .cache/Solver/*.c .cache/Solver/*.h .cache/MyLib/*.c .cache/MyLib/*.h

network : .cache/NeuronNetwork/*.c .cache/NeuronNetwork/*.h
	gcc $(CFLAGS) -o network .cache/NeuronNetwork/*.c .cache/NeuronNetwork/*.h -lm

interface : .cache/Interface/*.c .cache/Interface/*.h
	gcc $(CFLAGS) -o interface .cache/Interface/*.c .cache/Interface/*.h  $(LIBS)

image_save1: .cache/image_save/*.c
	gcc $(CFLAGS) -o image_save .cache/image_save/*.c

image_save2: .cache/image_save_second/*.c
	gcc $(CFLAGS) -o  image_save2 .cache/image_save_second/*.c $(LIBS)
