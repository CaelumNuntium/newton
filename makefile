newton: newton.c test_newton.c gauss.c newton.h f.h
	gcc -O2 -lm newton.c test_newton.c gauss.c -o newton
