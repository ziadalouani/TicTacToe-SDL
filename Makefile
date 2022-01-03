prog: main.c
	 gcc  main.c  -o prog $(shell sdl2-config --cflags --libs)

clean:
	rm -rf *.o
mrproper: clean
	rm -rf prog