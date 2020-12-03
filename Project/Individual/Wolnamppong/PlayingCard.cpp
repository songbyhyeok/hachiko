#include "PlayingCard.h"

PlayingCard::PlayingCard() : num(0), shape("NULL") {}

void PlayingCard::SetShape(string _shape) { shape = _shape; }

void PlayingCard::SetNum(int _num) { num = _num; }

int PlayingCard::GetNum() { return num; }

string PlayingCard::GetShape() { return shape; }


