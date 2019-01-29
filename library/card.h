/* Kabuki Arcade
    @file    ~/source/kabuki/arcade/cards/card.h
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

#ifndef KABUKI_ARCADE_CARDS_CARD
#define KABUKI_ARCADE_CARDS_CARD

#include "suit.h"

namespace kabuki { namespace cards {

/* Class that represents a card in a card game.
    Cards as we know them originated in Europe. We traditionally think of cards
    as only being clubs, hearts, diamonds, and spades, but there are also some
    other variations from other European countries. For more information on
    them, please @wiki "Playing Card Suits". The nifty thing about these extra
    card decks, is that we can make a double deck of cards, and use the suit
    format to tell the decks apart.
*/
class KABUKI Card {
    public:

    enum {
        kJoker = 0,  //< Pip value of a Joker.
        kAce   = 1,  //< Pip value of an Ace.
        kJack  = 11, //< Pip value of a Jack.
        kQueen = 12, //< Pip value of a Queen.
        kKing  = 13, //< Pip value of a King.
    };

    /* Default constructor.
        There exists a single unique card for each of the 54 cards in a pack
        of cards. Cards are taken from the pack and shuffled into the deck_
        using pointers.
    */
    Card (SI4 pip = 0, Suit* suit = nullptr, SI4 denomination = 0);

    /* Copy constructor deep-copies the state of the other object. */
    Card (const Card& other);
    
    /* Virtual destructor just in case we want to make a sub-class later. */
    virtual ~Card () {}

    /* Sets the values of the cards. */
    void Set (SI4 pip, Suit* suit, SI4 denomination = ~0);

    /* Compares this Card to the other Card.
        @return Returns 0 if they are identical.
        @return Returns 1 if this Card is greater than the other Card. */
    virtual SI4 Compare (Card* other);
                                          
    /* Compares this Card to the other Card and returns true if the two are
        identical. */     
    BOL Equals (Card* other);

    /* Returns the pip value of this Card 0-13.
        The pip value is a number between 0-13 that represents which card it is: 
        J=0, A=1, 2-10, J=11, Q=12, K=13. */
    SI4 GetPip ();
    
    /* Returns the point value of this Card
        The face value represents how many points this card is worth. */
    SI4 GetDenomination ();
                                     
    /* Sets the point value to the value. */          
    void SetDenomination (SI4 value);

    /* Returns the Suit of this card. */
    Suit* GetSuit ();

    /* Loads and sets the cardImage to the on in the given directory.
        Yes this goes in the library, just no file IO or hardware dependent
        stuff (besides OpenGL, OpenAL, etc).
        @return Returns 0 upon success.
        @return Returns -1 if the directory was actually a file.
        @return Returns 1 if the directory doesn't exist.
        @return Returns 2 if the file doesn't.
        @return Returns 3 if the image didn't load right. */
    //SI4 SetCardImage (const CH1* directory);
                       
    /* Returns the address of this Card's image. */                            
    //Image& GetImage ();
    
    /* Returns a string representation of this Object. */
    _::Text& Print (_::Text& txt = _::Text ());

    /* Overloaded binary operator=. */
    Card& operator= (const Card& other);

    private:

    SI4   pip_,          //< Pip value of this Card from 0-13.
          denomination_; //< Rank of this card in the deck.
    Suit* suit_;         //< Suit of this Card.
    //Image* image_;     //< Image of this Card.

};      //< class Card
}       //< namespace cards
}       //< namespace kabuki
#endif  //< KABUKI_ARCADE_CARDS_CARD
