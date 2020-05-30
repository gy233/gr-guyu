/* -*- c++ -*- */
/* 
 * Copyright 2020 guyu.
 * 
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 * 
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifndef INCLUDED_GUYU_MY_DQPSK_DEMOD_IMPL_H
#define INCLUDED_GUYU_MY_DQPSK_DEMOD_IMPL_H

#include <guyu/my_DQPSK_Demod.h>

#define PI 3.14159265358979323846

namespace gr {
  namespace guyu {

    class my_DQPSK_Demod_impl : public my_DQPSK_Demod
    {
     private:
      float diff_angle;
      float last_angle;

     public:
      my_DQPSK_Demod_impl();
      ~my_DQPSK_Demod_impl();

      // Where all the action really happens
      int work(int noutput_items,
         gr_vector_const_void_star &input_items,
         gr_vector_void_star &output_items);
    };

  } // namespace guyu
} // namespace gr

#endif /* INCLUDED_GUYU_MY_DQPSK_DEMOD_IMPL_H */

