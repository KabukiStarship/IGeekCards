/* Unseenia Cards @version 0.x
@link    https://github.com/kabuki-starship/unseenia.cards.git
@file    /blackjack_card_combo.inl
@author  Cale McCollough <https://cale-mccollough.github.io>
@license Copyright (C) 2014-9 Kabuki Starship <kabukistarship.com>;
All right reserved (R). This Source Code Form is subject to the terms of the
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with
this file, You can obtain one at <https://mozilla.org/MPL/2.0/>. */

#include <_config.h>

#if SEAM >= UNSEENIA_BLACKJACK_CONSOLE
#include "blackjack_card_combo.h"

using namespace unseenia::blackjack;

BlackjackCardCombo::BlackjackCardCombo(CardStack& copyStack,
                                       SIN acesHighLowORNA)
    : CardCombo(copyStack, acesHighLowORNA) {
  setValues(0, 1, 0, 1, acesHighLowORNA);
}

SIN BlackjackCardCombo::PointValue() {
  SIN total = 0;
  Card* current_card;
  for (SIN i = 0; i < CardCount(); ++i) {
    SIN currentPipValue = current_card->PipValue();

    if (currentPipValue == 1) {
      // If its an ace.
      if (AcesHigh())
        total += 10;
      else
        total += 1;
    } else
      total += current_card->PointValue();  //< Then just add the point to to
                                            // the score like normal.
  }
  return total;
}
