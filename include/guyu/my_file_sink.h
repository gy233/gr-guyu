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


#ifndef INCLUDED_GUYU_MY_FILE_SINK_H
#define INCLUDED_GUYU_MY_FILE_SINK_H

#include <guyu/api.h>
#include <gnuradio/sync_block.h>
#include <gnuradio/blocks/file_sink_base.h>

namespace gr {
  namespace guyu {

    /*!
     * \brief <+description of block+>
     * \ingroup guyu
     *
     */
    class GUYU_API my_file_sink : virtual public gr::sync_block,
                                  virtual public gr::blocks::file_sink_base
    {
     public:
      typedef boost::shared_ptr<my_file_sink> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of guyu::my_file_sink.
       *
       * To avoid accidental use of raw pointers, guyu::my_file_sink's
       * constructor is in a private implementation
       * class. guyu::my_file_sink::make is the public interface for
       * creating new instances.
       */
      static sptr make(double sample_rate, int duration, size_t itemsize, const char *filename, bool append=false);
    };

  } // namespace guyu
} // namespace gr

#endif /* INCLUDED_GUYU_MY_FILE_SINK_H */

