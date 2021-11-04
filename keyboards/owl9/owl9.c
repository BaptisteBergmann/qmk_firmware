/* Copyright 2021 owl
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "owl9.h"
#include "timer.h"



#if defined(RGB_MATRIX_ENABLE)
led_config_t g_led_config = {{// Key Matrix to LED Index
                              {0, 1, 2},
                              {3, 4, 5}},
                             {// LED Index to Physical Position
                              // x = 224 / (NUMBER_OF_COLS - 1) * COL_POSITION
                              // y =  64 / (NUMBER_OF_ROWS - 1) * ROW_POSITION
                                {0, 0},{112, 0},{224, 0}, 
                                {0, 64}, {112, 64}, {224, 64},
                               
                                {224, 64}, {0, 64}, 
                                {0, 0}, {224, 0}
                             }, {// LED Index to Flag
                                4, 4, 4,
                                4, 4, 4,
                                2, 2,
                                2, 2
                             }
                             };



void suspend_power_down_kb(void) {
    rgb_matrix_set_suspend_state(true);
    suspend_power_down_user();
}

void suspend_wakeup_init_kb(void) {
    rgb_matrix_set_suspend_state(false);
    suspend_wakeup_init_user();
}
#endif

