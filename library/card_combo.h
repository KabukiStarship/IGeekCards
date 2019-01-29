/* Kabuki Arcade
    @file    ~/source/kabuki/arcade/cards/card_combo.h
    @author  Cale McCollough <cale.mccollough@gmail.com>
    @license Copyright (C) 2017-2018 Cale McCollough <calemccollough@gmail.com>;
             All right reserved (R). Licensed under the Apache License, Version
             2.0 (the "License"); you may not use this file except in
             compliance with the License. You may obtain a copy of the License
             [here](http://www.apache.org/licenses/LICENSE-2.0). Unless
             required by applicable law or agreed to in writing, software
             distributed under the License is distributed on an "AS IS" BASIS,
             WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or
             implied. See the License for the specific language governing
             permissions and limitations under the License.
*/

#ifndef KABUKI_ARCADE_CARDS_CARDCOMBO
#define KABUKI_ARCADE_CARDS_CARDCOMBO

#include "card_stack.h"

namespace kabuki { namespace cards {
    
/* A CardStack point combination in a playing card game.
    There are two major things that will effect a combination's rank besides
    suit rank; the presence of jokers, and if aces are high or low. */
class CardCombo : public CardStack { 
    public:

    /* Default constructor. */
    CardCombo (const CardStack& cards, BOL aces_high = false,
               SI4 joker_pip_1 = 0, SI4 joker_suit_1 = 1,
               SI4 joker_pip_2 = 0, SI4 joker_suit_2 = 2);

    /* Virtual destructor. */
    virtual ~CardCombo ();

    /* Sets the given variables settings. */
    void Set (BOL aces_high = false, SI4 joker_pip_1 = 0, SI4 joker_suit_1 = 1,
              SI4 joker_pip_2 = 0, SI4 joker_suit_2 = 2);

    /* Function that returns the point value with the wild card and ace
        values. */
    virtual SI4 GetValue () = 0;

    /* Returns the joker_pip_1. */
    SI4 GetJokerPip1 ();
    
    /* Sets the joker_pip_1 to the value. */
    BOL SetJokerPip1 (SI4 value);

    /* Returns the joker_suit_1. */
    SI4 GetJokerSuitValue1 ();
    
    /* Sets the joker_suit_1 to the value. */
    BOL SetJokerSuitValue1 (SI4 value);

    /* Returns the joker_pip_2. */
    SI4 GetJokerPip2 ();
    
    /* Sets the joker_pip_2 to the value. */
    BOL SetJokerPip2 (SI4 value);

    /* Returns the joker_suit_2. */
    SI4 GetJokerSuitValue2 ();
    
    /* Sets the joker_suit_2 to the value. */
    BOL SetJokerSuitValue2 (SI4 value);

    /* Returns the joker_pip_1. */
    SI4 AcesHigh ();
    
    /* Sets the joker_pip_1 to the value. */
    void SetAcesHigh (SI4 value);
    
    private:

    BOL aces_high_;     //< Flag represents if aces are high (>1) or 
                         //< low (0), or either (<0).
    SI4  joker_pip_1_,   //< Black joker wildcard pip value.
         joker_suit_1_,  //< Black joker wildcard suit value.
         joker_pip_2_,   //< Red joker wildcard pip value.
         joker_suit_2_;  //< Red joker wildcard suit value.
        
};      //< class CardCombo
}       //< namespace cards
}       //< namespace kabuki
#endif  //< KABUKI_ARCADE_CARDS_CARDCOMBO
