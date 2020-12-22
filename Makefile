TARNAME = barnsley_farn# chose a name for tar archive
HOST = localhost# host name of receiving operating system
USER = chaka# username on receiving operating system
PORT = 2222# port to use, should stay 2222

all:
	@echo "This is a dummy to prevent running make without explicit target!"

clean: remove_tarfile remove_srcfiles
	rm -f barnsley_farn

pack: clean
	tar -czf $(TARNAME).tar.gz src/ Makefile

unpack:
	mkdir $(TARNAME)
	tar -zxvf $(TARNAME).tar.gz -C $(TARNAME)
	rm Makefile $(TARNAME).tar.gz
	cd $(TARNAME)

send: pack
	scp -P $(PORT) $(TARNAME).tar.gz $(USER)@$(HOST):~/

compile: clean
	mkdir -p src/build/
	cd src/build/ && cmake -DCMAKE_BUILD_TYPE=Release ..
	$(MAKE) -C src/build/
	mv src/build/barnsley_fern barnsley_fern

remove_tarfile:
	rm -f $(TARNAME).tar.gz

remove_srcfiles:
	rm -rf src/.idea
	rm -rf src/build
	rm -rf src/cmake-build-debug
	
# to extract Makefile to be able to unpack files
# tar -zxvf ($TARNAME).tar.gz Makefile