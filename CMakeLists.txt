project(SchedulerSimulator)

set(Sources
	./sources/main.cpp
	./headers/Processor.hpp
	./sources/Processor.cpp
	./headers/Scheduler.hpp
	./sources/Scheduler.cpp
	./headers/EventQueue.hpp
	./sources/EventQueue.cpp
	./headers/Event.hpp
	./sources/Event.cpp
	./headers/Task.hpp
	./sources/Task.cpp
	./headers/Burst.hpp
	./sources/Burst.cpp
	./headers/RRQueue.hpp
	./sources/RRQueue.cpp
	./headers/ReadyQueue.hpp
	./sources/ReadyQueue.cpp
	./headers/IOQueues.hpp
	./sources/IOQueues.cpp
	./headers/SJQueue.hpp
	./sources/SJQueue.cpp
	./headers/ASJQueue.hpp
	./sources/ASJQueue.cpp
	./headers/MemManager.hpp
	./sources/MemManager.cpp
)

set(CMAKE_CXX_FLAGS --std=c++11)

add_executable(SchedulerSimulator ${Sources})
