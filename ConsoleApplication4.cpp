#include <iostream>
#include <array>
#include <chrono>
#include <functional>
#include <limits>
#include <random>
#include <thread>
#include <vector>

std::vector<int> random_ints(int n)
{
	static std::mt19937 random_gen{std::random_device{}()};
	std::uniform_int_distribution<int> dist(0,std::numeric_limits<int>::max());
	std::vector<int> return_value;
	std::generate_n(std::back_inserter(return_value),n,[&](){ return dist(random_gen); });
	return return_value;
}

template <typename T = std::less<>>
void bubble_sort(auto& to_sort,T compare = std::less<>{});




int partition(auto& to_partition, int p_start, int p_end)
{	      
	//as pivot, choose to_partition[beginning]
	//if you are interested, look up median of medians
	int p_start_copy = p_start;
	int currentPivot = to_partition[p_start];
	while (p_start < p_end)
	{
		while (p_start < p_end && to_partition[p_start] <= currentPivot) { ++p_start; }
		while (p_end >= p_start && to_partition[p_end] > currentPivot) { --p_end; }
		if (p_start < p_end)
			std::swap(to_partition[p_start], to_partition[p_end]);
	} 
	std::swap(to_partition[p_start_copy], to_partition[p_end]);
	return p_end;
}


void quicksort(auto& to_sort, int beginning, int end)
{
	if (end <= beginning) return;
	auto partition_point = partition(to_sort, beginning, end);
	quicksort(to_sort, beginning, partition_point - 1);
	quicksort(to_sort, partition_point + 1, end);
}

void quicksort(auto& to_sort)
{
	quicksort(to_sort, 0, to_sort.size() - 1);
}

bool compare(char letter_1, char  letter_2)
{
	return letter_1 < letter_2;
}
bool arc_compare(char letter_1, char letter_2)
{
	return letter_2 < letter_1;
}
bool is_sorted(auto &numbers)
{
	for (int i{}; i < numbers.size()-1; ++i)
	{
		if (numbers[i] > numbers[i + 1]) return false;
	}
	return true;
}

auto time(auto fun)
{
	auto start = std::chrono::steady_clock::now();
		fun();
	auto end = std::chrono::steady_clock::now();

	return end-start;

}

int main()
{
	auto numbers = random_ints(214744);
	auto copy = numbers;

	auto runtime = time([&]()
	{
		quicksort(numbers);
	});

	std::cout<<"Sorting took "<<std::chrono::duration_cast<std::chrono::milliseconds>(runtime)<<' ';
	if(!is_sorted(numbers))
	{
		std::cout<<"Whyyyyyy?\n";
		return -1;
	}
	
	auto runtime_std = time([&]()
	{
		std::sort(copy.begin(),copy.end());
	});

	std::cout<<"Std-Sorting took "<<std::chrono::duration_cast<std::chrono::milliseconds>(runtime_std)<<'\n';
	if(!is_sorted(copy))
	{
		std::cout<<"Whyyyyyy?\n";
		return -1;
	}

	std::this_thread::sleep_for(std::chrono::minutes{1});
}

template <typename T>
void bubble_sort(auto& to_sort,T compare)
{
	for (int j{}; j < to_sort.size(); ++j)
	{
		for (int i{}; i < to_sort.size() - 1; ++i)
		{
			if (compare(to_sort[i], to_sort[i + 1])) std::swap(to_sort[i], to_sort[i + 1]);
		}
	}
}

