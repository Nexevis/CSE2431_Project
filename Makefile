CC = g++
DEBUG = -g
CFLAGS = -Wall $(DEBUG)

default :
		$(CC) $(CFLAGS) -o host host.c; \
			$(CC) $(CFLAGS) -o remote remote.c

clean:
		\rm host remote
tar:
		tar czfv project.tar.gz host.c remote.c Makefile
