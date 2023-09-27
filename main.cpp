#include <iostream>
#include "Greeter.h"

int main(void) {
  //iikh logo 크게 출력

  std::cout << "  III   III  K  K  H  H" << std::endl;
  std::cout << "   I     I   K K   H  H" << std::endl;
  std::cout << "   I     I   KK    HHHH" << std::endl;
  std::cout << "   I     I   K K   H  H" << std::endl;
  std::cout << "  III   III  K  K  H  H" << std::endl;

  //Greeter 객체 생성
  Greeter g;

  while (true) {
    system("cls");
    g.printAndSelectMenu();
    system("pause");
  }

  return 0;
}