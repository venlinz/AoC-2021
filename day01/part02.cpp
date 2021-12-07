// CPP part 2.
#include <iostream>
#include <fstream>
#include <array>
#include <numeric>
#include <iterator>
#include <vector>

#define INPUT_FILENAME "input.txt"
#define ARRAY_SIZE 1024 * 2

int main(void)
{
    std::ifstream input_file(INPUT_FILENAME);

    if (!input_file.is_open())
    {
        perror("* Error can't able to open file. State ");
        std::exit(EXIT_FAILURE);
    }
    std::string number_str;
    std::vector<int> input_numbers;
    while (std::getline(input_file, number_str))
    {
        input_numbers.push_back(std::stoi(number_str));
    }
    input_file.close();

    auto begin { std::begin(input_numbers) };
    auto end { std::end(input_numbers) };

    size_t depth_inclinations_than_prev = 0;
    for (auto i { begin + 3 }; i != end; ++i)
    {
        if (*i > *(i - 3))
        {
            depth_inclinations_than_prev++;
        }
    }
    std::cout << "depth_inclinations_than_prev: " << depth_inclinations_than_prev << '\n';
    return 0;
}
