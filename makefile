build:
	g++.exe -w -std=c++14 -Wfatal-errors \
	./src/*.cc \
	-o game.exe \
	-I"./include" \
	-L"./lib" \
	-llua53 \
	-lmingw32 \
	-lSDL2main \
	-lSDL2 \
	-lSDL2_image \
	-lSDL2_ttf \
	-lSDL2_mixer

clean:
	rm ./game.exe

run:
	chmod 777 game.exe; ./game.exe
