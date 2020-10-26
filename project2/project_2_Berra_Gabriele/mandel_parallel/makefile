all: mandel_par

mandel_par: mandel_par.c pngwriter.c
	gcc -o $@ -I. -O3 $^ -lpng -fopenmp

clean:
	rm -rf mandel_par

