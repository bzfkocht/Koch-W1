.PHONY:		clean

CXXFLAGS=	-Wall -Wextra -g -O
OBJECT	=	$(SOURCE:.cpp=.o)

$(BINARY): $(OBJECT)
	$(CXX) $(LDFLAGS) $^ -o $@

clean:
	-rm $(OBJECT) $(BINARY)

%.o:	%.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $<




