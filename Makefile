all:
	gcc *.c cJSON/cJSON.c -lcurl -o cavkb -ggdb -g

clean:
	rm cavkb 