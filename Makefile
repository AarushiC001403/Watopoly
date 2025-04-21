# Universal makefile for single C++ program
#
# Use gcc flag -MMD (user) or -MD (user/system) to generate dependencies among source files.
# Use make default rules for commonly used file-name suffixes and make variables names.
#
# % make [ a.out ]

########## Variables ##########

CXX = g++-14.2.0					# compiler
CXXFLAGS = -std=c++20 -fmodules-ts -g -Wall -MMD		# compiler flags
HEADERS = vector iostream map algorithm unordered_set memory array random sstream fstream string
HEADERFLAGS = -std=c++20 -fmodules-ts -c -x c++-system-header # compiler flags 
MAKEFILE_NAME = ${firstword ${MAKEFILE_LIST}}	# makefile name

SOURCES = Player.cc Player-impl.cc Square.cc Square-impl.cc Property.cc Property-impl.cc \
			Gym.cc Gym-impl.cc Residence.cc Residence-impl.cc AcademicBldg.cc AcademicBldg-impl.cc \
			NonProperty.cc NonProperty-impl.cc Tuition.cc Tuition-impl.cc SLC.cc SLC-impl.cc NH.cc NH-impl.cc Observer.cc \
			Subject.cc Subject-impl.cc Board.cc Board-impl.cc TextDisplay.cc TextDisplay-impl.cc Dice.cc Dice-impl.cc GamePlay.cc \
			GamePlay-impl.cc main.cc	# source files (*.cc)

OBJECTS = ${SOURCES:.cc=.o}			# object files forming executable
DEPENDS = ${OBJECTS:.o=.d}			# substitute ".o" with ".d"
EXEC = watopoly					# executable name

########## Targets ##########

.PHONY: all clean headers

all: headers ${EXEC}  # Compile system headers first, then full build

headers:
	@for header in ${HEADERS}; do \
		${CXX} ${HEADERFLAGS} ${HEADERFLAGS} $$header || exit 1; \
	done

${EXEC} : ${OBJECTS}				# link step
	${CXX} ${CXXFLAGS} $^ -o $@		# additional object files before $^

${OBJECTS} : ${MAKEFILE_NAME}			# OPTIONAL : changes to this file => recompile

# make implicitly generates rules to compile C++ files that generate .o files

-include ${DEPENDS}				# include *.d files containing program dependences

clean :						# remove files that can be regenerated
	rm -f ${DEPENDS} ${OBJECTS} ${EXEC}
