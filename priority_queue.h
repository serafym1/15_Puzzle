
// Simple queue to sort in given priority
// sorts after each push()

#include "vector"

template <typename T, typename Comparator = std::greater<T>>

class priority_queue {
	std::vector<T> queue;
	Comparator comp;
public:
	//priority_queue() = default;
	bool empty();
	void push(T value);
	void pop();
	T top();
};

template <typename T, typename Comparator>
void priority_queue<typename T, typename Comparator>::push(T value)
{
	queue.push_back(value);
	
	for (size_t i = 1; i < queue.size(); ++i) {
		T key = queue[i];
		size_t j = i;

		while (j > 0 && comp(key, queue[j - 1])) {
			queue[j] = queue[j - 1];
			--j;
		}
		queue[j] = key;
	}
}

template <typename T, typename Comparator>
void priority_queue<typename T, typename Comparator>::pop() {
	queue.erase(queue.begin());
}

template <typename T, typename Comparator>
bool priority_queue<typename T, typename Comparator>::empty() {
	return queue.empty();
}

template <typename T, typename Comparator>
T priority_queue<typename T, typename Comparator>::top() {
	return queue[0];
}
