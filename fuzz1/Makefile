level=fuzz1
target=/opt/workshop1/$(level)

all:
	gcc -m32 -fno-stack-protector main.c -o $(level)
	execstack -s $(level)

install: all
	install -D --owner nobody --group nogroup --mode 4755 $(level) $(target)
	install -D --owner nobody --group nogroup --mode 644 main.c $(target).c

clean:
	rm -f $(level) *~
