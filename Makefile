all: compile link

compile:
	g++ -Isfml/include -c main.cpp activfunction.cpp bird.cpp birdgroup.cpp hitbox.cpp nlayer.cpp nnet.cpp pipe.cpp -DSFML_STATIC -static -static-libgcc -static-libstdc++ -g

link:
	g++ main.o activfunction.o bird.o birdgroup.o hitbox.o nlayer.o nnet.o pipe.o -o main -Lsfml/lib -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lopengl32 -lfreetype -lwinmm -lgdi32 -static -static-libgcc -static-libstdc++ -g

run:
	.\main.exe