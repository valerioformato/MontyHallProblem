#include <memory>
#include <random>
#include <vector>

class Player {
public:
  Player(std::shared_ptr<std::mt19937> mtGen) : _mtGen(mtGen){};

  unsigned int ChooseDoor(const std::vector<unsigned int> &available_doors);

  unsigned int Player::SwitchDoor(unsigned int chosen_door,
                                  unsigned int revealedDoor,
                                  const std::vector<unsigned int> &available_doors);

private:
  std::shared_ptr<std::mt19937> _mtGen;
};