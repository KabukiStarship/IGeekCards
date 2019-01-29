/* Kabuki Card Games
    @file    /.../KabukiTheater-Examples/ShapesDrawingDemo/BallonTest.hpp
    @author  Cale McCollough <cale.mccollough@gmail.com>
    @license Copyright (C) 2016 [Cale McCollough](calemccollough.github.io)

                            All right reserved (R).

        Licensed under the Apache License, Version 2.0 (the "License"); you may
        not use this file except in compliance with the License. You may obtain
        a copy of the License at

                    http://www.apache.org/licenses/LICENSE-2.0

        Unless required by applicable law or agreed to in writing, software
        distributed under the License is distributed on an "AS IS" BASIS,
        WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
        See the License for the specific language governing permissions and
        limitations under the License.
*/

#include <KabukiTheater.hpp>

namespace KabukiTheaterExamples {

class Ballon
{
    public:

    Ballon (SI4 xValue, SI4 yValue, SI4 zValue, Color shade);

    void setX (SI4 newX;

    void setY (SI4 newY);

    void setZ (SI4 newZ);

    SI4 getZ ();

    void draw (Cell& C);

    void newPos ();

    private:

    SI4 x, 
        y, 
        z, 
        value, 
        place, 
        ballonNumber;
        
    Color color;
   
};

}   //< KabukiTheaterExamples
