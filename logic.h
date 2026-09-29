// logic.h
// Interface between the interaction layer (Coding B - MohammadHossein)
// and the core logic (Coding A - Soh Eu Zen).
//
// main.cpp only calls the function declared here.
// Soh implements it in logic.cpp.
//
// NOTE: The parameters below are a PROPOSED interface.
// Update the name, parameters and ranges once Soh confirms his design.

#ifndef LOGIC_H
#define LOGIC_H

#include <string>

// Valid input ranges shared by both sides.
// main.cpp validates against these before calling runCoreLogic(),
// so the core logic always receives valid values.
const int    CATEGORY_MIN = 1;
const int    CATEGORY_MAX = 3;
const double VALUE_MIN    = 0.0;
const double VALUE_MAX    = 1000.0;

// Core logic entry point (implemented by Coding A).
// selectedCategory: an already-validated option in [CATEGORY_MIN, CATEGORY_MAX]
// userValue:        an already-validated number in [VALUE_MIN, VALUE_MAX]
// Returns:          the result text to display to the user.
std::string runCoreLogic(int selectedCategory, double userValue);

#endif
