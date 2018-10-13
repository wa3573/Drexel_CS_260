time:
	@chmod 755 .
	@g++ -std=c++14 timing.cpp lcrstree.cpp loctree.cpp pointerqueue.cpp list.cpp -o astest.o
	@./astest.o time_tree_loc 3
	@./astest.o time_tree_loc 4
	@./astest.o time_tree_loc 5
	@./astest.o time_tree_lcrs 3
	@./astest.o time_tree_lcrs 4
	@./astest.o time_tree_lcrs 5
	
loctree:
	@chmod 755 .
	@g++ -std=c++14 timing.cpp lcrstree.cpp loctree.cpp pointerqueue.cpp list.cpp -o astest.o
	@./astest.o test_tree_loc

lcrstree:
	@chmod 755 .
	@g++ -std=c++14 timing.cpp lcrstree.cpp loctree.cpp pointerqueue.cpp list.cpp -o astest.o
	@./astest.o test_tree_lcrs

pointerqueue:
	@chmod 755 .
	@g++ -std=c++14 timing.cpp lcrstree.cpp loctree.cpp pointerqueue.cpp list.cpp -o astest.o
	@./astest.o test_queue

mergelists:
	@chmod 755 .
	@g++ -std=c++14 mergelists.cpp list.cpp -o astest.o
	@./astest.o

listconcat:
	@chmod 755 .
	@g++ -std=c++14 listconcat.cpp list.cpp -o astest.o
	@./astest.o

levelorder:
	@chmod 755 .
	@g++ -std=c++14 levelorder.cpp loctree.cpp list.cpp -o astest.o
	@./astest.o

traversalconvert:
	@chmod 755 .
	@g++ -std=c++14 traversalconvert.cpp loctree.cpp list.cpp -o astest.o
	@./astest.o

preorder:
	@chmod 755 .
	@g++ -std=c++14 preorder.cpp loctree.cpp list.cpp -o astest.o
	@./astest.o

postorder:
	@chmod 755 .
	@g++ -std=c++14 postorder.cpp loctree.cpp list.cpp -o astest.o
	@./astest.o
	
huffman:
	@chmod 755 .
	@g++ -std=c++14 huffman.cpp -o astest.o
	@./astest.o
	
clean:
	@\rm -f *.o *.csv

.PHONY: time pointerqueue loctree lcrstree mergelists listconcat levelorder traversalconvert preorder postorder huffman
