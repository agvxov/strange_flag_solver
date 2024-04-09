%.o: %.cpp
	${COMPILE.cpp} $< -o $@

%.o: %.c
	${COMPILE.c} $< -o $@

main: main.o StrangeFlag.o tcl_displayer.o
	${LINK.cpp} $+ $$(pkg-config --libs tcl tk)

clean:
	-rm *.o
