/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledos-sa <ledos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 19:42:33 by ledos-sa          #+#    #+#             */
/*   Updated: 2023/10/13 22:38:26 by ledos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
class Contact {
private:
  char *firstName;
  char *lastName;
  char *nickname;
  int phoneNumber;
  char *darkSecreat;

public:
  Contact( char *firstName,  char *lastName,  char *nickname,  int phoneNumber,
           char *darkSecreat) {
    this->firstName = firstName;
    this->lastName = lastName;
    this->nickname = nickname;
    this->phoneNumber = phoneNumber;
    this->darkSecreat = darkSecreat;
  }
  char *getfirstName() { return firstName; }
  char *getlastName() { return lastName; }
  char *getnickName() { return nickname; }
  char *getdarkSecreat() { return darkSecreat; }
};

class PhoneBook {
private:
  Contact contactos[8];

private:
  int counter = 0;

public:
  PhoneBook();
  int add(Contact contacto) {
    if (counter == 9) {
      std::cout << "Ta cheio\n";
      return (1);
    }
    contactos[counter] = contacto;
    counter++;
    return (0);
  }
};
int main(int argc, char *argv[]) {
  PhoneBook x = PhoneBook();
	x.add(Contact("Leonardo", "Maia", "leo", 916892137, "era uma vez"));
  // int x = 0;
}
