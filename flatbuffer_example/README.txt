This is what was done in this folder to create a flatbuffer Example:

run:
	nano hello_world.fbs
	
put in fbs file contents
	
run:
	nano hello_world.cpp

put in contents to include hello_world_generated.h

run:
	g++ -o output_example hello_world.cpp hello_world_generated.h -lflatbuffers	

run:
	./output_example 
	to see results
