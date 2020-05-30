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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include "my_file_sink_impl.h"
#include <stdexcept>
#include <cstring>
#include <ctime>

namespace gr {
  namespace guyu {

    my_file_sink::sptr
    my_file_sink::make(double sample_rate, int duration, size_t itemsize, const char *filename, bool append)
    {
      return gnuradio::get_initial_sptr
        (new my_file_sink_impl(sample_rate, duration, itemsize, filename, append));
    }

    /*
     * The private constructor
     */
    my_file_sink_impl::my_file_sink_impl(double sample_rate, int duration, size_t itemsize, const char *filename, bool append)
      : gr::sync_block("my_file_sink",
              gr::io_signature::make(1, 1, itemsize),
              gr::io_signature::make(0, 0, 0)),
        file_sink_base(filename, true, append),
        d_itemsize(itemsize),
        d_sample_rate(sample_rate),
        d_duration(duration),
        d_filename_const(filename)
    {
      d_nwritten_total=0;
      strcpy(d_filename,filename);
    }

    /*
     * Our virtual destructor.
     */
    my_file_sink_impl::~my_file_sink_impl()
    {
    }

    int
    my_file_sink_impl::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {
      char *inbuf = (char*)input_items[0];
      int  nwritten = 0;

      do_update();                    // update d_fp is reqd

      if(!d_fp)
        return noutput_items;         // drop output on the floor

      while(nwritten < noutput_items) {
        int count = fwrite(inbuf, d_itemsize, noutput_items - nwritten, d_fp);
        if(count == 0) {
          if(ferror(d_fp)) {
            std::stringstream s;
            s << "file_sink write failed with error " << fileno(d_fp) << std::endl;
            throw std::runtime_error(s.str());
          }
          else { // is EOF
            break;
          }
        }
        nwritten += count;
        inbuf += count * d_itemsize;
      }

      if(d_unbuffered)
        fflush (d_fp);
      
      d_nwritten_total = d_nwritten_total + nwritten;
      if (d_nwritten_total > d_sample_rate * d_duration)
      {
        close();
        d_nwritten_total = 0;
        std::time_t now = std::time(0);
        char* dt = std::ctime(&now);
        strcpy(d_filename,d_filename_const);
        strcat(d_filename,dt);
        open(d_filename);
      }
      return nwritten;
    }

  } /* namespace guyu */
} /* namespace gr */

