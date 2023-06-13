/*
 * converter_test.cpp
 *
 *  Created on: 10 Jun 2020
 *   Author(s): Jorn Reniers
 */

#include "../../src/slide.hpp"

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_string.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include <cmath>
#include <cassert>
#include <iostream>
#include <fstream>

using Catch::Matchers::WithinAbs;
using namespace slide;

constexpr double TOL_EQ = 1e-15;

TEST_CASE("Test losses", "[Converter]")
{
  slide::Converter c;

  //!< print the efficiency for a 1C charge for a small cell
  double I = 16;
  double v, loss, relloss;
  /*for(int i=0;i<16;i++){
          v = (2.7+i/10.0);
          loss = c.getLosses(v, I);
          relloss = loss / (I*v);

          std::cout<<"V = "<<v/(15.0*20.0)<<", I = "<<I<<", loss = "<<loss<<" W or "<<relloss*100<<" %"<<endl;

          //!< check the losses are between 0 and 15 %
          REQUIRE(relloss > 0);
          REQUIRE(relloss < 0.15);											//!< even at 0 W input, the losses are about 1.5 kW due to constant terms (switching, losses on DC bus, etc)
  }*/

  //!< print the efficiency for a 1C charge for a large battery (for 9p, 15s 20s)
  I = 9 * 16;
  for (int i = 0; i < 16; i++) {
    v = 15 * 20 * (2.7 + i / 10.0);
    loss = c.getLosses(v, I);
    relloss = loss / (I * v);

    //!< check the losses are between 0 and 15 %
    REQUIRE(relloss > 0);
    REQUIRE(relloss < 0.15);

    //!< cout<<"V = "<<v/(15.0*20.0)<<", I = "<<I<<", loss = "<<loss<<" W or "<<relloss*100<<" %"<<endl;
  }

  //!< print losses for a number of batteries
  v = 3.7;
  I = 16;
  /*cout<<"Losses for a single cell are "<<c.getLosses(v,I)<<" W or "<<c.getLosses(v,I)/(I*v)*100<<" %"<<endl;
  std::cout<<"Losses for a 10 parallel cells are "<<c.getLosses(v,I*10)<<" W or "<<c.getLosses(v,I)/(I*10*v)*100<<" %"<<endl;
  std::cout<<"Losses for a 10 series cells are "<<c.getLosses(v*10,I)<<" W or "<<c.getLosses(v,I)/(I*10*v)*100<<" %"<<endl;
  std::cout<<"Losses for a 10 series of 10 parallel cells are "<<c.getLosses(v*10,I*10)<<" W or "<<c.getLosses(v,I)/(I*100*v)*100<<" %"<<endl;
  std::cout<<"Losses for a 100 series of 10 parallel cells are "<<c.getLosses(v*100,I*10)<<" W or "<<c.getLosses(v,I)/(I*1000*v)*100<<" %"<<endl;*/
  /*
   * single cell: 1.5 kW 		1500 W per cell
   * 10 parallel: 2.2 kW		220 W per cell
   * 10 series: 1.5 kW 		150 W per cell
   * 10s 10p = 2.2 kW 		22 W per cell
   * 100s 10p = 2.2 kW 		2.2 W per cell
   */

  /*//!< EPFL battery: 9p * 15s * 20s7p
  I = 16 * 9 * 7;
  v = 4.2 * 15 * 20;
  c.setPower(I*v);
  v = 4.2 * 15 * 20;
  std::cout<<"Losses for the EFL battery at Vmax are "<<c.getLosses(v,I)<<" W or "<<c.getLosses(v,I)/(I*v)*100<<" %"<<endl;
  v = 3.7 * 15 * 20;
  std::cout<<"Losses for the EFL battery at Vnom are "<<c.getLosses(v,I)<<" W or "<<c.getLosses(v,I)/(I*v)*100<<" %"<<endl;
  v = 2.7 * 15 * 20;
  std::cout<<"Losses for the EFL battery at Vmin are "<<c.getLosses(v,I)<<" W or "<<c.getLosses(v,I)/(I*v)*100<<" %"<<endl;
  */

  // #TODO activate the commented out parts.
}