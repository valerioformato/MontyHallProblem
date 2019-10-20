#include <memory>
#include <random>
#include <vector>

class Host {
public:
  Host(unsigned int door) : realDoor(door){};

  unsigned int RevealDoor(unsigned int chosen_door,
                          const std::vector<unsigned int> &available_doors);

  const unsigned int realDoor;
};