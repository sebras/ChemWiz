
USE_DSRPDB=     yes


SRCS_CPP=	main.cpp molecule.cpp js-binding.cpp calc-engine-erkale.cpp process.cpp common.cpp Vec3-ext.cpp tm.cpp
HEADERS=	common.h Exception.h Mat3.h molecule.h Vec3.h js-binding.h calculators.h util.h process.h Vec3-ext.h tm.h
APP=		chemwiz
CXX?=		clang++80
CC?=		clang80
ifeq ($(DEBUG), yes)
CFLAGS=		-g -O0 -fno-omit-frame-pointer
else
CFLAGS=		-O3
endif
CFLAGS+=	-Wall -DPROGRAM_NAME=\"ChemWiz\"

CFLAGS+=	$(shell pkg-config --static --cflags mujs)
LDFLAGS+=	$(shell pkg-config --static --libs-only-L mujs)
LDLIBS+=	$(shell pkg-config --static --libs-only-l mujs)

CXXFLAGS=	$(CFLAGS) -std=c++17

ifeq ($(USE_DSRPDB), yes)
SRCS_CPP+=	molecule-dsrpdb.cpp
CXXFLAGS+=	-DUSE_DSRPDB
LDFLAGS+=	-ldsrpdb
endif

OBJS:=		$(SRCS_CPP:.cpp=.o) $(SRCS_C:.c=.o)

$(APP): $(OBJS) $(HEADERS) Makefile
	$(CXX) -o $(APP) $(LDFLAGS) $(OBJS) $(LDLIBS)

$(OBJS): $(HEADERS) Makefile

clean:
	rm -f $(OBJS) $(APP)
