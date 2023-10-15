#include <chrono>
#include <iostream>
#include <thread>

#include "Greeter.h"

int main(void) {
  // print the iikh logo
  std::cout << "  III   III   K  K  H  H" << std::endl;
  std::cout << "   I     I    K K   H  H" << std::endl;
  std::cout << "   I     I    KK    HHHH" << std::endl;
  std::cout << "   I     I    K K   H  H" << std::endl;
  std::cout << "  III   III   K  K  H  H" << std::endl;

  // halt for 1s
  std::this_thread::sleep_for(std::chrono::seconds(1));

  Greeter g;

  while (true) {
    system("cls");
    g.printAndSelectMenu();
    system("pause");
  }

  return 0;
}
