othello:
	cls
	gcc src/GameWindow.c -o bin/Othello -I include -L lib   -lSDL2 -lSDL2main -lSDL2_ttf -lSDL2_mixer -mwindows
	./bin/Othello
