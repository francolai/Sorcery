#ifndef subject_h
#define subject_h
#include <vector>
#include <memory>

class Observer;
class Subject {
	std::vector<std::unique_ptr<Observer>> ob;
	public:
	void attach(std::unique_ptr<Observer>);
	void notifyObserver();
	//virtual void getPrintingInfo() = 0;
};
	
