levels=bof1 bof2 bof3 bof4 fmt1 fmt2 fmt3 fmt4 fmt5 fuzz1 fuzz2

build:
	for i in $(levels); do sudo make -C $$i install; done

clean:
	for i in $(levels); do sudo make -C $$i clean; done

install:
	sudo ./install-scripts/setup.sh
	make clean build
	./install-scripts/install-tools.sh
