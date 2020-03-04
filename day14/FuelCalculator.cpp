#include "FuelCalculator.h"

#include <cmath>
#include <iostream>
#include <list>
#include <regex>

#include "util.h"

FuelCalculator::FuelCalculator(const std::string& inputPath)
    : _inputPath(inputPath) {}

std::vector<FuelCalculator::Ingredient> FuelCalculator::parseIngredients(
    const std::string& str) {
  std::regex ingredientPattern{R"#(^\s?(\d+)\s+(\w+)\s?$)#"};
  std::vector<Ingredient> ingredients;

  auto splitString = util::split(str, ',');

  for (const auto& value : splitString) {
    std::smatch matchResult;
    if (!std::regex_match(value, matchResult, ingredientPattern)) {
      std::cerr << "could not parse value: " << value << std::endl;
      continue;
    }

    Ingredient ingredient{};
    ingredient.count = std::stoul(matchResult[1].str());
    ingredient.name = matchResult[2].str();
    ingredients.push_back(ingredient);
  }

  return ingredients;
}

std::vector<FuelCalculator::Recipe> FuelCalculator::parseInput(
    const std::vector<std::string>& input) {
  std::vector<Recipe> recipes;

  std::regex recipePattern{R"#(^(.+)\s=>\s(\d+\s\w+)$)#"};

  for (const auto& line : input) {
    std::smatch matchResult;
    if (!std::regex_match(line, matchResult, recipePattern)) {
      std::cerr << "could not parse line: " << line << std::endl;
      continue;
    }

    auto outputIngredient = matchResult[2].str();
    auto inputIngredients = matchResult[1].str();

    Recipe recipe{};

    recipe.inputIngredients = parseIngredients(inputIngredients);
    recipe.outputIngredient = parseIngredients(outputIngredient).front();

    recipes.push_back(recipe);
  }

  return recipes;
}

unsigned long FuelCalculator::calculateFuelCost(
    const std::map<std::string, Recipe>& recipes, unsigned long fuelNeed) {
  IngredientsList neededIngredients;

  for (auto ingredient : recipes.at("FUEL").inputIngredients) {
    ingredient.count *= fuelNeed;
    neededIngredients.push_back(ingredient);
  }

  auto isBasicIngredient =
      [&recipes](const std::list<FuelCalculator::Ingredient>::value_type& val) {
        return recipes.at(val.name).inputIngredients.size() == 1 &&
               recipes.at(val.name).inputIngredients.front().name == "ORE";
      };

  while (!neededIngredients.all_of(isBasicIngredient)) {
    std::map<std::string, long unsigned> newIngredients;
    std::vector<std::string> ingredientsToRemove;

    Ingredient neededIngredient = neededIngredients.front();
    neededIngredients.pop_front();

    if (isBasicIngredient(neededIngredient)) {
      neededIngredients.push_back(neededIngredient);
      continue;
    }

    if (_leftovers.hasIngredient(neededIngredient.name)) {
      if (_leftovers[neededIngredient.name] > neededIngredient.count) {
        _leftovers[neededIngredient.name] -= neededIngredient.count;
        continue;
      } else {
        neededIngredient.count -= _leftovers[neededIngredient.name];
        _leftovers.erase(neededIngredient.name);
      }
    }

    const auto& ingredientRecipe = recipes.at(neededIngredient.name);
    auto factor = getFactor(ingredientRecipe.outputIngredient.count,
                            neededIngredient.count);

    auto leftoversCount = ingredientRecipe.outputIngredient.count * factor -
                          neededIngredient.count;
    if (leftoversCount > 0) {
      _leftovers[neededIngredient.name] += leftoversCount;
    }

    for (const auto& [name, count] : ingredientRecipe.inputIngredients) {
      auto newIngredientsCount = factor * count;
      if (_leftovers.hasIngredient(name)) {
        if (_leftovers[name] > newIngredientsCount) {
          _leftovers[name] -= newIngredientsCount;
          continue;
        } else {
          newIngredientsCount -= _leftovers[name];
          _leftovers.erase(name);

          if (newIngredientsCount == 0) continue;
        }
      }

      neededIngredients[name] += newIngredientsCount;
    }
  }

  long unsigned cost{0};
  for (const auto& [ingredientName, ingredientCount] : neededIngredients) {
    const auto& ingredientRecipe = recipes.at(ingredientName);
    auto factor =
        getFactor(ingredientRecipe.outputIngredient.count, ingredientCount);
    cost += factor * ingredientRecipe.inputIngredients.front().count;
  }

  return cost;
}

unsigned long FuelCalculator::getFactor(unsigned long recipeCount,
                                        unsigned long ingredientCount) {
  if (ingredientCount == 0)
    return 0;
  else if (recipeCount >= ingredientCount)
    return 1;
  else
    return std::ceil(double(ingredientCount) / double(recipeCount));
}

unsigned long FuelCalculator::calculateOrePerFuel(unsigned long fuelNeed) {
  auto programInput = util::readInput(_inputPath.c_str());
  auto recipes = parseInput(programInput);

  std::map<std::string, Recipe> recipesMap;

  auto recipeToPair = [](const Recipe& recipe) {
    return std::make_pair(recipe.outputIngredient.name, recipe);
  };

  std::transform(recipes.begin(), recipes.end(),
                 std::inserter(recipesMap, recipesMap.end()), recipeToPair);

  return calculateFuelCost(recipesMap, fuelNeed);
}

long unsigned FuelCalculator::calculateFuelCount(unsigned long ores) {
  auto programInput = util::readInput(_inputPath.c_str());
  auto recipes = parseInput(programInput);

  std::map<std::string, Recipe> recipesMap;

  auto recipeToPair = [](const Recipe& recipe) {
    return std::make_pair(recipe.outputIngredient.name, recipe);
  };

  std::transform(recipes.begin(), recipes.end(),
                 std::inserter(recipesMap, recipesMap.end()), recipeToPair);

  unsigned long first = 0;
  unsigned long last = ores;
  unsigned long middle = first + (last - first) / 2;

  while (first < last) {
    _leftovers.clear();
    if (calculateFuelCost(recipesMap, middle) < ores) {
      first = middle + 1;
    } else {
      last = middle - 1;
    }
    middle = first + (last - first) / 2;
  }

  return middle;  // -1 ?
}
