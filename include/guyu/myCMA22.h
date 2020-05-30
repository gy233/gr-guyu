/* -*- c++ -*- */
/* 
 * Copyright 2019 <+YOU OR YOUR COMPANY+>.
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


#ifndef INCLUDED_GUYU_MYCMA22_H
#define INCLUDED_GUYU_MYCMA22_H

#include <guyu/api.h>
#include <gnuradio/sync_decimator.h>

namespace gr {
  namespace guyu {

    /*!
     * \brief <+description of block+>
     * \ingroup guyu
     *
     */
    class GUYU_API myCMA22 : virtual public gr::sync_decimator
    {
    protected:
      virtual gr_complex error(const gr_complex &out) = 0;
      virtual void update_tap(gr_complex &tap, const gr_complex &in) = 0;

     public:
      typedef boost::shared_ptr<myCMA22> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of guyu::myCMA22.
       *
       * To avoid accidental use of raw pointers, guyu::myCMA22's
       * constructor is in a private implementation
       * class. guyu::myCMA22::make is the public interface for
       * creating new instances.
       */
      static sptr make(int num_taps, float modulus, float mu, int sps, int iter, bool print_flag);

      virtual void set_taps(const std::vector<gr_complex> &taps) = 0;
      virtual std::vector<gr_complex> taps() const = 0;
      virtual float gain() const = 0;
      virtual void set_gain(float mu) = 0;
      virtual float modulus() const = 0;
      virtual void set_modulus(float mod) = 0;
      virtual float iteration() const = 0;
      virtual void set_iteration(float iter) = 0;
      virtual gr_complex print_error() const = 0;
    };

  } // namespace guyu
} // namespace gr

#endif /* INCLUDED_GUYU_MYCMA22_H */

