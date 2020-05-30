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


#ifndef INCLUDED_GUYU_MY_DQPSK_DEMOD_H
#define INCLUDED_GUYU_MY_DQPSK_DEMOD_H

#include <guyu/api.h>
#include <gnuradio/sync_block.h>

namespace gr {
  namespace guyu {

    /*!
     * \brief <+description of block+>
     * \ingroup guyu
     *
     */
    class GUYU_API my_DQPSK_Demod : virtual public gr::sync_block
    {
     public:
      typedef boost::shared_ptr<my_DQPSK_Demod> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of guyu::my_DQPSK_Demod.
       *
       * To avoid accidental use of raw pointers, guyu::my_DQPSK_Demod's
       * constructor is in a private implementation
       * class. guyu::my_DQPSK_Demod::make is the public interface for
       * creating new instances.
       */
      static sptr make();
    };

  } // namespace guyu
} // namespace gr

#endif /* INCLUDED_GUYU_MY_DQPSK_DEMOD_H */

