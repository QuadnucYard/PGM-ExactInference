#pragma once

#ifndef USE_YAML

#include "xmlutils.hpp"
#include "tinyxmliterator.h"

#else

#include <yaml-cpp/yaml.h>

#endif // !USE_YAML

#include <fstream>
#include <filesystem>
#include <format>