
First run the following command to install git repos of afl and flatbuffer

	git submodule update --init --recursive


AFL:
	cd into afl folder
	run: make clean all
	run: make install

Flatbuffer:
	cd into flatbuffer
	run: cmake -G "Unix Makefiles"
	run: make -j
	run make install
