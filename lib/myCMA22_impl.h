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

#ifndef INCLUDED_GUYU_MYCMA22_IMPL_H
#define INCLUDED_GUYU_MYCMA22_IMPL_H

#include <guyu/myCMA22.h>
#include <gnuradio/filter/fir_filter.h>
#include <gnuradio/math.h>
#include <stdexcept>

namespace gr {
  namespace guyu {

    class myCMA22_impl : public myCMA22
    {
    private:
      std::vector<gr_complex> d_new_taps;
      std::vector<gr_complex> d_new_taps1;
      bool d_updated;
      gr_complex d_error;

      float d_modulus;
      float d_mu;
      int d_iter;
      bool d_print_flag;

      gr::filter::kernel::fir_filter_ccc* d_filter_1;
      gr::filter::kernel::fir_filter_ccc* d_filter_2;

    protected:
      gr_complex error(const gr_complex &out);
      void update_tap(gr_complex &tap, const gr_complex &in);

     public:
      myCMA22_impl(int num_taps, float modulus, float mu, int sps, int iter, bool print_flag);
      ~myCMA22_impl();

      void set_taps(const std::vector<gr_complex> &taps);
      std::vector<gr_complex> taps() const;

      float gain() const
      {
	return d_mu;
      }

      void set_gain(float mu) 
      {
	if(mu < 0.0f || mu > 1.0f) {
	  throw std::out_of_range("myCMA22::set_gain: Gain value must be in [0,1]");
	}
	d_mu = mu;
      }
    
      float modulus() const
      {
	return d_modulus;
      }

      void set_modulus(float mod) 
      {
	if(mod < 0)
	  throw std::out_of_range("myCMA22::set_modulus: Modulus value must be >= 0");
	d_modulus = mod;
      }
      
      float iteration() const
      {
	return d_iter;
      }

      void set_iteration(float iter) 
      {
	if(iter != 1)
	  throw std::out_of_range("myCMA22::set_iteration: Iteration value must be 1");
	d_iter = iter;
      }
      
      gr_complex print_error() const
      {
        return d_error;
      }
      
      // Where all the action really happens
      int work(int noutput_items,
         gr_vector_const_void_star &input_items,
         gr_vector_void_star &output_items);
    };

  } // namespace guyu
} // namespace gr

#endif /* INCLUDED_GUYU_MYCMA22_IMPL_H */

