all: run

run: initest
	./initest

initest:
	gcc -o initest ini.c initest.c

clean:
	rm -f initest
