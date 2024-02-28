#pragma once

#include "../ErrorHandler/ErrorHandler.hpp"

#include <source_location>

#define ERR(str) ErrorHandler::finish(str, std::source_location::current().function_name(), std::source_location::current().line())