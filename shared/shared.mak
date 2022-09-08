.PHONY:		clean

CXXFLAGS=	-Wall -Wextra -g
OBJECT	=	$(SOURCE:.cpp=.o)

$(BINARY): $(OBJECT)
	$(CXX) $(LDFLAGS) $^ -o $@

clean:
	-rm $(OBJECT) $(BINARY)

%.o:	%.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $<




