#pragma once

#include <functional>
#include <memory>
#include <deque>
#include <atomic>
#include <thread>
#include <future>

#define MakeTask(func) std::make_unique<Task>(Task(func))

class TaskMaster;

struct Task {
	friend TaskMaster;

public:
	Task(std::function<void()> task);
	~Task();

	void Run();

	std::function<void()> task;
};

__declspec(align(128))
struct Thread {
	std::thread thread;

	void* operator new(size_t i){ return _mm_malloc(i, 128); }
	void operator delete(void* p) { _mm_free(p); }
};

class TaskMaster {
public:
	static bool initialise(int workPoolSize = 0);
	static void shutdown();
	static void process();

	static unsigned int getNumberOfThreads();
	static void addTask(std::unique_ptr<Task> task);
	static std::unique_ptr<Task> getNextTask();

	static std::atomic_bool runThreads;
	static unsigned int getNumberOfTasks();
	static unsigned int getNumberOfTasksInProgress();
	static bool isDoingWork();
private:
	friend Task;

	static std::mutex taskLock;
	static std::atomic_int jobsInProgress;
	static std::atomic_int tasksInQueue;

	static std::deque<std::unique_ptr<Task>> taskList;
	static std::vector<std::unique_ptr<Thread>> threadPool;
};