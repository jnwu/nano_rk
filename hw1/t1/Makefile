
##############################################################################


#*
#******************************************************************************
#*
#*    Description:
#*        Scheduleability Analysis Tool Makefile
#*
#******************************************************************************

TARGET := testRunner
SRCS := task.cpp scheduling.cpp testRunner.cpp testResult.cpp

all: $(TARGET)

OBJS = $(SRCS:.cpp=.o)

$(TARGET): $(OBJS)
	g++  -o $(TARGET) $^ 

install:
	install -d $(DESTDIR)/usr/bin/
	install $(TARGET)  $(DESTDIR)/usr/bin/

clean:
	rm -f $(TARGET) $(OBJS)
