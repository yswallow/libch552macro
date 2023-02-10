LIBCH552MACRO_ROOT := ../..

build/copypad: build/copypad.o build/libch552macro.o
	cc -o build/copypad /usr/lib/libusb-1.0.so build/copypad.o build/libch552macro.o

build:
	mkdir -p build

build/copypad.o: build copypad.c
	gcc copypad.c -c -I/usr/include/libusb-1.0 -I$(LIBCH552MACRO_ROOT)/include -o build/copypad.o

build/libch552macro.o: build $(LIBCH552MACRO_ROOT)/src/libch552macro.c
	gcc $(LIBCH552MACRO_ROOT)/src/libch552macro.c -c -I/usr/include/libusb-1.0 -o build/libch552macro.o

.PHONY: clean exec
clean: build
	rm build/*

exec: build/copypad
	./build/copypad
