#include <iostream>
#include <thread>
#include <future>


//Simple implementation of how std::async might work under the hood
template <typename T>
std::string func(const bool status)
{
	if (status)
		return "This is my string message";
	throw std::exception("There is an exception has been thrown.");
}

template <typename T>
void Thunk(std::promise<T>&& prms, const bool& status)
{
	try
	{
		T result = func<T>(status);
		prms.set_value(result);

		
	}
	catch (...)
	{
		prms.set_exception(std::current_exception());
	}

}

int main()
{

	std::promise<std::string> prms;
	std::future<std::string> future = prms.get_future();
	bool status{ true };
	std::thread thunkThread(Thunk<std::string>, std::move(prms), std::ref(status));
	try
	{
		std::cout << future.get() << '\n';
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}

	thunkThread.join();
}


/*std::future<std::string> future = std::async(std::launch::async, withoutPromise);
std::cout << future.get() << '\n';*/
//int main()
//{
//
//	/*std::future<std::string> future = std::async(std::launch::async, withoutPromise);
//	std::cout << future.get() << '\n';*/
//
//	std::promise<std::string> prms;
//	std::future<std::string> future = prms.get_future();
//	std::thread thunkThread(Thunk<std::string>, std::move(prms));
//	std::cout << future.get() << '\n';
//	thunkThread.join();
//}