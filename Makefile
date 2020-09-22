all: datetime

datetime: datetime.cpp main.cpp
	g++ datetime.cpp main.cpp -o datetime

clean:
	rm datetime
