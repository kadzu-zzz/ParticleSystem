#include "TaskMaster.h"

Task::Task(std::function<void()> task) : task(task) {
}

Task::~Task() {
}

void Task::Run() {
	task();
	TaskMaster::jobsInProgress--;
}

std::mutex TaskMaster::taskLock;
std::deque<std::unique_ptr<Task>> TaskMaster::taskList = std::deque<std::unique_ptr<Task>>();
std::atomic_bool TaskMaster::runThreads = false;
std::atomic_int TaskMaster::jobsInProgress = 0;
std::atomic_int TaskMaster::tasksInQueue = 0;
std::vector<std::unique_ptr<Thread>> TaskMaster::threadPool = std::vector<std::unique_ptr<Thread>>();

void workPoolThread(int sleepLength) {
	while (TaskMaster::runThreads) {
		std::unique_ptr<Task> task = TaskMaster::getNextTask();

		if (task != nullptr) {
			task->Run();
		} else {
			std::this_thread::sleep_for(std::chrono::milliseconds(sleepLength));
		}
	}
}

bool TaskMaster::initialise(int workPoolSize) {
	runThreads = true;
	jobsInProgress = 0;

	for (unsigned int i = 0; i < std::max(workPoolSize != 0 ? workPoolSize : std::thread::hardware_concurrency(), 1u); i++) {
		threadPool.push_back(std::make_unique<Thread>());
		threadPool.back()->thread = std::thread(workPoolThread, 3 * (i + i));
		threadPool.back()->thread.detach();
	}

	taskList.clear();

	return true;
}

void TaskMaster::shutdown() {
	runThreads = false;
	jobsInProgress = 0;
	taskList.clear();
	threadPool.clear();
}

void TaskMaster::process() {
	runThreads = true;
}

unsigned int TaskMaster::getNumberOfThreads() {
	return threadPool.size();
}

void TaskMaster::addTask(std::unique_ptr<Task> task) {
	++tasksInQueue;
	while (!TaskMaster::taskLock.try_lock()) {
	}
	taskList.push_back(std::move(task));
	taskLock.unlock();
}

std::unique_ptr<Task> TaskMaster::getNextTask() {
	if (taskList.size() == 0)
		return nullptr;

	while (!TaskMaster::taskLock.try_lock()) {
	}

	if (taskList.size() != 0) {
		auto task = std::move(taskList.front());
		taskList.pop_front();
		++jobsInProgress;
		--tasksInQueue;
		taskLock.unlock();
		return task;
	}
	taskLock.unlock();
	return nullptr;
}

unsigned int TaskMaster::getNumberOfTasks() {
	return taskList.size();
}

unsigned int TaskMaster::getNumberOfTasksInProgress() {
	return static_cast<unsigned int>(jobsInProgress.load());
}

bool TaskMaster::isDoingWork() {
	return (tasksInQueue != 0 || jobsInProgress != 0);
}
