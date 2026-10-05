#include "geometry.h"

#include <exception>
#include <filesystem>
#include <iostream>
#include <sstream>
#include <string>

namespace
{
bool ReadChoice(int& choice, int minimum, int maximum)
{
    std::string line;

    while (std::getline(std::cin, line))
    {
        std::istringstream input(line);
        int value = 0;

        if (input >> value)
        {
            input >> std::ws;

            if (input.eof() && value >= minimum && value <= maximum)
            {
                choice = value;
                return true;
            }
        }

        std::cout << "Ошибка: выберите пункт от " << minimum
                  << " до " << maximum << ": ";
    }

    return false;
}
}

int main(int argc, char* argv[])
{
    if (argc > 3)
    {
        std::cerr << "Использование: lab1 [файл координат] [файл результатов]\n";
        return 1;
    }

    const std::filesystem::path coordinatesPath = argc > 1 ? argv[1] : "coordinates.txt";
    const std::filesystem::path resultsPath = argc > 2 ? argv[2] : "results.txt";

    while (true)
    {
        std::cout << "\n1 — квадрат\n2 — круг\n0 — выход\nВыберите область: ";
        int shape = 0;

        if (!ReadChoice(shape, 0, 2) || shape == 0)
        {
            break;
        }

        std::cout << "1 — ввод с клавиатуры\n2 — ввод из файла\nИсточник координат: ";
        int source = 0;

        if (!ReadChoice(source, 1, 2))
        {
            break;
        }

        try
        {
            double x = 0.0;
            double y = 0.0;

            if (source == 1)
            {
                if (!ReadCoordinatesFromKeyboard(x, y))
                {
                    break;
                }
            }
            else
            {
                ReadCoordinatesFromFile(coordinatesPath, &x, &y);
            }

            const bool isCircle = shape == 2;
            const bool isInside = isCircle ? IsInsideCircle(x, y) : IsInsideSquare(x, y);
            PrintResult(x, y, isCircle, isInside);
            SaveResult(resultsPath, x, y, isCircle, isInside);
            std::cout << "Результат записан в " << resultsPath.string() << ".\n";
        }
        catch (const std::exception& error)
        {
            std::cerr << "Ошибка: " << error.what() << '\n';
        }
    }

    return 0;
}
