#pragma once

#include <filesystem>

bool ReadCoordinatesFromKeyboard(double& x, double& y);
void ReadCoordinatesFromFile(const std::filesystem::path& path, double* x, double* y);
bool IsInsideCircle(double x, double y);
bool IsInsideSquare(double x, double y);
void PrintResult(double x, double y, bool isCircle, bool isInside);
void SaveResult(const std::filesystem::path& path,
                double x, double y, bool isCircle, bool isInside);
