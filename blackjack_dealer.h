/* Unseenia Cards @version 0.x
@link    https://github.com/kabuki-starship/unseenia.cards.git
@file    /blackjack_dealer.h
@author  Cale McCollough <https://cale-mccollough.github.io>
@license Copyright (C) 2014-9 Kabuki Starship <kabukistarship.com>;
All right reserved (R). This Source Code Form is subject to the terms of the
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with
this file, You can obtain one at <https://mozilla.org/MPL/2.0/>. */

#pragma once

#ifndef UNSEENIA_CARDS_BLACKJACK_DEADER_HEADER
#define UNSEENIA_CARDS_BLACKJACK_DEADER_HEADER

#include <_config.h>

#include "dealer.h"
#include "deck.h"
#include "player.h"

namespace unseenia {
namespace blackjack {
/* A class that represnts a dealer in a card game.
A dealer has the Deck of cards, but is not neccissaraly a player. A dealer
needs to keep track of all of the Players. A BlackjackDealer is both a Player
and a Dealer at the same time.
*/
class BlackjackDealer : public Player, public Dealer {
 public:
  static const SIN deck_count_ = 1,  //< The number of decks for this game.
      deck_size_ = 52,               //< The number of cards in the Deck.
      startingPoints = 999999,       //< The dealers starting points.
      starting_ante_ = 5,            //< The starting ante_.
      min_bet_ = 1,                  //< The minimum bet.
      min_cards_per_hand_ = 2,       //< The minimum number of cards in a hand.
      max_cards_per_hand_ =
          Deck::kDefaultCardCount,  //< The maximum number of cards in a hnd.
      maxNumPlayer = 2;             //< The maximum number of players.

  /* */
  BlackjackDealer(const CHR* name = nullptr);
};
}  // namespace blackjack
}  // namespace unseenia
#endif
