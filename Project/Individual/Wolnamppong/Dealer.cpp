#include "Dealer.h"

Dealer::Dealer() : bet(0), amount(0) {}

void Dealer::SetBet(int _bet) { bet = _bet; }

void Dealer::SetAmount(int _amount) { amount += _amount;  }

void Dealer::SetRoad(bool _switch) { road = _switch; }

int Dealer::GetBet() { return bet; }

int Dealer::GetAmount() { return amount; }

bool Dealer::GetRoad() { return road; }
