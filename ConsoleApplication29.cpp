#include <iostream>
#include <vector>
#include <string>

struct heap_elem {
  long long value;
  size_t request;
};

void Exchange(std::vector<heap_elem>& my_heap, size_t first_element, size_t second_element, std::vector<size_t>& pointers) {
  std::swap(my_heap[first_element], my_heap[second_element]);
  std::swap(pointers[my_heap[first_element].request], pointers[my_heap[second_element].request]);
}

void SiftUp(std::vector<heap_elem>& my_heap, size_t pointer, std::vector<size_t>& pointers) {
  while (pointer > 0) {
    size_t parent_pointer = (pointer - 1) / 2;
    if (my_heap[parent_pointer].value > my_heap[pointer].value) {
      Exchange(my_heap, pointer, parent_pointer, pointers);
      pointer = parent_pointer;
    }
    else break;
  }
}

void SiftDown(std::vector<heap_elem>& my_heap, size_t pointer, size_t heap_size, std::vector<size_t>& pointers) {
  while (2 * pointer + 1 < heap_size) {
    size_t child_pointer = 2 * pointer + 1;
    if (child_pointer + 1 < heap_size && my_heap[child_pointer + 1].value < my_heap[child_pointer].value) {
      ++child_pointer;
    }
    if (my_heap[child_pointer].value < my_heap[pointer].value) {
      Exchange(my_heap, pointer, child_pointer, pointers);
      pointer = child_pointer;
    }
    else {
      break;
    }
  }
}

void Insert(std::vector<heap_elem>& my_heap, long long new_elem, size_t& heap_size, std::vector<size_t>& pointers, size_t& pointers_size) {
  my_heap[heap_size].value = new_elem;
  my_heap[heap_size].request = pointers_size;
  pointers[pointers_size] = heap_size;
  SiftUp(my_heap, heap_size, pointers);
  ++heap_size;
  ++pointers_size;
}

void GetMin(std::vector<heap_elem>& my_heap, size_t& pointers_size) {
  ++pointers_size;
  std::cout << my_heap[0].value << std::endl;
}

void ExtractMin(std::vector<heap_elem>& my_heap, size_t& heap_size, std::vector<size_t>& pointers, size_t& pointers_size) {
  ++pointers_size;
  Exchange(my_heap, 0, heap_size - 1, pointers);
  SiftDown(my_heap, 0, --heap_size, pointers);
}

void DecreaseKey(std::vector<heap_elem>& my_heap, size_t pointer, long long delta, std::vector<size_t>& pointers, size_t& pointers_size) {
  ++pointers_size;
  my_heap[pointers[pointer - 1]].value -= delta;
  SiftUp(my_heap, pointers[pointer - 1], pointers);
}

void Execute(std::vector<heap_elem>& my_heap, size_t& heap_size, std::vector<size_t>& pointers, size_t& pointers_size, std::string request) {
  if (request == "insert") {
    long long new_elem;
    std::cin >> new_elem;
    Insert(my_heap, new_elem, heap_size, pointers, pointers_size);
  }
  if (request == "getMin") {
    GetMin(my_heap, pointers_size);
  }
  if (request == "extractMin") {
    ExtractMin(my_heap, heap_size, pointers, pointers_size);
  }
  if (request == "decreaseKey") {
    size_t pointer;
    std::cin >> pointer;
    long long delta;
    std::cin >> delta;
    DecreaseKey(my_heap, pointer, delta, pointers, pointers_size);
  }
}

int main() {
  std::vector <heap_elem> my_heap(100000);
  size_t heap_size = 0;
  std::vector <size_t> pointers(1000000);
  size_t pointers_size = 0;

  int q;
  std::cin >> q;

  for (int i = 0; i < q; ++i) {
    std::string request;
    std::cin >> request;
    Execute(my_heap, heap_size, pointers, pointers_size, request);
  }
  return 0;
}