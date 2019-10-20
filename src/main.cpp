#include "Host.h"
#include "Player.h"

#include <chrono>
#include <functional>
#include <iostream>
#include <memory>
#include <random>
#include <execution>

int main(int argc, char const *argv[]) {

  enum class ExperimentResult { Failed, Success };

  constexpr unsigned int nExperiments = 30000000;

  std::vector<ExperimentResult> switchDoorResults(nExperiments,
                                                  ExperimentResult::Failed);
  std::vector<ExperimentResult> keepDoorResults(nExperiments,
                                                ExperimentResult::Failed);

  std::random_device rd;
  auto mtGen = std::make_shared<std::mt19937>(rd());
  std::uniform_int_distribution<size_t> distr(0, 2);

  auto runExperiment = [&](bool playerSwitch) {

    std::vector<unsigned int> doors{1, 2, 3};
    unsigned int realDoor = doors.at(distr(*mtGen));

    auto player = std::make_unique<Player>(mtGen);
    auto host = std::make_unique<Host>(realDoor);

    auto chosenDoor = player->ChooseDoor(doors);
    auto revealedDoor = host->RevealDoor(chosenDoor, doors);

    auto switchedDoor = player->SwitchDoor(chosenDoor, revealedDoor, doors);

    auto door = playerSwitch ? switchedDoor : chosenDoor;

    return (door == host->realDoor) ? ExperimentResult::Success
                                    : ExperimentResult::Failed;
  };

  auto runSwitchExperiment = std::bind(runExperiment, true);
  auto runKeepExperiment = std::bind(runExperiment, false);

  auto start = std::chrono::steady_clock::now();

  std::generate(begin(switchDoorResults), end(switchDoorResults),
                runSwitchExperiment);
  std::generate(begin(keepDoorResults), end(keepDoorResults),
                runKeepExperiment);

  auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(
      std::chrono::steady_clock::now() - start);

  std::cout << "Took " << duration.count() << " ms.\n";

  auto nSuccessSwitch = std::count_if(
      begin(switchDoorResults), end(switchDoorResults),
      [](ExperimentResult &res) { return res == ExperimentResult::Success; });

  auto nSuccessKeep = std::count_if(
      begin(keepDoorResults), end(keepDoorResults),
      [](ExperimentResult &res) { return res == ExperimentResult::Success; });

  std::cout << "Switch success probability = "
            << static_cast<double>(nSuccessSwitch) / nExperiments << "\n";
  std::cout << "Keep success probability = "
            << static_cast<double>(nSuccessKeep) / nExperiments << "\n";

  std::cout << std::flush;

  return 0;
}
