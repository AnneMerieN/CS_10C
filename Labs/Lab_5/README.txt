For the first test, build a.out and run it against the test1 input

% c++ -std=c++14 main.cpp Heap.cpp PrintJob.cpp
% ./a.out < test1.in > mine.out

And then see if it worked
% diff mine.out test1.out

--------------------------------------------------

For the second test, compile test2.cpp.  When you run it, it should not
print anything out

% c++ -std=c++14 test2.cpp Heap.cpp PrintJob.cpp
% ./a.out

--------------------------------------------------

For the third test, compile test3.cpp.  When you run it, it should not
print anything out

% c++ -std=c++14 test3.cpp Heap.cpp PrintJob.cpp
% ./a.out
