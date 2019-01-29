﻿/* Kabuki Arcade
    @file    ~/source/kabuki/arcade/cards/arcade_card_game.cc
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

#include "client.h"

using namespace _;
using namespace kabuki::id;
using namespace std;

namespace kabuki { namespace cards {

Client::Client ():
    authenticator_ (new AuthenticatorDefault ()),
    state_        (0),
    round_number_ (0),
    user_         (authenticator_) {
    game_name_[0] = 0;
}

Client::~Client () {
    DeleteRemotePlayers ();
    delete authenticator_;
}

void Client::DeleteRemotePlayers () {
    for (SI4 i = players_.size (); i > 0; --i) {
        PlayerProxy* player = players_.back ();
        players_.pop_back ();
        delete player;
    }
}

uint Client::GetState () {
    return state_;
}

BOL Client::SetState (SI4 state) {
    if (state < 0) {
        return false;
    }
    state_ = state;
    return true;
}

void Client::PrintPlayers () {
    for (size_t i = 0; i < players_.size (); ++i) {
        players_[i]->Print (txt);
    }
}

void Client::PrintRoundStats () {
    PrintLine ('~');
    cout << "Round: " << round_number_ << "\n";

    PrintLine ('~');
}

Text& Client::Print (_::Text& txt) {
    PrintLine ('_');
    txt << "\n| " << game_name_
         << "\n| Num Players : " << players_.size () 
         << " Max: " << players_.capacity ()
         << "\n| Round Number: " << round_number_
         << "\n| Num Players : " << players_.size ();

    PrintPlayers ();
    PrintLine ('_');
}

const CH1* Client::Sudo (const CH1* text, const CH1* strand_end) {
    if (!(text = TextSkipSpaces (text, strand_end))) {
        return nullptr;
    }
}

const Operation* Client::Star (uint index, _::Expression* expr) {
    static const Operation This = { "CardsClient",
        OperationCount (0), OperationFirst ('A'),
        "kabuki::cards Script client.", 0
    };
    void* args[4];
    PlayerProxy* player;
    switch (index) {
        case '?': return &This;
        case 'A': {
            static const Operation OpA = { "SetState",
                Params<1, UI1> (), Params<0> (),
                "Sets the client state.", 0
            };
            if (!expr) return &OpA;
            byte state;
            if (!ExpressionArgs (expr, Params<1, UI1> (), Args (args, &state)))
                return expr->result;
            SetState (state);
            return nullptr;
        }
        case 'B': {
            static const Operation OpB = { "Print",
                Params<1, STR, kMaxMessageLength + 1> (), Params<0> (),
                "Sets the client state.", 0
            };
            if (!expr) return &OpB;
            CH1 buffer[kMaxMessageLength + 1];
            if (!ExpressionArgs (expr, Params<1, STR, kMaxMessageLength + 1> (),
                           Args (args, buffer)))
                return expr->result;
            cout << buffer;
            return nullptr;
        }
        case 'C': {
            static const uint_t* kRxHeaderC = Params<1, SI4,
                STR, User::kMaxStatusLength + 1,
                STR, Handle::kMaxLength + 1> ();
            static const Operation OpC = { "SetPlayer",
                kRxHeaderC, Params<0> (),
                "Sets the player at the given #index to the given "
                "#dislpay_name.", 0
            };
            if (!expr) return &OpC;
            int32_t player_number;
            CH1 status[User::kMaxStatusLength + 1],
                 handle[Handle::kMaxLength];
            if (!ExpressionArgs (expr, kRxHeaderC, Args (args, &player_number,
                                                   status, handle)))
                return expr->result;
            if (player_number < 0) {
                return Result (expr, Bin::kErrorInvalidArgument,
                               Params<1, SI4> ());
            }
            if (player_number > kMaxPlayers) {
                return Result (expr, Bin::kErrorInvalidArgument,
                               Params<1, SI4> ());
            }
            players_.reserve (player_number);
            player = players_[player_number];
            player->SetDislpayName (status);
            player->SetHandle (handle);
            return nullptr;
        }
    }
    return nullptr;
}

}       //< namespace cards
}       //< namespace kabuki
