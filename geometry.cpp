#include "geometry.h"

#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>
#include <stdexcept>
#include <string>

namespace
{
bool ReadCoordinates(std::istream& input, double& x, double& y)
{
    double inputX = 0.0;
    double inputY = 0.0;

    if (!(input >> inputX >> inputY))
    {
        return false;
    }

    input >> std::ws;

    if (!input.eof() || !std::isfinite(inputX) || !std::isfinite(inputY))
    {
        return false;
    }

    x = inputX;
    y = inputY;
    return true;
}

void WriteResult(std::ostream& output,
                 double x, double y, bool isCircle, bool isInside)
{
    output << std::setprecision(std::numeric_limits<double>::max_digits10)
           << "Точка (" << x << ", " << y << ") "
           << (isInside ? "попадает" : "не попадает")
           << " в " << (isCircle ? "круг" : "квадрат") << ".\n";
}
}

bool ReadCoordinatesFromKeyboard(double& x, double& y)
{
    std::string line;

    while (true)
    {
        std::cout << "Введите координаты x и y через пробел: ";

        if (!std::getline(std::cin, line))
        {
            return false;
        }

        std::istringstream input(line);

        if (ReadCoordinates(input, x, y))
        {
            return true;
        }

        std::cout << "Ошибка: введите ровно два конечных числа.\n";
    }
}

void ReadCoordinatesFromFile(const std::filesystem::path& path, double* x, double* y)
{
    if (x == nullptr || y == nullptr)
    {
        throw std::invalid_argument("Не передан указатель на координату.");
    }

    std::ifstream input(path);

    if (!input)
    {
        throw std::runtime_error("Не удалось открыть файл координат: " + path.string());
    }

    if (!ReadCoordinates(input, *x, *y))
    {
        throw std::runtime_error("Файл координат должен содержать ровно два конечных числа.");
    }
}

bool IsInsideCircle(double x, double y)
{
    return std::isfinite(x) && std::isfinite(y) && std::hypot(x, y) <= 1.0;
}

bool IsInsideSquare(double x, double y)
{
    return std::isfinite(x) && std::isfinite(y)
           && std::abs(x) <= 1.0 && std::abs(y) <= 1.0;
}

void PrintResult(double x, double y, bool isCircle, bool isInside)
{
    WriteResult(std::cout, x, y, isCircle, isInside);
}

void SaveResult(const std::filesystem::path& path,
                double x, double y, bool isCircle, bool isInside)
{
    std::ofstream output(path, std::ios::app);

    if (!output)
    {
        throw std::runtime_error("Не удалось открыть файл результатов: " + path.string());
    }

    WriteResult(output, x, y, isCircle, isInside);
    output.flush();

    if (!output)
    {
        throw std::runtime_error("Не удалось записать результат в файл.");
    }
}
