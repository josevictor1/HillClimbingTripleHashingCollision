CXX = g++
CXXFLAGS = -Ofast -std=c++11



collision: md5.o collision.o main.o
	$(CXX) $(CXXFLAGS) $^ -o $@

clean:
	@$(RM) collision *.o

rebuild: clean collision

.PHONY: collision clean rebuild
