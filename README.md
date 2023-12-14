### Create The Environment
 [docker image](https://hub.docker.com/repository/docker/xctarman/flatbuf/general), the Docker environment is already set up for you.
2) Clone `Flatbuffers-Mutator`
3) Compile `Hydrogen` with the help of `CMakeLists.txt`.
4) Assuming you are using the Docker and Ninja, the steps would be like below. But first [install](https://docs.docker.com/install/) Docker using the recommended method for your system.
```sh
# Download and run the Docker from your system.
$ docker run -v "Path to store the afl project":/flatbuf -it --platform linux/arm64 xctarman/flatbuf
# The above command will put you inside the Docker Container.
$$ git clone https://github.com/xerxest/Flatbuffers-Mutator.git /flatbuf
$$ cd /flatbuf/Flatbuffers-Mutator
$$ 

```

### Building 
```sh
# To build the harness file ( rm CCMakeLists.txt before running cmake)  
$$ cd /flatbuf/Flatbuffers-Mutator/src/mutator/buildHarness
$$ cmake ..
# The re-build the mutator 
$$ cd /flatbuf/Flatbuffers-Mutator/build
$$ cmake .. 
```
### Running the AFL++ 
```sh
# To force afl to use the custom mutator 
$$ export AFL_CUSTOM_MUTATOR_ONLY=1
# Give afl the path for the custom mutator 
$$ export AFL_CUSTOM_MUTATOR_LIBRARY="/flatbuf/Flatbuffers-Mutator/build/libFlatBufferMutator.so"
# Running AFL
$$ cd /flatbuf/Flatbuffers-Mutator/src/mutator/buildHarness
$$ afl-fuzz -i ./seed -o ./output ./FlatBufferHarness
$ note if you get an error with running, make sure to refresh the .bfbs file
$$ cp test.bfbs outFlatbuf.bfbs
```
