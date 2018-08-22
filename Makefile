ola2:	sa.cpp greedy.cpp SumofGaussians.cpp SumofGaussians.h
	g++ -o sa sa.cpp SumofGaussians.cpp
	g++ -o greedy greedy.cpp SumofGaussians.cpp

clean:
	rm sa
	rm greedy
