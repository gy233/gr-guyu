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

#ifndef INCLUDED_GUYU_MY_FILE_SINK_IMPL_H
#define INCLUDED_GUYU_MY_FILE_SINK_IMPL_H

#include <guyu/my_file_sink.h>

namespace gr {
  namespace guyu {

    class my_file_sink_impl : public my_file_sink
    {
     private:
      size_t d_itemsize;
      double d_sample_rate;
      int d_duration;
      double d_nwritten_total;
      char d_filename[100];
      const char *d_filename_const;

     public:
      my_file_sink_impl(double sample_rate, int duration, size_t itemsize, const char *filename, bool append=false);
      ~my_file_sink_impl();

      // Where all the action really happens
      int work(int noutput_items,
         gr_vector_const_void_star &input_items,
         gr_vector_void_star &output_items);
    };

  } // namespace guyu
} // namespace gr

#endif /* INCLUDED_GUYU_MY_FILE_SINK_IMPL_H */

