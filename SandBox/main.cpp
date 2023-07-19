#include <iostream>
#include <thread>
#include <future>


// This function simulates a simple worker function.
// It either returns a string message or throws an exception based on the passed boolean status.
template <typename T>
std::string func(const bool status)
{
	if (status)
		return "This is my string message";
	throw std::exception("There is an exception has been thrown.");
}

// This function, called a thunk, is designed to wrap the execution of our worker function (func) 
// with exception handling and the setting of promise value.
template <typename T>
void Thunk(std::promise<T>&& prms, const bool& status)
{
	try
	{
		T result = func<T>(status); // calling the worker function
		prms.set_value(result); // setting the promise value
	}
	catch (...)
	{
		// if an exception is thrown, set the promise exception so it can be handled in the parent thread
		prms.set_exception(std::current_exception());
	}

}

int main()
{
	std::promise<std::string> prms; // creating a std::promise
	std::future<std::string> future = prms.get_future(); // getting the associated future
	bool status{ true };
	// starting the new thread with the thunk function that takes our promise and status
	std::thread thunkThread(Thunk<std::string>, std::move(prms), std::ref(status));
	try
	{
		// if the worker function completes successfully, print out the result
		std::cout << future.get() << '\n';
	}
	catch (const std::exception& e)
	{
		// if an exception was thrown, print the exception message
		std::cout << e.what() << std::endl;
	}

	thunkThread.join(); // join the thread to the main thread
}
