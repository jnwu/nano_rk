
##############################################################################


#*
#******************************************************************************
#*
#*    Description:
#*        Scheduleability Analysis Tool Makefile
#*
#******************************************************************************

TARGET := analyze
SRCS := task.cpp scheduling.cpp analyze.cpp

all: $(TARGET)

OBJS = $(SRCS:.cpp=.o)

$(TARGET): $(OBJS)
	g++  -o $(TARGET) $^ 

install:
	install -d $(DESTDIR)/usr/bin/
	install $(TARGET)  $(DESTDIR)/usr/bin/

clean:
	rm -f $(TARGET) $(OBJS)
