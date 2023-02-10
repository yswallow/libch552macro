LIBCH552MACRO_ROOT := ../..
PROJECT_NAME := led

build/$(PROJECT_NAME): build/$(PROJECT_NAME).o build/libch552macro.o
	cc -o build/$(PROJECT_NAME) /usr/lib/libusb-1.0.so build/$(PROJECT_NAME).o build/libch552macro.o

build:
	mkdir -p build

build/$(PROJECT_NAME).o: build $(PROJECT_NAME).c
	gcc $(PROJECT_NAME).c -c -I/usr/include/libusb-1.0 -I$(LIBCH552MACRO_ROOT)/include -o build/$(PROJECT_NAME).o

build/libch552macro.o: build $(LIBCH552MACRO_ROOT)/src/libch552macro.c
	gcc $(LIBCH552MACRO_ROOT)/src/libch552macro.c -c -I/usr/include/libusb-1.0 -o build/libch552macro.o

.PHONY: clean exec
clean: build
	rm build/*

exec: build/$(PROJECT_NAME)
	sudo ./build/$(PROJECT_NAME)
