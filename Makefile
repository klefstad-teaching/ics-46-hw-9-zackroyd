CXXFLAGS=-ggdb -std=c++20 -Wall -Wextra -Werror -Wfatal-errors -pedantic
compile_gtest: src/dijkstras.cpp src/dijkstras.h src/ladder.cpp src/ladder.h gtest/student_gtests.cpp
	cmake --build build --target student_gtests
gtest: compile_gtest
	./build/student_gtests
compile_ladder: src/ladder.cpp src/ladder.h src/ladder_main.cpp
	g++ $(CXXFLAGS) src/ladder.cpp src/ladder_main.cpp -o bin/ladder
ladder: compile_ladder
	./bin/ladder
compile_dijkstras: src/dijkstras.cpp src/dijkstras.h src/dijkstras_main.cpp
	g++ $(CXXFLAGS) src/dijkstras.cpp src/dijkstras_main.cpp -o bin/dijkstras
dijkstras: compile_dijkstras
	./bin/dijkstras