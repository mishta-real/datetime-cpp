all: datetime

datetime: datetime.cpp timedelta.cpp main.cpp
	g++ datetime.cpp timedelta.cpp main.cpp -o datetime

clean:
	rm datetime
