defult:
	make -C src/
.PHONY: install clean remove
install:
	make -C src/ install
remove:
	make -C src/ remove
clean:
	make -C src/ clean
