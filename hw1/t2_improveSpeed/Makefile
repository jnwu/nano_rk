
##############################################################################


#*
#******************************************************************************
#*
#*    Description:
#*        Task Set Tool Makefile
#*
#******************************************************************************

TARGET := set
SRCS := generator.cpp generatorTool.cpp

all: $(TARGET)

OBJS = $(SRCS:.cpp=.o)

$(TARGET): $(OBJS)
	g++  -o $(TARGET) $^ 

install:
	install -d $(DESTDIR)/usr/bin/
	install $(TARGET)  $(DESTDIR)/usr/bin/

clean:
	rm -f $(TARGET) $(OBJS)
