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

#ifndef KABAUKI_CARDS_CLIENT
#define KABAUKI_CARDS_CLIENT

#include "deck.h"
#include "dealer.h"
#include "player_proxy.h"

namespace kabuki { namespace cards {

/* A playing card game client that can play many types of games in the console.
    The server does most of the game logic and feeds the client data on a 
    need to know basis. */
class Client : public id::AuthenticatorDefault, public _::Operation {
    public:

    typedef enum States {
        kStateDisconnected       = 0,
        kStateAwaitingConnection = 1,
        kStateConnected          = 2
    } State;
    
    enum {
        kMaxPlayers          = 64 * 1024, //< Man number of players.
        kDefaultConsoleWidth = 80,        //< Num rows in a DOS console.  
        kMaxMessageLength    = 140,       //< Max message length.
        kMaxGameNameLength   = 63,        //< Max game name length.
    };

    /* Default constructor. */
    Client ();

    /* Virtual destructor. */
    virtual ~Client ();

    void DeleteRemotePlayers ();

    /* Gets the FSM state. */
    uint GetState ();

    /* Virtual function sets the FSM state to a positive value. */
    virtual BOL SetState (SI4 state);

    /* Prints out the PlayerProxy(s). */
    void Client::PrintPlayers ();

    /* Prints the round stats string. */
    void PrintRoundStatsText ();

    /* Prints this game out to the console. */
    virtual _::Text& Print (_::Text& txt = _::Text ());

    /* Script operations. */
    virtual const _::Operation* Star (uint index, _::Expression* expr);

    protected:

    id::Authenticator  * authenticator_;
    CH1                 game_name_[kMaxGameNameLength]; //< Current game name.
    uint32_t             state_,        //< Client app state.
                         round_number_; //< Current round number.
    id::User             user_;         //< User.
    TArray<PlayerProxy*> players_; //< Array of PlayerProxy(s).

};  //< class Client

}       //< namespace cards
}       //< namespace kabuki
#endif  //< KABAUKI_CARDS_CLIENT
