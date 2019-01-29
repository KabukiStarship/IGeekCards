/* Kabuki Arcade
    @file       ~/source/kabuki/arcade/cards/arcade_blackjack_player.cc
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

#include "hand.h"
#include "card_stack.h"
#include "blackjack_player.h"

using namespace _;
using namespace std;
using namespace kabuki::id;

namespace kabuki { namespace cards {

SI4 BlackjackScore (Hand& hand, SI4 ace_value) {
    SI4 score = 0;  //< Always set the variable before you start using it!!!

    CardStack& cards = hand.GetVisibleCards ();
    Card* card;
    for (SI4 i = 0; i < cards.Length (); ++i) {
        card = cards.GetCard (i);
        SI4 denomination = card->GetDenomination ();
        score += ((denomination == Card::kAce) ? ace_value : denomination);
    }

    return score;
}

SI4 BlackjackMinScore (Hand& hand) {
    return BlackjackScore (hand, 1);
}

SI4 BlackjackMaxScore (Hand& hand) {
    return BlackjackScore (hand, 11);
}


SI4 BlackjackCompareHands (Hand& a, Hand& b) {
    SI4 a_min = BlackjackMinScore (a),
        a_max = BlackjackMaxScore (a),
        b_min = BlackjackMinScore (b),
        b_max = BlackjackMaxScore (b);

    if (a_min == 21 || a_max == 21)
        if (b_min == 21 || b_max == 21) // We both got 21!
            return 2;
        else
            return 3; //< We won!

    if (b_min == 21 || b_max == 21) //< We lost.
        return -2;

    SI4 best_score = a_max > 21?a_min:a_max,
        other_best_score = b_max > 21?b_min:b_max;

    if (best_score > 21)           //< We lost :-(
        if (other_best_score > 21) //< We both lost!
            return -2;
        else
            return -1;

    if (other_best_score > 21)     //< We won!!!
        return 1;

    if (best_score > other_best_score)
        return 1;

    //if (best_score == other_best_score)
    return 0;
}


BlackjackPlayer::BlackjackPlayer (id::User* user, CardStack& stock,
                                  BOL is_dealder) :
    Player (user, is_dealder),
    stock_ (stock) {
    // Nothing to do here!
}

BlackjackPlayer::~BlackjackPlayer () {
    // Nothing to do here.
}

void BlackjackPlayer::Hit () {
    is_turn_ = false;
    state_ = kStateWaitingForTurn;
#if DEBUG_SCRIPT
    cout << "\n| Player " << GetHandleKey () << " hits.";
#endif //< DEBUG_SCRIPT
}

void BlackjackPlayer::Hold () {
    is_turn_ = false;
    state_ = kStateHolding;
#if DEBUG_SCRIPT
    cout << "\n| Player " << GetHandleKey () << " holds.";
#endif //< DEBUG_SCRIPT

}

const CH1* BlackjackPlayer::SetState (SI4 state) {
    static const CH1* error = "Invalid state";
    if (state < 0) {
        return error;
    }
    if (state > 3) {
        return error;
    }
    state_ = state;
    return nullptr;
}

BOL BlackjackPlayer::IsHolding () {
    return state_ == kStateHolding;
}

/*
Array<CardCombo> BlackjackPlayer::GetHandCombos () {
    auto low_score,
        high_score;

    scores.low = 0;  //< scores.low is the total of the cards with aces as 1
    scores.high = 0; //< scores.high is the number of aces to add on an opt 10.

    for (SI4 s = 0; s < GetCount (); ++s) {
        SI4 currentValue = GetCard (s)->GetPip ();

        if (currentValue == 1) // First check if its an ace
        {
            ++scores.low;       //< Aces low means add 1 to the low total.
            scores.high += 10;  //< Aces high means add a 10 to the high total.
        } else if (currentValue >= 10) {
            // Next check to see if its a Jack, Queen, or King because they
            // are all 10 points.

            scores.low += 10;
            scores.high += 10;
        } else {
            // then its just number card so add it to both the low and high totals.
            scores.low += currentValue;
            scores.high += currentValue;
        }
    }

    return scores;
}*/

BOL BlackjackPlayer::Is21 () {
    return BlackjackMinScore (hand_) == 21 || BlackjackMaxScore (hand_) == 21;
}

BOL BlackjackPlayer::IsBust () {
    return BlackjackMaxScore (hand_) > 21;
}

