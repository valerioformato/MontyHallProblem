#include "Player.h"

unsigned int Player::ChooseDoor(const std::vector<unsigned int> &available_doors) {
  std::uniform_int_distribution<size_t> distr(0, available_doors.size()-1);

  return available_doors.at(distr(*_mtGen));
}

unsigned int Player::SwitchDoor(unsigned int chosen_door,
                                unsigned int revealedDoor,
                                const std::vector<unsigned int> &available_doors) {

  return *std::find_if(begin(available_doors), end(available_doors),
                       [&](auto value) {
                         return (value != revealedDoor && value != chosen_door);
                       });
}