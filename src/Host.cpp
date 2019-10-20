#include "Host.h"

unsigned int Host::RevealDoor(unsigned int chosen_door,
                              const std::vector<unsigned int> &available_doors) {
  return *std::find_if(
      begin(available_doors), end(available_doors),
      [&](auto value) { return (value != realDoor && value != chosen_door); });
}