/*
BOL BlackjackPlayer::PlayOrPass () {
    // Estimated chances of winning. 
    static const float chanes_of_winning_low[] = {
        0.1f, 0.2f, 0.3f, 0.4f, 0.5f, 0.6f, 0.7f, 0.8f, 0.9f
    };
    static const float chanes_of_winning_high[] = {
        0.6f, 0.6f, 0.5f, 0.5f, 0.4f, 0.4f, 0.2f, 0.2f, 0.2f
    };

    SI4 this_high_score  = GetScore (Deck::kAcesHigh),
        this_low_score   = GetScore (Deck::kAcesLow),
        other_high_score = other_score.GetScore (Deck::kAcesHigh),
        other_low_score  = other_score.GetScore (Deck::kAcesLow);

    if (this_low_score > 21) //< Then we definitely lost.
        return false;

    if (this_low_score == 21 || this_high_score == 21) {
        // Then we might have won so don't play again or we'll loose!
        return false;
    }

    if (this_high_score <= 21 - 10) {
        // The highest card value is 10, so if our highest score is less than
        // 11, then we can take any card and not go over 21.
        return true;
    }

    if (this_high_score < other_high_score) {
        // Than we have to play or we loose.
        return true;
    }
    */
    /* From here on out, we don't actually have to take another card because
        we might go over and loose, so we're playing a numbers game.

        At this point in time, we are less than 10 points away from going bust,
        and each number of points away from 21 we are has an x percent chance
        loosing. In this case, we should figure out what the percent chance is,
        and only take another card if the chances are high enough. 
    float chance_of_winning;

    if (this_high_score < 21) {
        SI4 numPointsLeft = 21 - this_high_score;
        chance_of_winning = chanes_of_winning_low[numPointsLeft];
    } else {
        SI4 numPointsLeft = 21 - this_low_score;
        chance_of_winning = chanes_of_winning_high[numPointsLeft];
    }

    if (chance_of_winning >= 0.5)
        return true;*/

    /* To do this, we're going to use a random number between 0 and 1, and
        multiply it by a number between 1-10 to get a percent.
        For example, a 50% chance of winning would get the number 5, then if you
        multiplied that by a random number between 0 and 1, then we have a 50%
        chance of getting a number greater than 0.5. 

    float randomNumberBetween0and1 = RandomFloat ();
    // We want to pick a random number between 0 and 1
    // If the percent chance is greater than 50%, then we should take another
    // card.
    return chance_of_winning * randomNumberBetween0and1 >= 0.5;
}*/

void BlackjackPlayer::RestartGame () {

}

void BlackjackPlayer::BeginRound () {

}

void BlackjackPlayer::PlayRound () {
    cout << "\n| " << GetHandle () << "'s turn.";
    if (IsBust () || Is21 ()) {
        // If the player's hand is a bust, than the dealer is not allowed to
        // deal that player another card.
        state_ = kStateHolding;
        return;
    }
    Card* card = stock_.Draw ();
    if (card == nullptr) {  // Always check for error conditions first!
        cout << "\n| Error! The Deck was empty.";
        state_ = kStateHolding;
        return;
    }

    hand_.GetVisibleCards ().Push (card);

    if (IsBust ()) {
        // If the player's hand is a bust, than the dealer is not allowed to
        // deal that player another card.
        state_ = kStateHolding;
    }
}

void BlackjackPlayer::EndRound () {

}

void BlackjackPlayer::EndGame () {

}

SI4 BlackjackPlayer::Compare (Hand& other) {
    return BlackjackCompareHands (hand_, other);
}

BOL BlackjackPlayer::Wins (Hand& other) {
    return BlackjackCompareHands (hand_, other) > 0;
}

Text& BlackjackPlayer::PrintStats (Text& txt) {
    return txt << "\n| BlackjackPlayer: " << GetHandle ();
}

Text& BlackjackPlayer::Print (_::Text& txt) {
    User* user = GetUser ();
    
    return txt << txt.Line ('_')
               << "\n| Player   : " << user->GetHandleKey ()
               << "\n| Num Chips: " << user->GetValue ()
               << " Wins: " << num_wins_
               << hand_.GetVisibleCards ().Print (txt)
               << txt.Line ('_');
}

const Operation* BlackjackPlayer::Star (uint index, _::Expression* expr) {
    static const Operation This = { "BlackjackPlayer",
        OperationCount (0), OperationFirst ('A'),
        "Player in a Blackjack game.", 0 };
    void* args[2];
    CH1 handle[Handle::kMaxLength],
        tweet[141];
    switch (index) {
        case '?': return ExpressionOperation (expr, &This);
        case 'A': {
            static const Operation OpA = { "Hit",
                Params<0> (), Params<0> (),
                "Signals a player to \"hit me\" and take another card.", 0 };
            if (!expr) return &OpA;
            if (!IsTurn ()) {
                return Result (expr, Bin::kErrorInvalidOperand);
            }
            SetState (kStatePlayingRound);
        }
        case 'B': {
            static const Operation OpA = { "Hold",
                Params<0> (), Params<0> (),
                "Signals a player to \"hold\" and not take any more cards "
                "this round.", 0 };
            if (!expr) return &OpA;
            if (!IsTurn ()) {
                return Result (expr, Bin::kErrorInvalidOperand);
            }
            SetState (kStatePlayingRound);
        }
        case 'C': {
            static const Operation OpA = { "Tweet",
                Params<2, STR, Handle::kMaxLength, STR, 141> (), Params<0> (),
                "Sends a message of 140 chars or less to this player.", 0 };
            if (!expr) return &OpA;
            if (ExpressionArgs (expr, Params<2, STR, Handle::kMaxLength, STR,
                                       141> (),
                          Args (args, handle, tweet))) return expr->result;
            cout << "\n| Message from @" << handle << "\n| " << tweet;
            return nullptr;
        }
    }
    return Result (expr, Bin::kErrorInvalidOperation);
}

const CH1* BlackjackPlayer::Sudo (const CH1* text,
                                         const CH1* strand_end) {
    return nullptr;
}

}   //< namespace cards
}   //< namespace kabuki
