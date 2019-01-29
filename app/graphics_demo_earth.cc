/* Kabuki Starship
    @file    /.../KabukiTheater-Examples/Software3DWireFrameViewer/SoftwareEngine.cpp
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

#include "SoftwareEngine.hpp"

namespace KabukiTheaterExamples {

HotAirBalloon::HotAirBalloon (SoftwareEngine driver, _2D::Point_f initPosition, string balloonName)
:   _3D::Shape (driver, initPosition, "Models/sphere2.plg"),
    name (balloonName)
{
    name = balloonName;
}

void HotAirBalloon::increaseHelliumFlow ()
{
    helliumFlow += (FLT) 0.01;
}

void HotAirBalloon::decreaseHelliumFlow ()
{
    helliumFlow += (FLT) 0.01;
}

void HotAirBalloon::addHellium ()
{
    helliumLift += helliumFlow;
}

void HotAirBalloon::removeHellium ()
{
    HotAirBalloon::helliumLift -= helliumFlow;
}

void HotAirBalloon::setUpNextFrame (SoftwareEngine driver)
{
    _3D::Vect
    translateX (driver.getWindVector().x);        
    translateZ (driver.getWindVector().z);
    translateY (driver.getWindVector().z + helliumLift);
}

void HotAirBalloon::print (Terminal& io)
{
    io.prints (name, ": position = ");
    getPosition().print (io);
}

}   //< KabukiTheaterExamples
