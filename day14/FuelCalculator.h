#ifndef DAY14_FUELCALCULATOR_H
#define DAY14_FUELCALCULATOR_H

#include <functional>
#include <list>
#include <map>
#include <string>
#include <vector>

class FuelCalculator {
 public:
  explicit FuelCalculator(const std::string& inputPath);

  unsigned long calculateOrePerFuel(unsigned long fuelNeed = 1);
  long unsigned calculateFuelCount(unsigned long ores);

 private:
  struct Ingredient {
    std::string name{};
    long unsigned count{0};
  };

  struct Recipe {
    std::vector<Ingredient> inputIngredients;
    Ingredient outputIngredient;
  };

  class IngredientsList : public std::list<FuelCalculator::Ingredient> {
   public:
    bool empty() {
      if (std::list<FuelCalculator::Ingredient>::empty()) return true;

      const auto hasNoIngredient = [](const auto& ingredient) {
        return ingredient.count == 0;
      };

      if (all_of(hasNoIngredient)) {
        clear();
        return true;
      }

      remove_if(hasNoIngredient);
      return false;
    }

    void erase(const std::string& name) {
      const auto hasThisName = [name](const auto& ingredient) {
        return ingredient.name == name;
      };

      this->remove_if(hasThisName);
    }

    bool hasIngredient(const std::string& name) {
      const auto hasThisName = [name](const auto& ingredient) {
        return ingredient.name == name;
      };

      return std::find_if(begin(), end(), hasThisName) != end();
    }

    long unsigned& operator[](const std::string& name) {
      const auto hasThisName = [name](const auto& ingredient) {
        return ingredient.name == name;
      };

      auto it = std::find_if(begin(), end(), hasThisName);
      if (it == end()) {
        push_back(Ingredient{name, 0});
        return back().count;
      } else {
        return it->count;
      }
    }

    template <typename Function>
    bool all_of(const Function& function) {
      return std::all_of(begin(), end(), function);
    }
  };

  std::string _inputPath;
  IngredientsList _leftovers;

  std::vector<Ingredient> parseIngredients(const std::string& str);
  std::vector<Recipe> parseInput(const std::vector<std::string>& input);
  unsigned long calculateFuelCost(const std::map<std::string, Recipe>& recipes,
                                  unsigned long fuelNeed);
  static unsigned long getFactor(unsigned long recipeCount,
                                 unsigned long ingredientCount);
};

#endif  // DAY14_FUELCALCULATOR_H
