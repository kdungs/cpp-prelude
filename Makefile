CXXFLAGS=-O3 -Wall -Werror -pedantic -std=c++11

all: test_prelude

test: test_prelude
	./test_prelude

clean:
	rm -f test_prelude
